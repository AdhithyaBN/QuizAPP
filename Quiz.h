#pragma once
#include<iostream>
#include "Question.h"
using namespace std;
class Quiz
{
public:
	Quiz();
	~Quiz();
	Quiz(int quizID, string title, string desc, bool active, int maxScore);
	Quiz(int quizID, string title, string desc, Question questions[], int score, bool active);
	int quizID;
	void setActive(bool active);
	int getQuizId();
	string getTitle();
	string getDescription();
	int getMaxScore();
	bool isActive();
	Question* getQuestions();


private:
	string title;
	string description;
	Question questions[3];
	int score;
	bool active;
};