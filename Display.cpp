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
	string role="3";
	string login;
	while (role != "2")
	{
		cout << "Are you an User or an Admin?\n";
		cout << "Enter\n0 for User\n1 for Admin\n2 for Exit\n";
		getline(cin>>ws,role);
		if (role == "2") {
			continue;
		}
		if (role != "0" && role != "1") {
			cout << role;
			cout << "Enter 0/1 only plis"<<endl;
			continue;
		}
		cout << "Do you wish to: " << endl;
		cout << "Register(0)/Login(1)" << endl;
		getline(cin>>ws, login);
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
					string choice = "4";
					cout << "Hello " << pair.second.getName()<<endl;

					while (choice != "2") {
						cout << "\nWhat do you wish to do\n(0)Take Quiz\n(1)Review Quizzes\n(2)Exit\n";
						cin >> choice;
						if (choice != "0" && choice != "1" && choice != "2" && choice != "4") {
							cout << "blind much?" << endl;
							continue;
						}
						if (choice == "0") {
							cout << "\nQuizzes available are: " << endl;
							map<int, string> quizNames = utilities->getQuizzes();
							map<int, string>::iterator it = quizNames.begin();
							cout << "QuizID Title" << endl;
							while (it != quizNames.end()) {
								cout << it->first << "	 " << it->second << endl;
								it++;
							}
							string quizID;
							cout << "\nEnter QuizID for the quiz you want to take (enter 0 to quit):" << endl;
							getline(cin>>ws,quizID);
							if (quizID != "0") {
								try {
									utilities->takeQuiz(pair.second, stoi(quizID));
								}
								catch (exception e) {
									cout << "Enter valid quizID" << endl;
								}
							}
						}
						if (choice == "1") {
							utilities->getUserQuizzes(pair.second);
						}
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
					string quizOp="4";
					Admin admin = pair.second;
					cout <<"Hello "<< admin.getName()<<endl;
					while (quizOp != "3") {
						cout << "Add Quiz (0) / Disable Quiz (1) / Enable Quiz(2) / Exit(3)" << endl;
						getline(cin >> ws,quizOp);
						if (quizOp != "0" && quizOp != "1" && quizOp != "2") {
							cout << "Blind much?" << endl;
						}
						else if (quizOp == "0") {
							utilities->addQuiz();
						}
						else if (quizOp == "1") {
							string quizID;
							cout << "Available Quizzes" << endl;
							map<int, string> quizNames = utilities->getQuizzes();
							map<int, string>::iterator it = quizNames.begin();
							cout << "QuizID Title" << endl;
							while (it != quizNames.end()) {
								cout << it->first << "	 " << it->second << endl;
								it++;
							}
							cout << "Enter quizID to disable" << endl;
							getline(cin>>ws,quizID);
							try {
								utilities->deleteQuiz(stoi(quizID));
							}
							catch (exception e) {
								cout << "Enter numbers plis" << endl;
							}
						}
						else if (quizOp == "2") {
							string quizID;
							int i = 0;
							cout << "Disabled quizzes" << endl;
							map<int, string> quizNames = utilities->getDisabledQuizzes();
							map<int, string>::iterator it = quizNames.begin();
							cout << "QuizID Title" << endl;
							while (it != quizNames.end()) {
								i += 1;
								cout << it->first << "	 " << it->second << endl;
								it++;
							}
							if (i == 0) {
								cout << "No quizzes to delete" << endl;
							}
							else {
								cout << "Enter quizID to enable" << endl;
								getline(cin>>ws,quizID);
								try {
									utilities->enableQuiz(stoi(quizID));
								}
								catch (exception e) {
									cout << "Please enter valid quizID" << endl;
								}
							}
							
						}
					}
				}
			}
		}



	}
}


