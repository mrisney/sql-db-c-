
# Relational Database Implementation in C++

## Overview
This repository contains the implementation of a relational database system in C++. The system is designed with a focus on efficient data storage, retrieval, and query processing. Key components of the system include a B+ tree for indexing, a multimap for data organization, a file IO abstraction layer for data persistence, and a sophisticated SQL parser using a state machine.

## Components

### SQL Interface (`sql.h`)
- **Purpose**: Serves as the main interface for SQL operations.
- **Key Features**: Provides high-level functions for interacting with the database.

### File Record Management (`file_record.h`)
- **Role**: Manages the storage and retrieval of records in the database.
- **Functionality**: Ensures efficient data handling and supports the file IO operations.

### B+ Tree (`bplustree.h`)
- **Description**: A core component for indexing data.
- **Functionality**: Optimizes data retrieval processes by maintaining a balanced tree structure. Essential for handling large datasets efficiently.

### Multimap (`multimap.h`)
- **Purpose**: Aids in data organization and indexing.
- **Features**: Allows for efficient storage and retrieval of data based on multiple keys, enhancing the querying capabilities.

### SQL Parser (`parser.h`)
- **Role**: Parses and interprets SQL queries.
- **Implementation**: Utilizes a state machine (defined in `state_machine_functions.h`) to process user queries into executable actions.

### State Machine (`state_machine_functions.h`)
- **Functionality**: Drives the parsing process of SQL queries.
- **Details**: Contains functions that define various states of the parser, ensuring accurate interpretation of SQL commands.

## System Architecture
- **Integration**: Each component is designed to work in harmony, providing a seamless experience for database management.
- **Performance**: Special emphasis on performance, with efficient algorithms like B+ tree for indexing and a well-structured parser.

## Usage
- Instructions on how to compile and run the database system.
- Examples of SQL commands and how to execute them using this system.

## Contributions and Feedback
- Guidelines on how to contribute to the project.
- Information on how to report issues or provide feedback.

---

This README provides an overview of the relational database system. For detailed documentation on each component, please refer to the respective header files.

---

## Additional Resources
- For basic testing of the database system, refer to the test file: [basic_test.cpp](_tests/_test_files/basic_test.cpp)
