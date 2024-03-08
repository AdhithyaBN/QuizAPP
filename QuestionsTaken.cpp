#include "QuestionsTaken.h"

// Constructor definition using 'this' pointer
QuestionsTaken::QuestionsTaken(int quizID, int questionID, int optionID, const std::string username,int attempt) {
    this->quizID = quizID;
    this->questionID = questionID;
    this->optionID = optionID;
    this->username = username;
    this->attempt = attempt;
}

QuestionsTaken::QuestionsTaken()
{
}

// Destructor definition
QuestionsTaken::~QuestionsTaken() {}

// Getter definitions
int QuestionsTaken::getQuizID() {
    return quizID;
}

int QuestionsTaken::getQuestionID() {
    return questionID;
}

int QuestionsTaken::getOptionID() {
    return optionID;
}

int QuestionsTaken::getAttempt()
{
    return attempt;
}

std::string QuestionsTaken::getUsername() {
    return username;
}
