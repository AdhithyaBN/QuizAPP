#pragma once
#include<iostream>
#include <string>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <utility>
#include "Quiz.h"

using namespace std;
class QuizDAO {
public:
    QuizDAO(sql::Connection* con);
    ~QuizDAO();
    QuizDAO();
    bool addQuiz(Quiz* quiz);
    std::pair<bool, Quiz> getQuiz(int id);
    bool updateQuiz(Quiz* quiz);
    bool deleteQuiz(int id);
    int getMaxQuizID();
    void disableQuiz(int quizID);
    void enableQuiz(int quizID);
    map<int,string> getQuizzes();
    map<int, string> getDisabledQuizzes();

private:
    sql::Connection* con;
};
