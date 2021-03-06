#ifndef FILE_H
#define FILE_H

#include <cstdint>
#include <ostream>
#include <string>

namespace AT {
    namespace RAF {
        using std::ostream;
        using std::string;

        class File {
        private:
            friend ostream& operator<<(ostream&, const File&);
            string path;
            uint32_t dataOffset;
            uint32_t dataSize;

        public:
            File();
            File(const string &path, uint32_t dataOffset, uint32_t dataSize);

            uint32_t getDataOffset() const;
            void setDataOffset(uint32_t dataOffset);
            uint32_t getDataSize() const;
            void setDataSize(uint32_t dataSize);
            const string& getPath() const;
            void setPath(const string& path);

            static uint32_t calculatePathHash(const string &path);
        };
    }
}
#endif
