#pragma once
#include<iostream>
using namespace std;
class User
{
public:
	User();
	~User();
	User(string name, int age, string phno, string username,string password);
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
