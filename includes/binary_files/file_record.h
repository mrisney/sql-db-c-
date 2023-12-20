#ifndef FILE_RECORD_H
#define FILE_RECORD_H

#include "utilities.h"
using namespace std;

class FileRecord{
public:
    FileRecord(){
        _size = 0;
        _record[0][0] = '\0';
    }

    FileRecord(const vector<string>& v){
        _size = v.size();
        
        for (int i = 0; i < v.size(); ++i)
            strncpy(_record[i], v[i].c_str(), MAX);
        
        _record[_size][0] = '\0';
    }

    long write(fstream& outs);
    long read(fstream& ins, long recno);

    vector<string> get_record() const;

      // Returns the record
    vector<char *> get_records() { return _records; }

    friend ostream& operator <<(ostream& outs, const FileRecord& r);
    
    char _record[101][101];

      // The record vector
    vector<char *> _records;

private:
    static const int MAX = 100;
    int _size;
};

#endif //FILE_RECORD_H