#include "string_encoder.cpp"
#include "json_encoder.cpp"
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;

TEST(string_encoder, encodeToUtf32Check) {
    string value = "test_value_1";
    string expected = "u+00000074u+00000065u+00000073u+00000074u+0000005fu+00000076u+00000061u+0000006cu+00000075u+00000065u+0000005fu+00000031";
    string actual = StringEncoder::stringToUnicode(Encoding::UTF32, value);

    EXPECT_EQ(actual, expected);
}

TEST(string_encoder, encodeToUtf16Check) {
    string value = "test_value_2";
    string expected = "\\u0074\\u0065\\u0073\\u0074\\u005f\\u0076\\u0061\\u006c\\u0075\\u0065\\u005f\\u0032";
    string actual = StringEncoder::stringToUnicode(Encoding::UTF16, value);

    EXPECT_EQ(actual, expected);
}

TEST(string_encoder, encodeToUtf8Check) {
    string value = "test_value_3";
    string expected = "\\x74\\x65\\x73\\x74\\x5f\\x76\\x61\\x6c\\x75\\x65\\x5f\\x33";
    string actual = StringEncoder::stringToUnicode(Encoding::UTF8, value);

    EXPECT_EQ(actual, expected);
}

TEST(string_encoder, cleanUpJsonDumpCheck) {
    string value = R"(\\x74\\x65\\x73\\x74\\x5f\\x76\\x61\\x6c\\x75\\x65\\x5f\\x34)"; // test_value_4
    string expected = "\\x74\\x65\\x73\\x74\\x5f\\x76\\x61\\x6c\\x75\\x65\\x5f\\x34";
    string actual = StringEncoder::cleanUpJsonDump(value);

    EXPECT_EQ(actual, expected);
}

TEST(json_encoder, encodeJsonCheck) {
    string input = "input.json";
    string output = "output.json";

    ofstream out(input);
    out << R"({
        "test5": "value5",
        "test6": "value6"
    })";
    out.close();

    JsonEncoder obfuscator(input, output, Encoding::UTF16);
    obfuscator.encodeJson();

    ifstream in(output);
    stringstream ss;
    ss << in.rdbuf();

    json actual = json::parse(ss.str());
    json expected = json::parse(R"({
        "\u0074\u0065\u0073\u0074\u0035": "\u0076\u0061\u006c\u0075\u0065\u0035",
        "\u0074\u0065\u0073\u0074\u0036": "\u0076\u0061\u006c\u0075\u0065\u0036"
    })");

    EXPECT_EQ(actual, expected);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
