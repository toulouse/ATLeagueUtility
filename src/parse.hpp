#ifndef PARSE_H
#define PARSE_H

#include <map>
#include <vector>

using std::map;
using std::ifstream;
using std::ostream;
using std::string;
using std::unique_ptr;

class ArchivedFile {
private:
    friend ostream& operator<<(ostream&, const ArchivedFile&);
    string path;
    uint32_t dataOffset;
    uint32_t dataSize;


public:
    ArchivedFile(string path, uint32_t dataOffset, uint32_t dataSize) {
        this->path = path;
        this->dataOffset = dataOffset;
        this->dataSize = dataSize;
    }
};


class Archive {
    map<string, ArchivedFile> files;
};

Archive openArchive(string filename);

#endif