#ifndef PARSE_H
#define PARSE_H

#include <map>
#include <vector>

using namespace std;

class File {
    string path;
    uint32_t dataOffset;
    uint32_t dataSize;
};

class Archive {
    map<string, File> files;
};

Archive openArchive(string filename);

#endif