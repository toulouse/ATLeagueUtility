#include <iostream>
#include <fstream>
#include <vector>
#include <boost/archive/binary_oarchive.hpp>

using namespace std;

class PathEntry {
public:
    uint32_t offset;
    uint32_t length;
};

class PathList {
public:
    uint32_t bytes;
    uint32_t count;
    vector<PathEntry> paths;
};

class FileEntry {
public:
    uint32_t pathHash;
    uint32_t dataOffset;
    uint32_t dataSize;
    uint32_t pathListIndex;
};

class FileList {
public:
    uint32_t count;
    vector<FileEntry> files;
};

class ArchiveFile {
public:
    uint32_t magicNumber;
    uint32_t version;
    uint32_t managerIndex;
    uint32_t fileListOffset;
    uint32_t pathListOffset;
};

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        cerr << "Not enough arguments!" << endl;
        return -1;
    }

    ifstream is;
    filebuf * fb = is.rdbuf();
    fb->open(argv[1], ios::in|ios::binary);

    if (!fb->is_open()) {
        cerr << "File couldn't be opened!" << endl;
        return -2;
    }

    return 0;
}
