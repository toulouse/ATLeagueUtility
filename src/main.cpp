#include <iostream>
#include <fstream>
#include <boost/archive/binary_oarchive.hpp>

using namespace std;

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        cerr << "Not enough arguments!" << endl;
        return -1;
    }

    ifstream is;
    filebuf * fb = is.rdbuf();
    fb->open(argv[1], ios::in|ios::binary);

    if (!fb->is_open()) {
        cerr << "File couldn't be opened!" << endl;
        return -2;
    }

    return 0;
}
