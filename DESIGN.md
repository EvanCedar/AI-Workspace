# M0 Design and Understanding Note

Answer briefly in your own words. This is not intended to be a long report.

1. `Workspace` is responsible for storing and organizing collections of Documents, Prompts, and Messages. `Document`, `Prompt`, and `Message` are responsible for managing their own data and behavior.

2. The collections in `Workspace` are private so they cannot be changed directly from outside the class. On a `Workspace` class can acces and change those collections. The non-const `At`  allow stored objects to be modified, while the const allow them to be accessed without being changed.

3. One meaningful test I added checks that a failed `Document::load()` does not change the existing Document. This could catch an implementation that clears or partially modifies the Document before discovering that the file could not be opened.

4. One implementation decision I verified was using `vector::at()` instead of `operator[]` in the Workspace retrieval functions. This ensures an invalid index throws `std::out_of_range`, as required by the specification.

5. I used generative AI to help explain C++ concepts, review the assignment requirements, assist with debugging syntax errors, and help generate ideas for test cases.
I affirm that I have thoroughly reviewed all AI-assisted code listed above, that I fully understand how it operates within the broader application architecture, and that I am able to modify or debug it independently.