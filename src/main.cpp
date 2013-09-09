#include <fstream>
#include <iostream>
#include <vector>
#include "parse.hpp"

using std::ifstream;
using std::cerr;
using std::cout;
using std::endl;
using std::ios_base;

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        cerr << "Not enough arguments!" << endl;
        return -1;
    }

    ifstream fs;
    fs.open(argv[1], ios_base::in | ios_base::binary);
    if (!fs.is_open()) {
        cerr << "File couldn't be opened!" << endl;
        return -2;
    }

    auto archive = readArchive(fs);
    for (auto it = archive.files.begin(); it != archive.files.end(); it++) {
        cout << "File: " << it->first << " Debug info: " << it->second << endl;
    }

    return 0;
}
