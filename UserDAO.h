#pragma once
#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include"User.h"
using namespace std;
class UserDAO
{
public:
    UserDAO(sql::Connection* con);
    UserDAO();
    ~UserDAO();
    sql::Connection* con;
    bool isUsernameExists(const string username);
    void addUser(User* user);
    std::pair<bool, User>getUser(string username);

private:

};