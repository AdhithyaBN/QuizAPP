#pragma once
#include<iostream>
using namespace std;
class Option
{
public:
	Option();
	Option(int quizID, int QuestionID, int optionID, string text, int score);
	~Option();
	int quizID;
	int questionID;
	int optionID;
	bool updateScore();
	bool updatetext();
	std::string getText();
	int getScore();
	int getQuizID();
	int getQuestionID();
	int getOptionID();


private:
	string text;
	int score;

};