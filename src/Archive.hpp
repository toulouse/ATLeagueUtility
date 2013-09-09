#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <map>

using std::map;
using std::string;

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
        };
    }
}

#endif
