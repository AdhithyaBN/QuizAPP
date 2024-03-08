#include<iostream>
#include "Display.h"
using namespace std;


Display::Display()
{
}

Display::~Display()
{
}

void Display::start()
{
	
	cout << "Welcome to the Quiz App"<<endl;
	string role;
	string login;
	while (true)
	{
		cout << "Are you an User or an Admin?\n";
		cout << "Enter\n0 for User\n1 for Admin\n";
		getline(cin,role);
		if (role != "0" && role != "1") {
			cout << role;
			cout << "Enter 0/1 only plis"<<endl;
			continue;
		}
		cout << "Do you wish to: " << endl;
		cout << "Register(0)/Login(1)" << endl;
		getline(cin, login);
		if (login != "0" && login != "1") {
			cout << "Enter 0/1 only plis" << endl;;
			continue;
		}
		if (role == "0") {
			if (login == "0") {
				utilities->registerNewUser();
			}
			if (login == "1") {
				auto pair = utilities->authenticateUser();
				for (int i = 0; i < 2 && !pair.first; i++)
				{
					pair= utilities->authenticateUser();
				}if (pair.first) {
					int choice;
					cout << "Hello " << pair.second.getName()<<endl;
					cout << "\nWhat do you wish to do\n(0)Take Quiz\n(1)Review Quizzes\n";
					cin >> choice;
					if (choice == 0) {
						cout << "\nQuizzes available are: " << endl;
						map<int,string> quizNames=utilities->getQuizzes();
						map<int, string>::iterator it = quizNames.begin();
						cout << "QuizID Title" << endl;
						while (it != quizNames.end()) {
							cout << it->first << "	 " << it->second << endl;
							it++;
						}
						int quizID;
						cout << "\nEnter QuizID for the quiz you want to take:" << endl;
						cin >> quizID;
						utilities->takeQuiz(pair.second, quizID);
					}
					if (choice == 1) {
						utilities->getUserQuizzes(pair.second);
					}
				}
			}

		}
		if (role == "1") {
			if (login == "0") {
				utilities->registerNewAdmin();
			}
			else if (login == "1") {
				auto pair = utilities->authenticateAdmin();
				for (int i = 0; i < 2 && !pair.first; i++)
				{
					pair = utilities->authenticateAdmin();
				}if (pair.first) {
					string quizOp="3";
					Admin admin = pair.second;
					cout <<"Hello "<< admin.getName()<<endl;
					while (quizOp != "2") {
						cout << "Add Quiz (0) / Delete Quiz (1) / Exit(2)" << endl;
						getline(cin,quizOp);
						if (quizOp != "0" && quizOp != "1" && quizOp != "2") {
							cout << "Blind much?" << endl;
						}
						else if (quizOp == "0") {
							utilities->addQuiz();
						}
						else if (quizOp == "1") {
							cout << "Enter quiz to be deleted, (For dev: show quizzes and then get id and obtain that and delete)" << endl;
							//admin.deleteQuiz(Quiz quiz);
						}
					}
				}
			}
		}



	}
}


