#ifndef ARCHIVEMETADATA_H
#define ARCHIVEMETADATA_H

#include <fstream>
#include <map>
#include <memory>

using std::map;
using std::string;
using std::ifstream;
using std::unique_ptr;

namespace AT {
    namespace RAF {
        class File;
        class ArchiveMetadata {
        private:
            map<string, File> files;

        public:
            ArchiveMetadata();
            ArchiveMetadata(const map<string, File>& files);
            const map<string, File>& getFiles() const;
            void setFiles(const map<string, File>& files);

            /**
             * Factory method for ArchiveMetadata.
             */
            static unique_ptr<ArchiveMetadata> readArchiveMetadata(ifstream &fs);
        };
    }
}

#endif
