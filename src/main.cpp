#include <fstream>
#include <iostream>
#include <vector>

#include "Archive.hpp"
#include "File.hpp"

using std::ifstream;
using std::cerr;
using std::cout;
using std::endl;
using std::ios_base;

using AT::RAF::Archive;

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

    auto archive = Archive::readArchive(fs);
    auto files = archive->getFiles();
    for (auto it = files.begin(); it != files.end(); it++) {
        cout << "File: " << it->first << " Debug info: " << it->second << endl;
    }

    return 0;
}
