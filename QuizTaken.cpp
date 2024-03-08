#include "QuizTaken.h"

// Constructor definition using 'this' pointer
QuizTaken::QuizTaken(int quizID, int score, const std::string username,int attempt) {
    this->quizID = quizID;
    this->score = score;
    this->username = username;
    this->attempt = attempt;
}

QuizTaken::QuizTaken()
{
}

// Destructor definition
QuizTaken::~QuizTaken() {}

// Getter definitions
int QuizTaken::getQuizID() {
    return quizID;
}

int QuizTaken::getScore() {
    return score;
}

int QuizTaken::getAttempt()
{
    return attempt;
}

std::string QuizTaken::getUsername() {
    return username;
}