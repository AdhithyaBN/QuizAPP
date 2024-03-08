
#include <stdlib.h>
#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "mysql_connection.h"
#include "DBConnect.h"
using namespace std;

DBConnect::DBConnect()
{
}

DBConnect::~DBConnect()
{
}
sql::Connection* DBConnect::getConnection()
{
    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
        con->setSchema("quizzapp");
        return con;
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
}
