#include "Archive.hpp"

#include "File.hpp"

Archive::Archive() {}
Archive::Archive(const map<string, File>& files) : Archive::Archive() {
    this->files = files;
}

const map<string, File>& Archive::getFiles() const {
    return files;
}

void Archive::setFiles(const map<string, File>& files) {
    this->files = files;
}