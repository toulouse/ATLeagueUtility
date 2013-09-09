#ifndef PARSE_H
#define PARSE_H

#include <map>
#include <vector>

using std::map;
using std::ifstream;
using std::ostream;
using std::string;
using std::unique_ptr;

class File {
private:
    friend ostream& operator<<(ostream&, const File&);
    string path;
    uint32_t dataOffset;
    uint32_t dataSize;


public:
    File(string path, uint32_t dataOffset, uint32_t dataSize) {
        this->path = path;
        this->dataOffset = dataOffset;
        this->dataSize = dataSize;
    }
};


class Archive {
public:
    map<string, File> files;
};

Archive openArchive(string filename);

#endif