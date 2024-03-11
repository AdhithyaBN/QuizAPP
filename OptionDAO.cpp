#include <iostream>
#include <string>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Option.h"
#include "OptionDAO.h"

using namespace std;

OptionDAO::OptionDAO()
{
}

OptionDAO::OptionDAO(sql::Connection* conn) {
    this->con = conn;
}

OptionDAO::~OptionDAO() {
 //   delete con;
}

bool OptionDAO::addOption(Option option) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO OPTIONS(optionText, score, quizID, questionID, optionID) VALUES (?, ?, ?, ?, ?)");
        pstmt->setString(1, option.getText());
        pstmt->setInt(2, option.getScore());
        pstmt->setInt(3, option.getQuizID());
        pstmt->setInt(4, option.getQuestionID());
        pstmt->setInt(5, option.getOptionID());
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return false;
    }
}

bool OptionDAO::updateOptionScore(int quizID, int questionID, int optionID, int score) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE OPTIONS SET score=? WHERE quizID=? AND questionID=? AND optionID=?");
        pstmt->setInt(1, score);
        pstmt->setInt(2, quizID);
        pstmt->setInt(3, questionID);
        pstmt->setInt(4, optionID);
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return false;
    }
}

bool OptionDAO::updateOptionText(int quizID, int questionID, int optionID, string text) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE OPTIONS SET optionText=? WHERE quizID=? AND questionID=? AND optionID=?");
        pstmt->setString(1, text);
        pstmt->setInt(2, quizID);
        pstmt->setInt(3, questionID);
        pstmt->setInt(4, optionID);
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return false;
    }
}

bool OptionDAO::deleteOption(int quizID, int questionID, int optionID) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("DELETE FROM OPTIONS WHERE quizID=? AND questionID=? AND optionID=?");
        pstmt->setInt(1, quizID);
        pstmt->setInt(2, questionID);
        pstmt->setInt(3, optionID);
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return false;
    }
}

Option OptionDAO::getOption(int quizID, int questionID, int optionID) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM OPTIONS WHERE quizID=? AND questionID=? AND optionID=?");
        pstmt->setInt(1, quizID);
        pstmt->setInt(2, questionID);
        pstmt->setInt(3, optionID);
        sql::ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            Option option(res->getInt("quizID"), res->getInt("questionID"), res->getInt("optionID"), res->getString("optionText"), res->getInt("score"));
            delete pstmt;
            delete res;
            return option;
        }
        else {
            delete pstmt;
            delete res;
            return Option(); // Return an empty Option object if option is not found
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return Option(); // Return an empty Option object in case of an error
    }
}

map<string, Option> OptionDAO::getAllOptions(int quizID, int questionID)
{
    map<string, Option> optionMap;

    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM OPTIONS WHERE quizID=? AND questionID=?");
        pstmt->setInt(1, quizID);
        pstmt->setInt(2, questionID);
        sql::ResultSet* res = pstmt->executeQuery();

        while (res->next()) {
            Option option(res->getInt("quizID"), res->getInt("questionID"), res->getInt("optionID"), res->getString("optionText"), res->getInt("score"));
            optionMap.insert(make_pair(to_string(res->getInt("optionID")), option));
        }
        delete pstmt;
        delete res;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return optionMap; // Return an empty Option object in case of an error
    }

    return optionMap;
}



