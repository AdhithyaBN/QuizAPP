#include <iostream>
#include <string>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <utility>
#include"AdminDAO.h"
using namespace std;



AdminDAO::AdminDAO(sql::Connection* con) {
    this->con = con;
}

AdminDAO::AdminDAO() {}

AdminDAO::~AdminDAO() {}

bool AdminDAO::isUsernameExists( string username)
{
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT COUNT(*) FROM ADMIN WHERE username = (?)");
    pstmt->setString(1, username);
    sql::ResultSet* res = pstmt->executeQuery();
    res->next();
    int count = res->getInt(1);
    delete res;
    delete pstmt;
    return count > 0;
}

void AdminDAO::addAdmin( Admin* admin) {
    sql::PreparedStatement* pstmt = this->con->prepareStatement("INSERT INTO ADMIN1 (admin_name, age, phno, username, password1) VALUES (?, ?, ?, ?, ?)");
    pstmt->setString(1, admin->getName());
    pstmt->setInt(2, admin->getAge());
    pstmt->setString(3, admin->getPhno());
    pstmt->setString(4, admin->getUsername());
    pstmt->setString(5, admin->getPassword());

    pstmt->executeQuery();
    delete pstmt;
}

std::pair<bool, Admin> AdminDAO::getAdmin( string username) {
    sql::PreparedStatement* pstmt = this->con->prepareStatement("SELECT * FROM ADMIN1 WHERE username = ?");
    pstmt->setString(1, username);
    sql::ResultSet* res = pstmt->executeQuery();

    bool found = false;
    Admin admin;

    if (res->next()) {
        string name = res->getString("admin_name");
        int age = res->getInt("age");
        string phno = res->getString("phno");
        string password = res->getString("password1");
        admin= Admin(name, age, phno, username, password);
        found = true;
    }

    delete res;
    delete pstmt;

    return std::make_pair(found, admin);
}

