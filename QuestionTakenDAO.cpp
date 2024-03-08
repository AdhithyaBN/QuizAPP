#include "QuestionTakenDAO.h"

QuestionTakenDAO::QuestionTakenDAO(sql::Connection* conn)
    : con(conn) {}

QuestionTakenDAO::QuestionTakenDAO()
{
}

QuestionTakenDAO::~QuestionTakenDAO() {}

bool QuestionTakenDAO::addQuestionsTaken(QuestionsTaken questionsTaken) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO QUESTIONSTAKEN(username, quizID, questionID, optionID, attempt) VALUES (?, ?, ?, ?, ?)");
        pstmt->setString(1, questionsTaken.getUsername());
        pstmt->setInt(2, questionsTaken.getQuizID());
        pstmt->setInt(3, questionsTaken.getQuestionID());
        pstmt->setInt(4, questionsTaken.getOptionID());
        pstmt->setInt(5, questionsTaken.getAttempt());
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return false;
    }
}

std::map<int, QuestionsTaken> QuestionTakenDAO::getQuestionsTaken(const std::string username, int quizID)
{
    std::map<int, QuestionsTaken> questionsMap;
    QuestionsTaken questionsTaken;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM QUESTIONSTAKEN WHERE username=? AND quizID=?");
        pstmt->setString(1, username);
        pstmt->setInt(2, quizID);
        sql::ResultSet* res = pstmt->executeQuery();

        while (res->next()) {
            int questionID = res->getInt("questionID");
            int optionID = res->getInt("optionID");
            int attempt = res->getInt("attempt");
            questionsTaken = QuestionsTaken(quizID, questionID, optionID, username, attempt);
            questionsMap[questionID] = questionsTaken;
        }

        delete res;
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
    }
    return questionsMap;
}
