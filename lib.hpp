#ifndef LIB_HPP
#define LIB_HPP

#include "utils.hpp"

string cleanup(string str);
string string_to_unicode(string str);
void obfuscate(json &data);

string cleanup(string str) {
    string result;
    result.reserve(str.length());
    for (size_t i = 0; i < str.length(); i ++) {
        if (str[i] == '\\' && i + 1 < str.length() && str[i + 1] == '\\') {
            result += '\\';
            i ++;
        } else {
            result += str[i];
        }
    }
    
    return result;
}

string string_to_unicode(string str) {
    stringstream ss;
    for (char c : str) {
        ss << "\\u" << setfill('0') << setw(4) << hex << static_cast<int>(c);
    }
    return ss.str();
}

void obfuscate(json &data) {
    if (data.is_object()) {
        json obfuscated;

        for (auto it = data.begin(); it != data.end(); it ++) {
            auto &key = it.key();
            auto &value = it.value();

            json obfuscated_key = string_to_unicode(key);
            obfuscate(value);
            obfuscated.emplace(obfuscated_key.get<string>(), move(value));
        }
        data = obfuscated;

    } else if (data.is_array()) {
        for (auto &item : data) {
            obfuscate(item);
        }

    } else if (data.is_string()) {
        data = string_to_unicode(data.get<string>());
    }
}

#endif
