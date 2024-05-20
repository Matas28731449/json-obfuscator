#include "../include/json_encoder.hpp"

#include <fstream>

using std::ifstream;
using std::ofstream;

JsonEncoder::JsonEncoder(string _input, string _output, Encoding _encoding) : input(_input), output(_output), encoding(_encoding) { }

void JsonEncoder::encodeJson() {
    ifstream in(input);
    json data = json::parse(in);

    jsonToUnicode(data);

    ofstream out(output);
    out << StringEncoder::cleanUpJsonDump(data.dump(2)) << "\n";
}

void JsonEncoder::printEncodings(string path) {
    string encodingStr;

    if (encoding == UTF8) {
        encodingStr = "utf-8";
    } else if (encoding == UTF16) {
        encodingStr = "utf-16";
    } else if (encoding == UTF32) {
        encodingStr = "utf-32";
    }

    ofstream out(path + "replacement_map_" + encodingStr + ".txt");
    for (auto str : replacements) {
        out << str.first << " -> " << str.second << "\n";
    }
    out.close();
}

void JsonEncoder::jsonToUnicode(json &data) {
    if (data.is_object()) {
        json temp; // temporary json object

        for (auto it = data.begin(); it != data.end(); it ++) {
            auto &key = it.key();
            auto &value = it.value();

            jsonToUnicode(value);

            string utf16FormatKey = StringEncoder::stringToUnicode(Encoding::UTF16, key); // standard encoding for json file obfuscation
            string optedFormatKey = StringEncoder::stringToUnicode(encoding, key); // opted encoding for replacements mapping
            
            replacements[key] = optedFormatKey;
            temp[utf16FormatKey] = std::move(value);
        }
        data = temp;

    } else if (data.is_array()) {
        for (auto &element : data) {
            jsonToUnicode(element);
        }

    } else if (data.is_string()) {
        string utf16FormatVal = StringEncoder::stringToUnicode(Encoding::UTF16, data.get<string>());
        string optedFormatVal = StringEncoder::stringToUnicode(encoding, data.get<string>());

        replacements[data.get<string>()] = optedFormatVal;
        data = utf16FormatVal;
    }
}
