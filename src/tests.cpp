#include <gtest/gtest.h>
#include "string_encoder.cpp"

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
    string value = "\\\\x74\\\\x65\\\\x73\\\\x74\\\\x5f\\\\x76\\\\x61\\\\x6c\\\\x75\\\\x65\\\\x5f\\\\x34"; // test_value_4
    string expected = "\\x74\\x65\\x73\\x74\\x5f\\x76\\x61\\x6c\\x75\\x65\\x5f\\x34"; // test_value_4
    string actual = StringEncoder::cleanUpJsonDump(value);

    EXPECT_EQ(actual, expected);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
