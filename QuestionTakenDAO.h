#pragma once
#include <iostream>
#include <string>
#include <map>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "QuestionsTaken.h"

class QuestionTakenDAO {
public:
    QuestionTakenDAO(sql::Connection* conn);
    QuestionTakenDAO();
    ~QuestionTakenDAO();
    sql::Connection* con;

    bool addQuestionsTaken(QuestionsTaken questionsTaken);
    std::map<int, QuestionsTaken> getQuestionsTaken(const std::string username, int quizID);

private:

};
