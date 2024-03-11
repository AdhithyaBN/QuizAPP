#pragma once
#include<iostream>
#include<map>
#include"User.h"
#include "UserDAO.h"
#include "DBConnect.h"
#include "QuizDAO.h"
#include "QuestionDAO.h"
#include "OptionDAO.h";
#include "AdminDAO.h"
#include "QuestionTakenDAO.h"
#include "QuizTakenDAO.h"
using namespace std;
class Utilities
{
public:
	Utilities();
	~Utilities();
	void registerNewUser();
	void registerNewAdmin();
	void addQuiz();
	std::pair<bool, User> authenticateUser();
	std::pair<bool, Admin> authenticateAdmin();
	UserDAO userdao;
	AdminDAO admindao;
	QuizDAO quizdao;
	QuestionDAO questiondao;
	OptionDAO optiondao;
	QuestionTakenDAO questiontakendao;
	QuizTakenDAO quiztakendao;
	DBConnect dbcon;
	sql::Connection* con;
	map<int,string> getQuizzes();
	map<int, string> getDisabledQuizzes();
	void takeQuiz(User user,int quizID);
	map<pair<int, int>, QuizTaken> getUserQuizzes(User user);
	void deleteQuiz(int quizID);
	void enableQuiz(int quizID);
	
private:
	 
};