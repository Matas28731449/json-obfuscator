#include "lib.hpp"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " 'input_file_name.json' 'output_file_name.json' 'unicode_format (e.g. utf-8)'\n";
        return 1;
    }

    Encoding encoding;

    if (argc > 3) { // if Unicode format is specified in an argument
        string args = argv[3]; // argument string
        if (args == "utf-32") {
            encoding = Encoding::UTF32;
        } else if (args == "utf-16") {
            encoding = Encoding::UTF16;
        } else if (args == "utf-8") {
            encoding = Encoding::UTF8;
        } else {
            cerr << "Specified format is unknown. Unicode formats: UTF-8, UTF-16, UTF-32\n";
            return 1;
        }
    } else { // if Unicode format is not specified
        encoding = UTF16; // since Unicode Escape Sequence and UTF-16 structured the same
    }

    // INPUT
    ifstream in(argv[1]);

    unordered_map<string, string> replacementMap;
    json data = json::parse(in);

    dataToUnicode(encoding, replacementMap, data);

    // OUTPUT
    ofstream out(argv[2]);
    string output = cleanup(data.dump(2));
    out << output << "\n";

    createReplacementMap(encoding, replacementMap);

    return 0;
}
