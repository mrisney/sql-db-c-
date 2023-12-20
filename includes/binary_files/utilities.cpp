#include "utilities.h"
using namespace std;


bool file_exists(const std::string& filename) {
    std::fstream f;
    f.open(filename, std::fstream::in | std::fstream::binary);
    return f.is_open();
}

void open_fileRW(std::fstream& f, const std::string& filename) {
    f.open(filename, std::fstream::in | std::fstream::out | std::fstream::binary);

    if (!f.is_open()) {
        // File does not exist, try creating it
        f.clear(); // Clear any error flags
        f.open(filename, std::fstream::out | std::fstream::binary);
        f.close(); // Close the file after creation

        // Now try opening it again with read/write mode
        f.open(filename, std::fstream::in | std::fstream::out | std::fstream::binary);
        if (!f.is_open()) {
            throw std::runtime_error("Failed to create and open file: " + filename);
        }
    }
}

void open_fileW(std::fstream& f, const std::string& filename) {
    f.open(filename, std::fstream::out | std::fstream::binary);

    if (!f.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }
}


bool file_exists(const char filename[]){
    const bool debug = false;
    fstream f;
    f.open(filename, std::fstream::in | std::fstream::binary);

    if (f.fail()){
        if (debug) cout << "file_exists(): file does not exist: " << filename << endl;
        return false;
    }

    if (debug) cout << "file_exists(): file does exist: " << filename << endl;
    f.close();
    return true;
}

void open_fileRW(fstream& f, const char filename[]){
    const bool debug = false;
    
    if (!file_exists(filename)){
        f.open(filename, std::fstream::out | std::fstream::binary);

        if (f.fail()){
            if (debug) cout << "open_fileRW failed: " << filename << endl;
            throw std::runtime_error("File failed to create: " + std::string(filename));

        }

        else {
            if (debug) cout << "open_fileRW: file created: " << filename << endl;
        }
    }

    else {
        f.open(filename, std::fstream::in | std::fstream::out | std::fstream::binary);

        if (f.fail()){
            if (debug) cout << "open_fileRW failed: " << filename << endl;
            throw std::runtime_error("File failed to open: " + std::string(filename));

        }
    }
}

void open_fileW(fstream& f, const char filename[]){
    const bool debug = false;   
    f.open(filename, std::fstream::out | std::fstream::binary);

    if (f.fail()){
        if (debug) cout << "open_fileW failed: " << filename << endl;
        throw std::runtime_error("File failed to open: " + std::string(filename));

    }
}