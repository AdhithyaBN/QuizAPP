#include<iostream>
#include <string>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <utility>
#include "Quiz.h"
#include "QuizDAO.h"
using namespace std;



QuizDAO::QuizDAO(sql::Connection* con) {
    this->con = con;
}

QuizDAO::~QuizDAO() {}

QuizDAO::QuizDAO() {}

bool QuizDAO::addQuiz(Quiz* quiz) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO QUIZ(id, title, descr, maxScore, activ) VALUES (?, ?, ?, ?, ?)");
        pstmt->setInt(1, quiz->getQuizId());
        pstmt->setString(2, quiz->getTitle());
        pstmt->setString(3, quiz->getDescription());
        pstmt->setInt(4, quiz->getMaxScore());
        pstmt->setBoolean(5, quiz->isActive());
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return false;
    }
}

std::pair<bool, Quiz> QuizDAO::getQuiz(int id) {
    Quiz temp = Quiz();
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM QUIZ WHERE id = ?");
        pstmt->setInt(1, id);
        sql::ResultSet* res = pstmt->executeQuery();
        if (res->next()) {
            temp= Quiz(res->getInt("id"), res->getString("title"), res->getString("descr"), res->getBoolean("activ"), res->getInt("maxScore") );
            delete pstmt;
            delete res;
            return std::make_pair(true, temp);
        }
        else {
            delete pstmt;
            delete res;
            return std::make_pair(false, temp);
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return std::make_pair(false, temp);
    }
}

bool QuizDAO::updateQuiz(Quiz* quiz) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE QUIZ SET title=?, descr=?, maxScore=?, activ=? WHERE id=?");
        pstmt->setString(1, quiz->getTitle());
        pstmt->setString(2, quiz->getDescription());
        pstmt->setInt(3, quiz->getMaxScore());
        pstmt->setBoolean(4, quiz->isActive());
        pstmt->setInt(5, quiz->getQuizId());
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return false;
    }
}

bool QuizDAO::deleteQuiz(int id) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("DELETE FROM QUIZ WHERE id=?");
        pstmt->setInt(1, id);
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return false;
    }
}

map<int,string> QuizDAO::getQuizzes()
{
    map<int, string> quizNames;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT COUNT(*) FROM QUIZ");
        sql::ResultSet* res1 = pstmt->executeQuery();
        sql::PreparedStatement* pstmtQ = con->prepareStatement("SELECT activ, id, title FROM QUIZ");
        sql::ResultSet* res = pstmtQ->executeQuery();
        res1->next();
        for (int i = 0; i < res1->getInt(1);i++) {
            res->next();
            if (res->getBoolean("activ")) {
                quizNames.insert(make_pair(res->getInt("id"), res->getString("title")));
            }
        }
            
            delete pstmt;
            delete res;
            delete pstmtQ;
            delete res1;
        return quizNames;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return quizNames;
    }
}
