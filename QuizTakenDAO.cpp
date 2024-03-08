#include"QuizTakenDAO.h"

QuizTakenDAO::QuizTakenDAO(sql::Connection* conn)
    : con(conn) {}

QuizTakenDAO::~QuizTakenDAO() {}

QuizTakenDAO::QuizTakenDAO()
{
}

bool QuizTakenDAO::addQuizTaken(QuizTaken quizTaken) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO QUIZTAKEN(quizID, username, score, attempt) VALUES (?, ?, ?, ?)");
        pstmt->setInt(1, quizTaken.getQuizID());
        pstmt->setString(2, quizTaken.getUsername());
        pstmt->setInt(3, quizTaken.getScore());
        pstmt->setInt(4,quizTaken.getAttempt());
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return false;
    }
}

pair<bool, QuizTaken> QuizTakenDAO::getQuizTaken(int quizID, const std::string username) {
    QuizTaken quizTaken;
    bool found = false;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM QUIZTAKEN WHERE quizID=? AND username=?");
        pstmt->setInt(1, quizID);
        pstmt->setString(2, username);
        sql::ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            quizTaken = QuizTaken(res->getInt("quizID"), res->getInt("score"), res->getString("username"), res->getInt("attempt"));
            found = true;
        }

        delete res;
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
    }
    return std::make_pair(found, quizTaken);
}

map<pair<int, int>, QuizTaken> QuizTakenDAO::getAllQuizzesTaken(const std::string username)
{
    map<pair<int, int>, QuizTaken> set;
    QuizTaken quizTaken;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM QUIZTAKEN WHERE username=?");
        pstmt->setString(1, username);
        sql::ResultSet* res = pstmt->executeQuery();

        while (res->next()) {
            quizTaken = QuizTaken(res->getInt("quizID"), res->getInt("score"), res->getString("username"), res->getInt("attempt"));
            set.insert(make_pair(make_pair(res->getInt("quizID"), res->getInt("attempt")), quizTaken));
        }

        delete res;
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
    }
    return set;
}
