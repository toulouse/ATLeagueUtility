#include <boost/shared_ptr.hpp>
#include <vector>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>


using namespace std;
using boost::iostreams::mapped_file_source;
using boost::iostreams::stream;

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

    stream<mapped_file_source> fs;
    fs.open(mapped_file_source((argv[1])));

    if (!fs.is_open()) {
        cerr << "File couldn't be opened!" << endl;
        return -2;
    }

    // Read Archive File
    ArchiveFile *archiveFile = new ArchiveFile;
    fs.read((char *)archiveFile, sizeof(ArchiveFile));

    // Read File List
    FileList *fileList = new FileList;
    fs.seekg(archiveFile->fileListOffset);

    uint32_t fileCount;
    fs.read((char *)&fileCount, sizeof(uint32_t));
    fileList->count = fileCount;

    // Read File Entries
    vector<FileEntry> files(fileCount);
    fs.read((char *)&files[0], fileCount * sizeof(FileEntry));
    fileList->files = files;

    // Read Path List
    PathList *pathList = new PathList;
    fs.seekg(archiveFile->pathListOffset);

    uint32_t pathBytes;
    fs.read((char *)&pathBytes, sizeof(uint32_t));
    pathList->bytes = pathBytes;

    uint32_t pathCount;
    fs.read((char *)&pathCount, sizeof(uint32_t));
    pathList->count = pathCount;

    // Read Path Entries
    vector<PathEntry> paths(pathCount);
    fs.read((char *)&paths[0], pathCount * sizeof(PathEntry));
    pathList->paths = paths;

    // Read Path Strings
    vector<string> pathStrings(pathCount);
    vector<PathEntry>::iterator pathIter;
    vector<string>::iterator pathStringIter;
    for (pathIter = paths.begin(), pathStringIter = pathStrings.begin(); pathIter < paths.end() && pathStringIter < pathStrings.end(); ++pathIter, ++pathStringIter) {
        uint32_t adjustedPathOffset = archiveFile->pathListOffset + pathIter->offset;
        uint32_t pathLength = pathIter->length;

        char *bytes = new char[pathLength];
        fs.seekg(adjustedPathOffset);
        fs.read(bytes, pathLength);
        *pathStringIter = string(bytes, pathLength);
        cout << *pathStringIter << endl;
    }



    return 0;
}
