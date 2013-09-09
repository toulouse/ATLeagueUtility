#ifndef PARSE_H
#define PARSE_H

#include <fstream>
#include <map>

using std::ifstream;
using std::unique_ptr;

namespace AT {
    namespace RAF {
        class Archive;
        // TODO: move this into a factory class or something
        unique_ptr<Archive> readArchive(ifstream &fs) __attribute__ ((deprecated));
    }
}

#endif
