#include <fstream>
#include <iostream>
#include <vector>

#include "Archive.hpp"
#include "ArchiveMetadata.hpp"
#include "File.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios_base;
using std::string;

using AT::RAF::Archive;
using AT::RAF::ArchiveMetadata;

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        cerr << "Not enough arguments!" << endl;
        return -1;
    }

    const string metadata = string(argv[1]);
    const string archiveFilename = metadata + ".dat";

    ifstream fs;
    fs.open(metadata, ios_base::in | ios_base::binary);
    if (!fs.is_open()) {
        cerr << "File couldn't be opened!" << endl;
        return -2;
    }

    auto archiveMetadata = ArchiveMetadata::readArchiveMetadata(fs);
    auto archive = new Archive(archiveFilename); // without the 'new' this is an error
    auto files = archiveMetadata->getFiles();
    for (auto it = files.begin(); it != files.end(); it++) {
        cout << "File: " << it->first << " Debug info: " << it->second << endl;
        auto file = archive->readFile(it->second);
        // Do something with contents later
    }
    delete archive;

    return 0;
}
