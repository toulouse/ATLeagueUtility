#ifndef ARCHIVE_H
#define ARCHIVE_H

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
        class Archive {
        private:
            map<string, File> files;

        public:
            Archive();
            Archive(const map<string, File>& files);
            const map<string, File>& getFiles() const;
            void setFiles(const map<string, File>& files);

            /**
             * Factory method for Archive.
             */
            static unique_ptr<Archive> readArchive(ifstream &fs);
        };
    }
}

#endif
