#include "../include/json_encoder.hpp"
#include <iostream>

using std::cerr;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " [input_filename.json] [output_filename.json] [unicode_format (e.g. utf-8)]\n";
        return 1;
    }

    Encoding encoding = Encoding::UTF16; // default unicode escape sequence format

    if (argc > 3) {
        string encodingArg = argv[3];
        if (encodingArg == "utf-32") {
            encoding = Encoding::UTF32;
        } else if (encodingArg == "utf-16") {
            encoding = Encoding::UTF16;
        } else if (encodingArg == "utf-8") {
            encoding = Encoding::UTF8;
        } else {
            cerr << "Unknown encoding format. Supported formats: UTF-8, UTF-16, UTF-32\n";
            return 1;
        }
    }

    JsonEncoder obfuscator(argv[1], argv[2], encoding);
    obfuscator.encodeJson();
    obfuscator.printEncodings("maps/");

    return 0;
}
