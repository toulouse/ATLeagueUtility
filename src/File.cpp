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

        ostream& operator<<(ostream &stream, const File &file) {
            return stream << "File(path=" << file.path + ", dataOffset=" <<  file.dataOffset << ", dataSize=" <<  file.dataSize << ")";
        }
    }
}