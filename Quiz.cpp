#include<iostream>
#include "Question.h"
using namespace std;
class Quiz
{
public:
	Quiz();
	~Quiz(); 
	Quiz(int quizID, string title, string desc, bool active,int maxScore);
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

Quiz::Quiz()
{
}

Quiz::~Quiz()
{
}

Quiz::Quiz(int quizID, string title, string desc, bool active, int maxScore)
{
	this->quizID = quizID;
	this->title = title;
	this->description = desc;
	this->active = active;
	this->score = maxScore;
}

Quiz::Quiz(int quizID, string title, string desc, Question questions[], int score, bool active)
{
	this->active = active;
	this->description = desc;
	this->quizID = quizID;
	this->score = score;
	this->title = title;
	for (int i = 0; i < 3; i++)
	{
		this->questions[i] = questions[i];
	}
}

void Quiz::setActive(bool active)
{
	this->active = active;
}
int Quiz::getQuizId() { return quizID; }
string Quiz::getTitle() { return title; }
string Quiz::getDescription() { return description; }
int Quiz::getMaxScore()
{
	return this->score;
}
bool Quiz::isActive() { return active; }
Question* Quiz::getQuestions() {
	return questions;
}

