#include "../include/string_encoder.hpp"
#include <sstream>
#include <codecvt>
#include <iomanip>

using std::stringstream;
using std::wstring_convert;
using std::codecvt_utf8_utf16;
using std::codecvt_utf16;
using std::codecvt_utf8;
using std::u32string;
using std::u16string;
using std::setfill;
using std::setw;
using std::hex;

string StringEncoder::cleanUpJsonDump(string str) {
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

string StringEncoder::stringToUnicode(Encoding encoding, string str) {
    switch (encoding) {
        case Encoding::UTF32:
            return encodeToUtf32(str);
        case Encoding::UTF16:
            return encodeToUtf16(str);
        case Encoding::UTF8:
            return encodeToUtf8(str);
    }
}

string StringEncoder::encodeToUtf32(string str) {
    stringstream ss;
    wstring_convert<codecvt_utf8<char32_t>, char32_t> convert;
    u32string u32str = convert.from_bytes(str);
    for (char32_t c : u32str) {
        ss << "u+" << setfill('0') << setw(8) << hex << static_cast<int>(c);
    }
    return ss.str();
}

string StringEncoder::encodeToUtf16(string str) {
    stringstream ss;
    wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> convert;
    u16string u16str = convert.from_bytes(str);
    for (char16_t c : u16str) {
        ss << "\\u" << setfill('0') << setw(4) << hex << static_cast<int>(c);
    }
    return ss.str();
}

string StringEncoder::encodeToUtf8(string str) {
    stringstream ss;
    for (char c : str) {
        ss << "\\x" << setfill('0') << setw(2) << hex << static_cast<int>(static_cast<unsigned char>(c));
    }
    return ss.str();
}
