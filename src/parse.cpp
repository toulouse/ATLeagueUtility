#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "parse.hpp"

using namespace std;

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

uint32_t calculateHashFromString(string s) {
    uint32_t hash = 0;
    uint32_t temp = 0;
    for (string::iterator it = s.begin(); it < s.end(); it++) {
        hash = (hash << 4) + tolower(*it);
        temp = hash & 0xf0000000;
        if (!temp) {
            hash ^= (temp >> 24);
            hash ^= temp;
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

    Archive archive;

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

    // Path Strings
    map<uint32_t, PathEntry *> pathHashToPathMap;
    map<PathEntry *, string> pathToPathStringMap;

    for (vector<PathEntry>::iterator it = paths.begin(); it < paths.end(); it++) {
        uint32_t adjustedPathOffset = archiveHeader->pathListOffset + it->offset;
        uint32_t pathLength = it->length;

        char *bytes = new char[pathLength];
        fs.seekg(adjustedPathOffset);
        fs.read(bytes, pathLength);
        string path = string(bytes, pathLength);

        uint32_t pathHash = calculateHashFromString(path);

        cout << "ph " << pathHash << " p " << path << endl;
        PathEntry *pathEntry = it.base();
        pathHashToPathMap.insert(make_pair(pathHash, pathEntry));
        pathToPathStringMap.insert(make_pair(pathEntry, path));
    }

    for (vector<FileEntry>::iterator it = files.begin(); it < files.end(); it++) {
        auto pathHashIt = pathHashToPathMap.find(it->pathHash);
        if (pathHashIt == pathHashToPathMap.end()) {
            cerr << "Could not find path entry with index=" << it->pathListIndex << " hash=" << it->pathHash << endl;
            continue;
        }

        PathEntry *pathEntry = pathHashIt->second;
        auto pathIt = pathToPathStringMap.find(pathEntry);
        if (pathIt == pathToPathStringMap.end()) {
            cerr << "Could not find file with offset=" << pathEntry->offset << ", length=" << pathEntry->length << endl;
            continue;
        }

        string path = pathIt->second;
        cerr << path << ": offset=" << pathEntry->offset << ", length=" << pathEntry->length << endl;
    }

    return archive;
}