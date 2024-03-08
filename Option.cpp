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

Option::Option()
{
}

Option::Option(int quizID, int questionID, int optionID, string text, int score)
{
	this->optionID = optionID;
	this->questionID = questionID;
	this->quizID = quizID;
	this->score = score;
	this->text = text;
}

Option::~Option()
{
}

bool Option::updateScore()
{
	return false;
}

bool Option::updatetext()
{
	return false;
}
std::string Option::getText() {
	return text;
}

int Option::getScore() {
	return score;
}

int Option::getQuizID() {
	return quizID;
}

int Option::getQuestionID() {
	return questionID;
}

int Option::getOptionID() {
	return optionID;
}

