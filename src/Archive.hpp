#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::string;
using std::vector;

namespace AT {
    namespace RAF {
        class File;
        class Archive {
        private:
            ifstream file;
        public:
            Archive(Archive&&) = default; // Explicit move constructor
            Archive(const string &archiveFilename);
            ~Archive();
            vector<char> readFile(const File &f);
        };
    }
}

#endif
