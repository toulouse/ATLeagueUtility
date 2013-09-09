#include "File.hpp"

namespace AT {
    namespace RAF {
        File::File() {}
        File::File(const string &path, uint32_t dataOffset, uint32_t dataSize) : File::File() {
            this->path = path;
            this->dataOffset = dataOffset;
            this->dataSize = dataSize;
        }

        uint32_t File::getDataOffset() const {
            return dataOffset;
        }

        void File::setDataOffset(uint32_t dataOffset) {
            this->dataOffset = dataOffset;
        }

        uint32_t File::getDataSize() const {
            return dataSize;
        }

        void File::setDataSize(uint32_t dataSize) {
            this->dataSize = dataSize;
        }

        const string& File::getPath() const {
            return path;
        }

        void File::setPath(const string& path) {
            this->path = path;
        }

        /* static */ uint32_t File::calculatePathHash(const string &path) {
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

        ostream& operator<<(ostream &stream, const File &file) {
            return stream << "File(path=" << file.path + ", dataOffset=" <<  file.dataOffset << ", dataSize=" <<  file.dataSize << ")";
        }
    }
}