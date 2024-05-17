#include "../include/json_encoder.hpp"

#include <fstream>

using std::ifstream;
using std::ofstream;

JsonEncoder::JsonEncoder(string inputFilename, string outputFilename, Encoding encodingType) {
    input = inputFilename;
    output = outputFilename;
    encoding = encodingType;
};

void JsonEncoder::encodeJson() {
    ifstream in(input);
    json data = json::parse(in);

    jsonToUnicode(data);

    ofstream out(output);
    out << StringEncoder::cleanUpJsonDump(data.dump(2)) << "\n";
}

void JsonEncoder::printEncodings(string path) {
    string str;

    if (encoding == UTF8) {
        str = "utf-8";
    } else if (encoding == UTF16) {
        str = "utf-16";
    } else if (encoding == UTF32) {
        str = "utf-32";
    }

    ofstream out(path);
    for (auto str : replacements) {
        out << str.first << " -> " << str.second << "\n";
    }
}

void JsonEncoder::jsonToUnicode(json &data) {
    if (data.is_object()) {
        json temp; // temporary json object

        for (auto it = data.begin(); it != data.end(); it ++) {
            auto &key = it.key();
            auto &value = it.value();

            jsonToUnicode(value);

            string utf16FormatKey = StringEncoder::stringToUnicode(Encoding::UTF16, key), // standard encoding for json obfuscation
                   optedFormatKey = StringEncoder::stringToUnicode(encoding, key); // opted encoding for replacements mapping
            
            replacements[key] = optedFormatKey;
            temp[utf16FormatKey] = move(value);
        }
        data = temp;

    } else if (data.is_array()) {
        for (auto &element : data) {
            jsonToUnicode(element);
        }

    } else if (data.is_string()) {
        string utf16FormatVal = StringEncoder::stringToUnicode(Encoding::UTF16, data.get<string>()),
               optedFormatVal = StringEncoder::stringToUnicode(encoding, data.get<string>());

        replacements[data.get<string>()] = optedFormatVal;
        data = utf16FormatVal;
    }
}
