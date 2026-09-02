#include "Document.hpp"

#include <fstream>
#include <sstream>
#include <utility>

Document::Document(std::string title, std::string contents) : title_(std::move(title)), contents_(std::move(contents)) {
    
    // nothing.

}

bool Document::operator==(const Document& other) const {
    return title_ == other.title_ &&  sourcePath_ == other.sourcePath_ && contents_ == other.contents_;

}

bool Document::operator!=(const Document& other) const {
    return !(*this == other);
}



bool Document::load(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return false;
    }
    std::ostringstream buffer;
    buffer << file.rdbuf();

    if(file.bad()) {
        return false;
    }

    std::string newContents = buffer.str();
    std::size_t lastSlash = path.find_last_of("/\\");
    std::string newTitle;

    if (lastSlash == std::string::npos) {
        newTitle = path;
    } else {
        newTitle = path.substr(lastSlash + 1);
    }

    sourcePath_ = path;
    title_ = std::move(newTitle);
    contents_ = std::move(newContents);
    return true;
}

const std::string& Document::title() const noexcept {
    return title_;

}

const std::string& Document::sourcePath() const noexcept {
    return sourcePath_;

}

const std::string& Document::contents() const noexcept {
    return contents_;
  
}

void Document::setTitle(std::string title) {
    title_ = std::move(title);
  
}

std::size_t Document::characterCount() const noexcept {
    return contents_.size();
    
}

bool Document::empty() const noexcept {
    return contents_.empty();
   
}
