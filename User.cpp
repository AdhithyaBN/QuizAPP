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

User::User()
{
}

User::~User()
{
}

User::User(string name, int age, string phno, string username,string password)
{
	this->age = age;
	this->name = name;
	this->phno = phno;
	this->username = username;
	this->password = password;
}

string User::getName() {
	return name;
}

int User::getAge() {
	return age;
}

string User::getPhno() {
	return phno;
}

string User::getUsername() {
	return username;
}

string User::getPassword() {
	return password;
}

