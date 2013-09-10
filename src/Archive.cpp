#include "Archive.hpp"

#include "File.hpp"

using std::ios_base;

namespace AT {
    namespace RAF {
        Archive::Archive(const string &archiveFilename) {
            file.open(archiveFilename, ios_base::in | ios_base::binary);
        };

        Archive::~Archive() {
            file.close();
        }

        vector<char> Archive::readFile(const File &f) {
            vector<char> result(f.getDataSize());
            file.seekg(f.getDataOffset());
            file.read(&result[0], f.getDataSize());
            return result;
        }
    }
}
