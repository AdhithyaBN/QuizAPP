#pragma once
#include <iostream>
#include <string>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Option.h"

using namespace std;

class OptionDAO {
public:
    OptionDAO();
    OptionDAO(sql::Connection* conn);
    ~OptionDAO();
    bool addOption(Option option);
    bool updateOptionScore(int quizID, int questionID, int optionID, int score);
    bool updateOptionText(int quizID, int questionID, int optionID, string text);
    bool deleteOption(int quizID, int questionID, int optionID);
    Option getOption(int quizID, int questionID, int optionID);
    map<int, Option> getAllOptions(int quizID, int questionID);

private:
    sql::Connection* con;
};
