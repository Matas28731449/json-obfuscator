# JSON Obfuscator

<img width="1640" alt="input-output-image" src="https://github.com/Matas28731449/json-obfuscator/assets/116190079/b2694962-366e-4637-8330-1e325c26df48">

## Installation process

1. Clone the GitHub repository:

   ```
   git clone https://github.com/Matas28731449/json-obfuscator.git
   ```

2. Navigate to cloned repository:

   ```
   cd json-obfuscator/
   ```

3. Use Makefile to compile:

   ```
   make
   ```
   OR
   ```
   make run ARGS="path_to_input.json path_to_output.json unicode_format"
   ```
   To compile and run consistently

## Goal

The goal was to write a simple JSON obfuscation tool that would replace the strings in a file with their respective Unicode escape sequences, making it more difficult for a human reader to analyze it. The output JSON file must be valid and functionally equivalent to the input.

## Realization steps

1. Accept the input & output files as command-line arguments.

2. Use N. Lohmann's JSON library to parse the input JSON file to indentify the strings.

3. Convert the strings to their respective Unicode escape sequences.

4. Apply object-oriented principles and write the implementation described in step 3 within the `StringEncoder` class.

5. Write the implementation described in step 2 within the `JsonEncoder` class.

6. Generate a replacement map (String -> Unicode Escape Sequence) in a format specified as a command-line argument (e.g. utf-32, utf-16, utf-8).

7. Ensure the Unicode encoded JSON object produces the same output as the input object.

## Used tools

[JSON for Modern C++](https://github.com/nlohmann/json)

[Unicode UTF Converter](https://www.coderstool.com/unicode-utf-tools)

## References

[Best Practice Object Oriented Programming](https://katrompas.accprofessors.com/best-practice-oop-programming)

[Mastering Unicode in Modern C++: A Comprehensive Guide to Wide Characters, Encodings, and Best Practices](https://www.linkedin.com/pulse/mastering-unicode-modern-c-comprehensive-guide-wide-characters-tariq/)
