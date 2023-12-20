#include "file_record.h"
#include <iomanip>

long FileRecord::write(std::fstream &outs) {
    outs.seekp(0, std::ios::end);
    long pos = outs.tellp();   
    outs.write(reinterpret_cast<const char*>(&_record[0][0]), sizeof(_record));
    if (!outs) {
        throw std::runtime_error("Failed to write to file");
    }
    return pos / sizeof(_record);
}

long FileRecord::read(std::fstream &ins, long recno) {
    long pos = recno * sizeof(_record);
    ins.seekg(pos);
    ins.read(reinterpret_cast<char*>(&_record[0][0]), sizeof(_record));

    _size = 0;
    for (; _record[_size][0] != '\0'; ++_size) { }
    return ins.gcount();
}

std::vector<std::string> FileRecord::get_record() const {
    std::vector<std::string> result;
    for (int i = 0; i < _size; ++i) {
        result.push_back(_record[i]);
    }
    return result;   
}

std::ostream& operator <<(std::ostream& outs, const FileRecord& r) {
    for (int i = 0; i < r._size ; ++i) {
        outs << std::setw(25) << r._record[i];
    }
    return outs;
}