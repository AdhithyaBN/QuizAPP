#pragma once
#include <iostream>
#include <string>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Admin.h"
using namespace std;
class AdminDAO {
public:
    AdminDAO(sql::Connection* con);
    AdminDAO();
    ~AdminDAO();
    bool isUsernameExists(std::string username);
    void addAdmin( Admin* admin);
    std::pair<bool, Admin>getAdmin(string username);

private:
    sql::Connection* con;
};