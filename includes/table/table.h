#ifndef TABLE_H
#define TABLE_H

#include "typedefs.h"

class Table {

 public:
    
    // CONSTRUCTORS
    Table();
    Table(const string& name);
    Table(const string& name, const vectorstr& field_names);
    // ~Table();   // TODO clean up table files
   
    // SQL: CREATE TABLE
    string create_table(const string& name, const vectorstr& field_names);

    // SQL: INSERT INTO
    void insert_into(const vectorstr& field_values);

    // SQL: SELECT
    Table select_all(const vectorstr& field_names = vectorstr());
    Table select(const vectorstr& fields, const string& field_name, const string& op, const string& field_value);
    Table select(const vectorstr& fields, const Queue<Token*>& postfix_q);
    Table select(const vectorstr& fields, const vectorstr& input_v);

    // all selected record numbers
    inline vectorl select_recnos() const { return _recnos; }
    
    // print table
    friend ostream& operator<<(std::ostream& outs, const Table& t);
    
    // title of the table
    inline string title() const { return _name; }
    
    // fields from table
    inline vectorstr get_fields() { return _field_names; }
    
    // number of records in table
    inline long record_count() const { return select_recnos().size(); }

private:
    
    static long Serial;

    string _name;                       
    vectorstr _field_names;             
    long _recno;                        
                     
    map_sl _map;                        
    vector<mmap_sl> _indices;
    vectorl _recnos;        
    vectorstr _fields;      

    void set_fields(const vectorstr& field_names);  
    void reindex(const vectorstr& field_values); 

    vectorl set_operator(const mmap_sl::Iterator& begin, const mmap_sl::Iterator& end);
    vectorl set_recnos(const string& field_name, const string& op, const string& field_value);
    Table vector_to_table();
    vectorl rpn(const queue_token& postfix_q);
    queue_token set_infix(const vectorstr& input_v);
    
};    

#endif // TABLE_H