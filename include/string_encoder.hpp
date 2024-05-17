#ifndef UNICODE_ENCODER_HPP
#define UNICODE_ENCODER_HPP

#include <string>

using std::string;

enum Encoding {
    UTF32,
    UTF16,
    UTF8
};

class StringEncoder {
    public:
        static string stringToUnicode(Encoding encoding, string str);
        static string cleanUpJsonDump(string str);

    private:
        static string encodeToUtf32(string str);
        static string encodeToUtf16(string str);
        static string encodeToUtf8(string str);
};

#endif
