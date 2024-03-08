#pragma once
#include<iostream>
#include"Option.h"
using namespace std;
class Question
{
public:
	Question();
	Question(const std::string quest, int quizID, int questionID);
	Question(int quizID, int questionID, string quest, Option options[]);
	~Question();
	int quizID;
	int questionID;
	void setQuestion(std::string quest);
	void setQuizID(int quizID);
	void setQuestionID(int questionID);
	std::string getQuestion();
	int getQuizID();
	int getQuestionID();
	Option* getOptions();


private:
	string quest;
	Option options[4];
};
