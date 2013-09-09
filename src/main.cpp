#include <fstream>
#include <iostream>
#include <vector>
#include "parse.hpp"

using namespace std;

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        cerr << "Not enough arguments!" << endl;
        return -1;
    }

//    ifstream fs;
//    fs.open(argv[1], ios_base::in | ios_base::binary);
//
//    if (!fs.is_open()) {
//        cerr << "File couldn't be opened!" << endl;
//        return -2;
//    }

    openArchive(argv[1]);

    return 0;
}
