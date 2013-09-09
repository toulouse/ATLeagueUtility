#include "ArchiveMetadata.hpp"

#include <cassert>
#include <vector>

#include "File.hpp"

using std::ios_base;
using std::vector;

namespace AT {
    namespace RAF {
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


        ArchiveMetadata::ArchiveMetadata() {}
        ArchiveMetadata::ArchiveMetadata(const map<string, File>& files) : ArchiveMetadata::ArchiveMetadata() {
            this->files = files;
        }

        const map<string, File>& ArchiveMetadata::getFiles() const {
            return files;
        }

        void ArchiveMetadata::setFiles(const map<string, File>& files) {
            this->files = files;
        }

        unique_ptr<ArchiveMetadata> ArchiveMetadata::readArchiveMetadata(ifstream &fs) {
            if (!fs.is_open()) {
                throw "File couldn't be opened!";
            }
            fs.seekg(ios_base::beg);

            // --------------------
            // Read in archive file
            // --------------------
            // Archive Header
            ArchiveHeader archiveHeader;
            fs.read(reinterpret_cast<char *>(&archiveHeader), sizeof(ArchiveHeader));

            // File List
            FileList fileList;
            fs.seekg(archiveHeader.fileListOffset);

            uint32_t fileCount;
            fs.read(reinterpret_cast<char *>(&fileCount), sizeof(uint32_t));
            fileList.count = fileCount;

            // File Entries
            vector<FileEntry> files(fileCount);
            fs.read(reinterpret_cast<char *>(&files[0]), fileCount * sizeof(FileEntry));
            fileList.files = files;

            // Path List
            PathList pathList;
            fs.seekg(archiveHeader.pathListOffset);

            uint32_t pathBytes;
            fs.read(reinterpret_cast<char *>(&pathBytes), sizeof(uint32_t));
            pathList.bytes = pathBytes;

            uint32_t pathCount;
            fs.read(reinterpret_cast<char *>(&pathCount), sizeof(uint32_t));
            pathList.count = pathCount;

            // Path Entries
            vector<PathEntry> paths(pathCount);
            fs.read(reinterpret_cast<char *>(&paths[0]), pathCount * sizeof(PathEntry));
            pathList.paths = paths;

            // --------------------------
            // Build Archive model object
            // --------------------------
            unique_ptr<ArchiveMetadata> metadata(new ArchiveMetadata());
            map<string, File> fileMap;

            for (auto it = files.begin(); it < files.end(); it++) {
                PathEntry pathEntry = paths[it->pathListIndex];

                uint32_t adjustedPathOffset = archiveHeader.pathListOffset + pathEntry.offset;
                uint32_t pathLength = pathEntry.length;
                
                char *bytes = new char[pathLength];
                fs.seekg(adjustedPathOffset);
                fs.read(bytes, pathLength);
                string path = string(bytes, pathLength - 1);
                delete bytes;
                assert(File::calculatePathHash(path) == it->pathHash);
                fileMap.insert(make_pair(path, File(path, it->dataOffset, it->dataSize)));
            }
            
            metadata->setFiles(fileMap);
            return metadata;
        }

    }
}