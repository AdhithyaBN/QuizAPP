#pragma once
#include<iostream>
using namespace std;
class QuizTaken
{
public:
	QuizTaken();
	~QuizTaken();
	QuizTaken(int quizID, int score, const std::string username, int attempt);
	int getQuizID();
	int getScore();
	int getAttempt();
	std::string getUsername();

private:
	int quizID, score,attempt;
	string username;
};
