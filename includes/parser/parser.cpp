#include "parser.h"

using namespace std;

int Parser::_table[MAX_ROWS][MAX_COLUMNS];

void Parser::initialize() {
    make_table();
    build_keyword_list();
}

Parser::Parser() {
    initialize();
    char str[] = "";
    set_string(str);
}

Parser::Parser(char str[]){
    initialize();
    set_string(str);
}

void Parser::set_string(char str[]){
    
    _inputq.clear();
    strcpy(_buffer, str);
    STokenizer stk(_buffer);
    TokenS t;
    stk >> t;

    while (stk.more()){

        string token = t.token_str(); // Use the token_str method

        // Convert token to lowercase
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);


        string type = t.type_string();
        
        if (t.type() >= TOKEN_ALPHA && t.type() <= TOKEN_PUNC)
            _inputq += t.token_str();

        else if (t.type() == TOKEN_SPECIAL){
            string temp = t.token_str();
            temp.erase(0, 1);
            temp.erase(temp.size()-1, 1);
            _inputq += temp;
        }
        t = TokenS();
        stk >> t;
    }
    _flag = get_parse_tree();
}

void Parser::make_table(){
    init_table(_table);

    mark_cell(0, _table, MAKE, 1);
    mark_cell(1, _table, TABLE, 2);
    mark_cell(0, _table, INSERT, 1);
    mark_cell(1, _table, INTO, 2);
    mark_cell(0, _table, SELECT, 3);

    mark_cell(2, _table, SYMBOL, 4);
    mark_cell(4, _table, FIELDS, 5);
    mark_cell(4, _table, VALUES, 7);
    mark_cell(5, _table, SYMBOL, 6);
    mark_cell(6, _table, SYMBOL, 6);
    mark_cell(7, _table, SYMBOL, 8);
    mark_cell(8, _table, SYMBOL, 8);

    mark_cell(3, _table, STAR, 9);    
    mark_cell(3, _table, SYMBOL, 12);  
    mark_cell(12, _table, SYMBOL, 12);
    mark_cell(9, _table, FROM, 10);
    mark_cell(12, _table, FROM, 10);
    mark_cell(10, _table, SYMBOL, 11);
    
    mark_cell(11, _table, WHERE, 13);
    mark_cell(13, _table, SYMBOL, 14);
    mark_cell(14, _table, SYMBOL, 14);
    
    for (int i = 0; i <= 14; ++i){
        if (i == 6 || i == 8 || i == 11 || i == 14 || i == 23)
            mark_success(_table, i);
        else
            mark_fail(_table, i);
    }
}

void Parser::build_keyword_list() {
   vectorstr keywords = {"make", "table", "insert", "into", "select", "fields", "values", "from", "*", "where"};
    for (const auto& keyword : keywords) {
        _keywords[keyword] = _keywords.size() + 1;
    }
}

long Parser::get_column(const string& token){
    if (_keywords.contains(token))
        return _keywords[token];
    return SYMBOL;
}   

bool Parser::get_parse_tree(){
    _ptree.clear();
    int state = 0;
    
    for (int i = 0; i < _inputq.size() && state != -1; ++i){
        string token = _inputq[i];
        state = _table[state][get_column(token)];

        switch (state){
            case 1:
            case 3:
                _ptree["command"] += token;
                break;

            case 4:
            case 11:
                _ptree["table_name"] += token;
                break;

            case 6:
                _ptree["col"] += token;
                break;

            case 9:
            case 12:
                _ptree["fields"] += token;
                break;

            case 8:
                _ptree["values"] += token;
                break;

            case 13: {
                string temp = "yes";
                _ptree["where"] += temp;
                break;
            }

            case 14: 
                _ptree["condition"] += token;
                break;

            default:
                break;
        }
    }
    return is_success(_table, state);
}

void Parser::print_parse_tree() const {
    // Cast away constness to use non-const begin() and end() methods
    auto& non_const_ptree = const_cast<MMap<std::string, std::string>&>(_ptree);

    for (auto it = non_const_ptree.begin(); it != non_const_ptree.end(); ++it) {
        const auto& pair = *it;
        std::cout << pair.key << ": [";

        for (size_t i = 0; i < pair.value_list.size(); ++i) {
            std::cout << pair.value_list[i];
            if (i < pair.value_list.size() - 1) {
                std::cout << ", ";
            }
        }

        std::cout << "]" << std::endl;
    }
}


