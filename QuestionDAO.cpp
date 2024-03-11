#include <string>
#include <memory>
#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "QuestionDAO.h" 
using namespace std;


QuestionDAO::QuestionDAO()
{
}

QuestionDAO::QuestionDAO(sql::Connection* con) : con(con) {}

QuestionDAO::~QuestionDAO() {
//    delete con;
}

bool QuestionDAO::addQuestion(Question* question) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO QUESTION(question, quizID, questionID) VALUES (?, ?, ?)");
        pstmt->setString(1, question->getQuestion());
        pstmt->setInt(2, question->getQuizID());
        pstmt->setInt(3, question->getQuestionID());
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return false;
    }
}

Question QuestionDAO::getQuestion(int quizID, int questionID) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT question FROM QUESTION WHERE quizID = ? AND questionID = ?");
        pstmt->setInt(1, quizID);
        pstmt->setInt(2, questionID);
        sql::ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            Question question(res->getString("question"), quizID, questionID);
            delete pstmt;
            delete res;
            return question;
        }
        else {
            delete pstmt;
            delete res;
            return Question(); // Return a default-constructed Question object if no question is found
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return Question(); // Return a default-constructed Question object in case of an error
    }
}

map<int, Question> QuestionDAO::getAllQuestions(int quizID)
{
    map<int, Question> questionMap;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM QUESTION WHERE quizID = ?");
        pstmt->setInt(1, quizID);
        sql::ResultSet* res = pstmt->executeQuery();

        while (res->next()) {
            Question question(res->getString("question"), quizID, res->getInt("questionID"));
            questionMap.insert(make_pair(res->getInt("questionID"), question));
        }
        delete res;
        delete pstmt;

    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return questionMap; // Return a default-constructed Question object in case of an error
    }
    return questionMap;
}


