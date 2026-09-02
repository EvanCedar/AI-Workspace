#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <filesystem>

#include "Document.hpp"
#include "Message.hpp"
#include "Prompt.hpp"
#include "Workspace.hpp"

void prompt_test() {
    Prompt empty;
    assert(empty.empty());

    Prompt p("Reviewer", "Review this requirement.");
    assert(p.title() == "Reviewer");
    assert(!p.empty());

    Prompt same("Reviewer", "Review this requirement.");
    Prompt different("Writer", "something.");
    Prompt sameTitle("Reviewer", "something.");

    assert(p == same);
    assert(p != different);
    assert(p != sameTitle);
}

void message_test() {
    Message empty;
    assert(empty.empty());

    Message m(MessageRole::Assistant, "Hello");

    assert(m.role() == MessageRole::Assistant);
    assert(m.text() == "Hello");
    assert(!m.empty());

    Message same(MessageRole::Assistant, "Hello");
    Message different(MessageRole::User, "Hello");

    assert(m == same);
    assert(m != different);
}

void document_construction_test() {
    Document empty;
    assert(empty.empty());

    Document d("Title", "abc");

    assert(d.title() == "Title");
    assert(d.contents() == "abc");
    assert(d.sourcePath().empty());
    assert(d.characterCount() == 3);
    assert(!d.empty());

}

void document_load_success_test() {
    std::filesystem::create_directory("test_data");

    std::ofstream file("test_data/reference_load.txt");
    file << "Hello from a test file.";
    file.close();

    Document d;
    bool result = d.load("test_data/reference_load.txt");

    assert(result);
    assert(d.title() == "reference_load.txt");
    assert(d.sourcePath() == "test_data/reference_load.txt");
    assert(d.contents() == "Hello from a test file.");
}

void document_load_failure_test() {
    Document d("Original", "Original contents");

    bool result = d.load("file_that_does_not_exist.txt");

    assert(!result);
    assert(d.title() == "Original");
    assert(d.contents() == "Original contents");
    assert(d.sourcePath().empty());
}


void workspace_test() {
    Workspace w("Demo");

    w.addDocument(Document("Doc", "contents"));
    w.addPrompt(Prompt("Reviewer", "Review this."));
    w.addMessage(Message(MessageRole::User, "Hello"));

    assert(w.documentCount() == 1);
    assert(w.promptCount() == 1);
    assert(w.messageCount() == 1);

    assert(w.documentAt(0).title() == "Doc");
    assert(w.promptAt(0).title() == "Reviewer");
    assert(w.messageAt(0).text() == "Hello");
}

void workspace_invalid_index_test() {
    Workspace w;

    bool threw = false;

    try {
        w.documentAt(0);
    }
    catch (const std::out_of_range&) {
        threw = true;
    }

    assert(threw);
}

void workspace_copy_test() {
    Workspace original("Original");
    original.addPrompt(Prompt("Prompt", "Original text"));

    Workspace copy = original;

    original.setName("Changed");
    original.promptAt(0).setText("Changed text");

    assert(copy.name() == "Original");
    assert(copy.promptAt(0).text() == "Original text");
}


int main() {
    prompt_test();
    message_test();
    document_construction_test();
    document_load_success_test();
    document_load_failure_test();
    workspace_test();
    workspace_invalid_index_test();
    workspace_copy_test();

    std::cout << "M0 tests passed\n";
    return 0;
}
