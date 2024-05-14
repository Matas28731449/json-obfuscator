# unicode-encoding

## Goal

The goal is to write a simple JSON obfuscation tool that replaces the strings in a file with their respective Unicode escape sequences, making it more difficult for a human reader to analyze it. The output JSON file should be valid and functionally equivalent to the input.

## Compilation

The mandatory compilation line is due to the nlohmann/json library being used, which utilizes the C++11 version:

```
g++ -std=c++11 -o main main.cpp
```
