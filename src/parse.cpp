#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "parse.hpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::ios_base;
using std::ostream;
using std::unique_ptr;
using std::vector;

ostream& operator<<(ostream &stream, const ArchivedFile &file) {
    return stream << "File(path=" << file.path + ", dataOffset=" <<  file.dataOffset << ", dataSize=" <<  file.dataSize << ")";
}

struct PathEntry {
    uint32_t offset;
    uint32_t length;
};

struct PathList {
    uint32_t bytes;
    uint32_t count;
    vector<PathEntry> paths;
};

struct FileEntry {
    uint32_t pathHash;
    uint32_t dataOffset;
    uint32_t dataSize;
    uint32_t pathListIndex;
};

struct FileList {
    uint32_t count;
    vector<FileEntry> files;
};

struct ArchiveHeader {
    uint32_t magicNumber;
    uint32_t version;
    uint32_t managerIndex;
    uint32_t fileListOffset;
    uint32_t pathListOffset;
};

uint32_t calculatePathHash(string path) {
    uint32_t hash = 0;
    uint32_t temp = 0;
    for (auto it = path.begin(); it < path.end(); it++) {
        hash = (hash << 4) + tolower(*it);
        temp = hash & 0xf0000000;
        if (temp) {
            hash = hash ^ (temp >> 24);
            hash = hash ^ temp;
        }
    }
    return hash;
}

Archive openArchive(string filename) {
    ifstream fs;
    fs.open(filename, ios_base::in | ios_base::binary);

    if (!fs.is_open()) {
        throw "File couldn't be opened!";
    }

    // --------------------
    // Read in archive file
    // --------------------

    // Archive Header
    ArchiveHeader *archiveHeader = new ArchiveHeader;
    fs.read((char *)archiveHeader, sizeof(ArchiveHeader));

    // File List
    FileList *fileList = new FileList;
    fs.seekg(archiveHeader->fileListOffset);

    uint32_t fileCount;
    fs.read((char *)&fileCount, sizeof(uint32_t));
    fileList->count = fileCount;

    // File Entries
    vector<FileEntry> files(fileCount);
    fs.read((char *)&files[0], fileCount * sizeof(FileEntry));
    fileList->files = files;

    // Path List
    PathList *pathList = new PathList;
    fs.seekg(archiveHeader->pathListOffset);

    uint32_t pathBytes;
    fs.read((char *)&pathBytes, sizeof(uint32_t));
    pathList->bytes = pathBytes;

    uint32_t pathCount;
    fs.read((char *)&pathCount, sizeof(uint32_t));
    pathList->count = pathCount;

    // Path Entries
    vector<PathEntry> paths(pathCount);
    fs.read((char *)&paths[0], pathCount * sizeof(PathEntry));
    pathList->paths = paths;

    // --------------------------
    // Build Archive model object
    // --------------------------
    Archive archive;
    map<string, ArchivedFile> fileMap;

    for (auto it = files.begin(); it < files.end(); it++) {
        PathEntry pathEntry = paths[it->pathListIndex];

        uint32_t adjustedPathOffset = archiveHeader->pathListOffset + pathEntry.offset;
        uint32_t pathLength = pathEntry.length;

        char *bytes = new char[pathLength];
        fs.seekg(adjustedPathOffset);
        fs.read(bytes, pathLength);
        string path = string(bytes, pathLength - 1);
        fileMap.insert(make_pair(path, ArchivedFile(path, it->dataOffset, it->dataSize)));
    }

    for (auto it = fileMap.begin(); it != fileMap.end(); it++) {
        cout << "File: " << it->first << " Debug info: " << it->second << endl;
    }

    return archive;
}