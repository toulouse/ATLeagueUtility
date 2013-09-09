#ifndef PARSE_H
#define PARSE_H

#include <fstream>
#include <memory>

using std::ifstream;
using std::unique_ptr;

class Archive;
// TODO: move this into a factory class or something
unique_ptr<Archive> readArchive(ifstream &fs) __attribute__ ((deprecated));

#endif
