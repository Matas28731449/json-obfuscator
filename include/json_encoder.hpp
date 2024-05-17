#ifndef JSON_OBFUSCATOR_H
#define JSON_OBFUSCATOR_H

#include "../json/single_include/nlohmann/json.hpp"
#include "string_encoder.hpp"

using json = nlohmann::ordered_json;
using std::unordered_map;

class JsonEncoder {
    public:
        JsonEncoder(string input, string output, Encoding encoding);

        void encodeJson();
        void printEncodings(string path);
    
    private:
        string   input,
                 output;
        Encoding encoding;
        unordered_map<string, string> replacements;

        void jsonToUnicode(json &data);
};

#endif
