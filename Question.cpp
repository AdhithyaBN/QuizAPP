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

Question::Question()
{
}
Question::Question(const std::string quest, int quizID, int questionID) {
	this->quest = quest;
	this->quizID = quizID;
	this->questionID = questionID;
}


Question::Question(int quizID, int questionID, string quest, Option options[])
{
	for (int i = 0; i < 4; i++)
	{
		Question::options[i] = options[i];
	}
	Question::quest = quest;
	Question::questionID = questionID;
	Question::quizID = quizID;

}

Question::~Question()
{
}
void Question::setQuestion(std::string quest) {
	this->quest = quest;
}

void Question::setQuizID(int quizID) {
	this->quizID = quizID;
}

void Question::setQuestionID(int questionID) {
	this->questionID = questionID;
}
std::string Question::getQuestion() {
	return quest;
}

int Question::getQuizID() {
	return quizID;
}

int Question::getQuestionID() {
	return questionID;
}
Option* Question::getOptions() {
	return options; // Return the array of Option objects
}

