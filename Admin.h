#pragma once
#include "Quiz.h"

using namespace std;
class Admin
{
public:
	Admin();
	~Admin();
	bool deleteQuiz(Quiz* quiz);
	Admin(string name, int age, string phno, string username,string password);
	string getName();
	int getAge();
	string getPhno();
	string getUsername();
	string getPassword();

private:
	string name;
	int age;
	string phno;
	string username;
	string password;
};