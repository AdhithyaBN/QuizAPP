#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Question.h" // Assuming you have a Question class defined
using namespace std;
class QuestionDAO {
public:
    QuestionDAO();
    QuestionDAO(sql::Connection* con);
    ~QuestionDAO();

    // Methods for CRUD operations
    bool addQuestion(Question* question);
    Question getQuestion(int quizID, int questionID);
    map<int,Question> getAllQuestions(int quizID);

private:
    sql::Connection* con;
};