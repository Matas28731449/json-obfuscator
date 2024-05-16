#ifndef UTILS_HPP
#define UTILS_HPP

#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <codecvt>
#include <locale>

using json = nlohmann::ordered_json;
using std::unordered_map;
using std::stringstream;
using std::string;
using std::cerr;
using std::hex;
using std::setw;
using std::move;
using std::setfill;
using std::ifstream;
using std::ofstream;
using std::wstring_convert;
using std::codecvt_utf8;
using std::codecvt_utf16;
using std::codecvt_utf8_utf16;
using std::u16string;
using std::u32string;

enum Encoding {
    UTF32,
    UTF16,
    UTF8
};

string cleanup(string str);
string stringToUnicode(Encoding encoding, string str);
void dataToUnicode(Encoding encoding, unordered_map<string, string> &map, json &data);
void createReplacementMap(Encoding encoding, unordered_map<string, string> map);

#endif