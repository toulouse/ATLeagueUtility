#ifndef PARSE_H
#define PARSE_H

#include <fstream>
#include <map>

using std::ifstream;
using std::unique_ptr;

class Archive;
unique_ptr<Archive> readArchive(ifstream &fs);

#endif
