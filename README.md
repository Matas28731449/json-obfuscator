# JSON Obfuscator

<img width="1640" alt="input-output-image" src="https://github.com/Matas28731449/json-obfuscator/assets/116190079/b2694962-366e-4637-8330-1e325c26df48">

## Goal

The goal is to write a simple JSON obfuscation tool that replaces the strings in a file with their respective Unicode escape sequences, making it more difficult for a human reader to analyze it. The output JSON file should be valid and functionally equivalent to the input.

## Compilation

The mandatory compilation line is due to the nlohmann/json library being used, which utilizes the C++11 version:

```
g++ -std=c++11 -o main main.cpp
```
