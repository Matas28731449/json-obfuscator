#include "lib.hpp"

int main(int argc, char **argv) {
    // INPUT
    ifstream in(argv[1]);

    json data = json::parse(in);
    obfuscate(data);

    // OUTPUT
    string output = data.dump(2);
    ofstream out(argv[2]);
    out <<  cleanup(output) << "\n";

    return 0;
}
