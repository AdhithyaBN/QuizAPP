#include "Admin.h"
#include<iostream>
using namespace std;
Admin::Admin()
{
}
Admin::Admin(string name, int age, string phno, string username,string password)
{
	this->age = age;
	this->name = name;
	this->phno = phno;
	this->username = username;
	this->password = password;
}
Admin::~Admin() 
{
}


bool Admin::deleteQuiz(Quiz* quiz)
{
	quiz->setActive(false);
	return true;
}

string Admin::getName()
{
	return name;
}

int Admin::getAge()
{
	return age;
}

string Admin::getPhno()
{
	return phno;
}

string Admin::getUsername()
{
	return username;
}

string Admin::getPassword()
{
	return password;
}



