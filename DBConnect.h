#pragma once

#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;
class DBConnect
{
public:
    DBConnect();
    ~DBConnect();
    const string server = "tcp://127.0.0.1:3306";
    const string username = "root";
    const string password = "A7bn6541!A7bn6541!";
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;
    sql::Connection* getConnection();
private:

};
