#ifndef LIB_HPP
#define LIB_HPP

#include "utils.hpp"

string cleanup(string str) {
    string cleanedStr;
    cleanedStr.reserve(str.length());
    for (size_t i = 0; i < str.length(); i ++) {
        if (str[i] == '\\' && i + 1 < str.length() && str[i + 1] == '\\') {
            cleanedStr += '\\';
            i ++;
        } else {
            cleanedStr += str[i];
        }
    }
    
    return cleanedStr;
}

string stringToUnicode(Encoding encoding, string str) {
    stringstream ss;
    switch (encoding) {
        case UTF32: {
            wstring_convert<codecvt_utf8<char32_t>, char32_t> convert;
            u32string u32str = convert.from_bytes(str);
            for (char32_t c : u32str) {
                ss << "U+" << setfill('0') << setw(8) << hex << static_cast<int>(c);
            }
            break;
        }

        case UTF16: {
            wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> convert;
            u16string u16str = convert.from_bytes(str);
            for (char16_t c : u16str) {
                ss << "\\u" << setfill('0') << setw(4) << hex << static_cast<int>(c);
            }
            break;
        }

        case UTF8: {
            for (char c : str) {
                ss << "\\x" << setfill('0') << setw(2) << hex << static_cast<int>(static_cast<unsigned char>(c));
            }
            break;
        }
    }
    
    return ss.str();
}

void dataToUnicode(Encoding type, unordered_map<string, string> &map, json &data) {
    if (data.is_object()) {
        json encoded;

        for (auto it = data.begin(); it != data.end(); it++) {
            auto &key = it.key();
            auto &value = it.value();

            dataToUnicode(type, map, value); // recursive approach

            string defaultEncodedKey = stringToUnicode(UTF16, key), // default encoding
                   formatEncodedKey = stringToUnicode(type, key); // encoded by a specified format type provided as an argument
            map[key] = formatEncodedKey;
            
            encoded[defaultEncodedKey] = std::move(value);
        }
        data = encoded;

    } else if (data.is_array()) {
        for (auto &item : data) {
            dataToUnicode(type, map, item);
        }

    } else if (data.is_string()) {
        string defaultEncodedValue = stringToUnicode(UTF16, data.get<string>()),
               formatEncodedValue = stringToUnicode(type, data.get<string>());
        map[data.get<string>()] = formatEncodedValue;
        data = defaultEncodedValue;
    }
}

void createReplacementMap(Encoding encoding, unordered_map<string, string> map) {
    string str;

    if (encoding == UTF8) {
        str = "utf-8";
    } else if (encoding == UTF16) {
        str = "utf-16";
    } else if (encoding == UTF32) {
        str = "utf-32";
    }

    ofstream out("maps/replacement_map_" + str + ".txt");
    for (auto pair : map) {
        out << pair.first << " -> " << pair.second << "\n";
    }
}

#endif
