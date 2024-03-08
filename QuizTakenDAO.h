#pragma once
#include <iostream>
#include <string>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "QuizTaken.h"

class QuizTakenDAO {
public:
    QuizTakenDAO(sql::Connection* conn);
    ~QuizTakenDAO();
    QuizTakenDAO();
    sql::Connection* con;

    bool addQuizTaken(QuizTaken quizTaken);
    pair<bool,QuizTaken> getQuizTaken(int quizID, const std::string username);
    map<pair<int,int>, QuizTaken> getAllQuizzesTaken( const std::string username);


private:
};


