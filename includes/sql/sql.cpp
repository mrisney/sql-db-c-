#include <iostream>
#include <filesystem>
#include "sql.h"

//namespace fs = std::__fs::filesystem;

using namespace std;


Table SQL::command(const string& command){
    char cmd[300];
    strcpy(cmd, command.c_str());
    Parser parser(cmd);
    mmap_ss ptree = parser.parse_tree(); 

    if (!parser.fail())
        return get_sql_command(ptree, cmd);

    else {
        cout << "BAD COMMAND : '" << command <<"', CHECK SYNTAX" << endl;
        _table = Table();
        return _table;
    }
}

void SQL::run(){    
    string str = "";
    int i = 0;
    cout << "\n>run:\n\n";

    do {
        cout << "Please enter the command: " << endl;
        getline(cin, str, '\n');
        cout << "\n>Command [" << i++ << "]: " << str << endl;
        cout << command(str) << endl;
        cout << "records selected: " << select_recnos() << endl;
        cout << ">SQL: DONE." << endl << endl << endl;
        cout << "\n<SQL: Continue? Press [X] to exit:" << endl;
        getline(cin, str, '\n');
    } while (str != "x" && str != "X");

    cout << "\n>SQL: Exiting. Press [X] to clean up the files." << endl;
    cin >> str;

    // if (str == "x" || str == "X"){
    //     for (int i = 0; i < _names.size(); ++i)
    //         drop_table(_names[i]);
    // }
    cout << "---------- END OF RUN PROCESS ----------\n\n";
}

void SQL::batch(const string& file_name){
    ifstream f;
    string str = "";
    int i = 0;
    f.open(file_name);

    if (f.fail()){
        throw std::runtime_error(file_name+" ... file not found");
        exit(1);
    }
    cout << "\n>batch: " << file_name << endl << endl;

    while (!f.eof()){
        getline(f, str);
        
        if (str[0] == '/')
            cout << str << endl;

        else if (str != ""){
            cout << "\n>Command [" << i++ << "]: " << str << endl;
            cout << command(str) << endl;
            cout << "records selected: " << select_recnos() << endl;
            cout << ">SQL: DONE." << endl << endl << endl;
        }
    }
    f.close();
    cout << "---------- END OF BATCH PROCESS ----------\n\n";
}

/*
void SQL::drop_table(const string& table_name){
    fs::path cwd = fs::current_path();
    try {
        // Iterate over the current directory
        for (const auto& entry : fs::directory_iterator(cwd)) {
            // Check if the entry is a file and has the .txt or .tbl file extension
            if (entry.is_regular_file()) {
                string filename = entry.path().filename().string();
                string extension = entry.path().extension().string();

                // Check if table_name is null or empty, or if the filename starts with the table_name
                if (table_name.empty() || filename.find(table_name) == 0) {
                    if (extension == ".tbl" || extension == ".txt") {
                        // Delete the file
                        fs::remove(entry.path());
                        std::cout << "deleted: " << entry.path() << std::endl;
                    }
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
*/

Table SQL::get_sql_command(mmap_ss& ptree, const string& command){
    string name = ptree["table_name"][0];

    if (ptree["command"][0] == "make"){
        _names += name;
        _table = Table(name, ptree["col"]);
        return _table;
    }

    if (ptree["command"][0] == "insert"){
        _table = Table(name);
        _table.insert_into(ptree["values"]);
        return _table;   
    }

    if (ptree["command"][0] == "select"){
        _table = Table(name);
        bool condition = ptree.contains("where");

        if (condition && ptree["fields"][0] == "*")
            return _table.select(_table.get_fields(), ptree["condition"]);

        else if (condition && ptree["fields"][0] != "*")
            return _table.select(ptree["fields"], ptree["condition"]);

        else if (!condition && ptree["fields"][0] == "*")
            return _table.select_all();

        else if (!condition && ptree["fields"][0] != "*")
            return _table.select_all(ptree["fields"]);
    }
    
    throw std::runtime_error(command+" : invalid SQL");
    _table = Table();
    return _table;
}