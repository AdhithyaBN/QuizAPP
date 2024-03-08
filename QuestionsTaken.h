#pragma once
#include<iostream>
using namespace std;
class QuestionsTaken
{
public:
	QuestionsTaken();
	~QuestionsTaken();
	QuestionsTaken(int quizID, int questionID, int optionID, const std::string username,int attempt);

	// Getter declarations
	int getQuizID();
	int getQuestionID();
	int getOptionID();
	int getAttempt();
	std::string getUsername();
private:
	int quizID, questionID, optionID,attempt;
	string username;
};

