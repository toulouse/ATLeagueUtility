#include "Archive.hpp"

#include "File.hpp"

namespace AT {
    namespace RAF {
        Archive::Archive() {}
        Archive::Archive(const map<string, File>& files) : Archive::Archive() {
            this->files = files;
        }

        const map<string, File>& AT::RAF::Archive::getFiles() const {
            return files;
        }

        void AT::RAF::Archive::setFiles(const map<string, File>& files) {
            this->files = files;
        }
    }
}