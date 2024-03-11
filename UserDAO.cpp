#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include"UserDAO.h"
using namespace std;

UserDAO::UserDAO(sql::Connection* con)
{
    this->con = con;
}

UserDAO::UserDAO()
{
}

UserDAO::~UserDAO()
{
 //   delete con;
}
bool UserDAO::isUsernameExists(const string username)
{
    
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT COUNT(*) FROM USER WHERE username = ?");
    pstmt->setString(1, username);
    sql::ResultSet* res = pstmt->executeQuery();
    res->next();
    int count = res->getInt(1);
    delete res;
    delete pstmt;
    return count > 0;
}

void UserDAO::addUser(User* user)
{
    sql::PreparedStatement* pstmt = this->con->prepareStatement("INSERT INTO USER(name1, age, phno, username, password1) VALUES (?, ?, ?, ?, ?)");
    pstmt->setString(1, user->getName());
    pstmt->setInt(2, user->getAge());
    pstmt->setString(3, user->getPhno());
    pstmt->setString(4, user->getUsername());
    pstmt->setString(5, user->getPassword());
    pstmt->executeQuery();
    delete pstmt;

}
std::pair<bool, User> UserDAO::getUser( string username) {
    sql::PreparedStatement* pstmt = this->con->prepareStatement("SELECT * FROM USER WHERE username = ?");
    pstmt->setString(1, username);
    sql::ResultSet* res = pstmt->executeQuery();

    bool found = false;
    User user;

    if (res->next()) {
        string name = res->getString("name1");
        int age = res->getInt("age");
        string phno = res->getString("phno");
        string password = res->getString("password1");

        user = User(name, age, phno, username, password);
        found = true;
        return std::make_pair(found, user);
    }

    delete res;
    delete pstmt;

    return std::make_pair(found, user);
}

