#ifndef PARSE_H
#define PARSE_H

#include <map>
#include <vector>

using std::map;
using std::ifstream;
using std::ostream;
using std::string;
using std::unique_ptr;

class File {
private:
    friend ostream& operator<<(ostream&, const File&);
    string path;
    uint32_t dataOffset;
    uint32_t dataSize;

public:
    File() {}

    File(const string &path, uint32_t dataOffset, uint32_t dataSize) : File() {
        this->path = path;
        this->dataOffset = dataOffset;
        this->dataSize = dataSize;
    }

	uint32_t getDataOffset() const {
		return dataOffset;
	}

	void setDataOffset(uint32_t dataOffset) {
		this->dataOffset = dataOffset;
	}

	uint32_t getDataSize() const {
		return dataSize;
	}

	void setDataSize(uint32_t dataSize) {
		this->dataSize = dataSize;
	}

	const string& getPath() const {
		return path;
	}

	void setPath(const string& path) {
		this->path = path;
	}
};


class Archive {
private:
	map<string, File> files;

public:
    Archive() {}

	Archive(const map<string, File>& files) : Archive() {
		this->files = files;
	}

	const map<string, File>& getFiles() const {
		return files;
	}

	void setFiles(const map<string, File>& files) {
		this->files = files;
	}
};

unique_ptr<Archive> readArchive(ifstream &fs);

#endif
