#include "Archive.hpp"

#include <vector>

#include <boost/interprocess/streams/vectorstream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_stream.hpp>

#include "File.hpp"

using std::ios_base;
using std::vector;

using boost::interprocess::basic_vectorstream;
using boost::iostreams::array_source;
using boost::iostreams::copy;
using boost::iostreams::filtering_istream;
using boost::iostreams::zlib_decompressor;

namespace AT {
    namespace RAF {
        Archive::Archive(const string &archiveFilename) {
            file.open(archiveFilename, ios_base::in | ios_base::binary);
        };

        Archive::~Archive() {
            file.close();
        }

        vector<char> Archive::readFile(const File &f) {
            // Read in zlib-compressed file
            vector<char> rawContents(f.getDataSize());
            file.seekg(f.getDataOffset());
            file.read(&rawContents[0], f.getDataSize());

            // Set up zlib filter and point its source to the compressed vector
            filtering_istream is;
            is.push(zlib_decompressor());
            is.push(array_source(&rawContents[0], f.getDataSize()));

            // Copy the input stream to an output vector stream; return vector
            basic_vectorstream<vector<char>> vectorStream;
            copy(is, vectorStream);
            return vectorStream.vector();
        }
    }
}
