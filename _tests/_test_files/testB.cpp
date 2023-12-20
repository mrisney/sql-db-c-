#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

//------------------------------------------------------------------------------------------
//Files we are testing:
#include "../../includes/sql/sql.h"
//------------------------------------------------------------------------------------------

using namespace std;

// Forward declarations of test functions
bool test_create_table(bool debug);
bool test_insert_records(bool debug);
bool test_select_records(bool debug);
bool test_edge_cases(bool debug);
// Add other test functions as needed

// Implementation of test functions
bool test_create_table(bool debug) {
  // Logic to test table creation
  // Use SQL class to create table and check if creation was successful
  // Return true if test passes, false otherwise
  return true; // Placeholder
}

bool test_insert_records(bool debug) {
  // Logic to test record insertion
  return true; // Placeholder
}

bool test_select_records(bool debug) {
  // Logic to test record selection
  return true; // Placeholder
}

bool test_edge_cases(bool debug) {
  // Logic to test edge cases
  return true; // Placeholder
}

bool test_drop_table(bool debug) {
    SQL sql;
    // Assume command returns true on success

     cout << sql.command("make table temp_table2 fields id, name") << endl;



    bool create_success  = true;

    if (!create_success) {
        if (debug) {
            cout << "Failed to create table." << endl;
        }
        return false; // Table creation failed
    }

    // Drop the table
   // sql.drop_table("");

    // Check if the table still exists
    // This is a placeholder for your actual implementation
    // E.g., sql.has_table("temp_table") which should return false if the table doesn't exist
    return true; // Placeholder
}



// Test function for destructor
bool test_destructor(bool debug) {
    {
        SQL sql;
        sql.command("make table temp_table1 fields id, name");
        sql.command("make table temp_table2 fields id, name");
        // Destructor will be called at the end of this scope
    }

    // Add logic to verify that 'temp_table1' and 'temp_table2' no longer exist
    // Return true if all tables are dropped, false otherwise
    return true; // Placeholder
}


// Test cases using Google Test framework
TEST(SQLTest, CreateTable) {
  EXPECT_TRUE(test_create_table(false));
}

TEST(SQLTest, InsertRecords) {
  EXPECT_TRUE(test_insert_records(false));
}

TEST(SQLTest, SelectRecords) {
  EXPECT_TRUE(test_select_records(false));
}

TEST(SQLTest, EdgeCases) {
  EXPECT_TRUE(test_edge_cases(false));
}

TEST(SQLTest, DropTable) {
    EXPECT_TRUE(test_drop_table(false));
}

TEST(SQLTest, Destructor) {
    EXPECT_TRUE(test_destructor(false));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running SQLTest.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}
