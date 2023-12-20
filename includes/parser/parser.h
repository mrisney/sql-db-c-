#ifndef PARSER_H
#define PARSER_H

#include "../table/typedefs.h"

using namespace std;

class Parser{

public:

    Parser();
    Parser(char str[]);

    void set_string(char str[]);
    void make_table();
    void build_keyword_list();
    long get_column(const string& token);
    bool get_parse_tree();
    mmap_ss parse_tree() const { return _ptree; }
    bool fail() const { return !_flag; }
    void print_parse_tree() const;

private:

    char _buffer[MAX_BUFFER];
    static int _table[MAX_ROWS][MAX_COLUMNS];

    void initialize(); // Private method for internal initialization

    vectorstr _inputq;
    map_sl _keywords;
    mmap_ss _ptree;
    bool _flag;
    
    enum keys { MAKE = 1, TABLE, INSERT, INTO, SELECT, FIELDS, VALUES, FROM, STAR, WHERE, SYMBOL };

};

#endif //PARSER_H