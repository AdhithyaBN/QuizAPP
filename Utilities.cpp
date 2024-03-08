#include<iostream>

#include "Utilities.h";

using namespace std;


Utilities::Utilities()
{
	con = dbcon.getConnection();
	userdao = UserDAO(con);
	admindao = AdminDAO(con);
	quizdao = QuizDAO(con);
	questiondao = QuestionDAO(con);
	optiondao = OptionDAO(con);
	questiontakendao = QuestionTakenDAO(con);
	quiztakendao = QuizTakenDAO(con);
}

Utilities::~Utilities()
{
}
std::pair<bool, User> Utilities::authenticateUser() {
	string username, password;
	cout << "Please enter your username: " << endl;
	getline(cin,username);

	auto userPair = userdao.getUser(username);
	if (userPair.first) {
		cout << "Please enter your password: " << endl;
		getline(cin,password);
		if (userPair.second.getPassword() == password) {
			cout << "Authentication successful!\n" << endl;
			return std::make_pair(true, userPair.second);
		}
		else {
			cout << "Incorrect password." << endl;
		}
	}
	else {
		cout << "User not found." << endl;
	}
	User temp = User();
	return std::make_pair(false, temp);
}

std::pair<bool, Admin> Utilities::authenticateAdmin()
{
	string username, password;
	cout << "Please enter your username: " << endl;
	getline(cin,username);

	auto adminPair = admindao.getAdmin(username);
	if (adminPair.first) {
		cout << "Please enter your password: " << endl;
		getline(cin,password);
		if (adminPair.second.getPassword() == password) {
			cout << "Authentication successful!\n" << endl;
			return std::make_pair(true, adminPair.second);
		}
		else {
			cout << "Incorrect password." << endl;
		}
	}
	else {
		cout << "Admin not found." << endl;
	}
	Admin temp = Admin();
	return std::make_pair(false, temp); // Return a default-constructed Admin object}
}

map<int, string> Utilities::getQuizzes()
{
	map<int,string> quizNames=quizdao.getQuizzes();
	return quizNames;
}

void Utilities::takeQuiz(User user,int quizID)
{
	auto quizPair = quizdao.getQuiz(quizID);
	auto quizTakenPair = quiztakendao.getQuizTaken(quizID, user.getUsername());
	int attempt=1;
	QuizTaken quizTaken;
	if (quizTakenPair.first) {
		quizTaken = quizTakenPair.second;
		attempt = quizTaken.getAttempt()+1;
	}
	map<int, Question> questionMap;
	map<int, Option> optionMap;
	Question question;
	Option option;
	if (quizPair.first) {
		Quiz quiz = quizPair.second;
		cout << "\nQuiz " << quiz.getTitle() << "  " <<" Max Score: "<<quiz.getMaxScore()<< endl;
		questionMap = questiondao.getAllQuestions(quiz.getQuizId());
		cout << "\nQuestions: " << endl;
		int score = 0;
		for (int questionID = 0; questionID < 3; questionID++) {
			question = questionMap[questionID];
			int optionSelected;

			cout <<questionID + 1 << ". " << question.getQuestion()<< endl;
			optionMap=optiondao.getAllOptions(quiz.getQuizId(), question.getQuestionID());
			cout << "Options:" << endl;
			for (int optionID = 0; optionID < 4; optionID++) {
				option = optionMap[optionID];
				cout <<option.getOptionID()<<") "<< option.getText() << endl;
			}
			cout << "Enter Option: ";
			cin >> optionSelected;
			cout << "\n";
			score += optionMap[optionSelected].getScore();

			questiontakendao.addQuestionsTaken(QuestionsTaken(quiz.getQuizId(), question.getQuestionID(), optionSelected, user.getUsername(),attempt));
		}
		cout << "Quiz completed with score: " << score << endl;
		quiztakendao.addQuizTaken(QuizTaken(quiz.getQuizId(), score, user.getUsername(),attempt));

	}
}

map<pair<int, int>, QuizTaken> Utilities::getUserQuizzes(User user)
{
	map<pair<int, int>, QuizTaken> set= quiztakendao.getAllQuizzesTaken(user.getUsername());
	map<pair<int, int>, QuizTaken>::iterator it = set.begin();
	cout << "QuizID Attempt Score" << endl;
	while (it != set.end()) {
		cout << it->first.first << "	 "<<it->first.second<<"		" << it->second.getScore() << endl;
		it++;
	}
}


void Utilities::registerNewUser()
{
	string username, password;
	cout << "Set username:" << endl;
	getline(cin,username);
	while (userdao.isUsernameExists(username)) {
		cout << "Username exists, enter new username" << endl;
		getline(cin, username);
	}
	cout << "Set password" << endl;
	getline(cin,password);
	string name, phno;
	int age;
	cout << "Enter name:" << endl;
	getline(cin,name);
	cout << "Enter phno:" << endl;
	getline(cin,phno);
	cout << "Enter age:" << endl;
	cin >> age;
	cout << "User registered, login now!\n" << endl;
	User user = User(name, age, phno, username, password);
	userdao.addUser(&user);
}

void Utilities::registerNewAdmin()
{
	string username, password;
	cout << "Set username:" << endl;
	getline(cin, username);
	while (admindao.isUsernameExists(username)) {
		cout << "Username exists, enter new username" << endl;
		getline(cin, username);
	}
	cout << "Set password:" << endl;
	getline(cin, password);
	string name, phno;
	int age;
	cout << "Enter name:" << endl;
	getline(cin, name);
	cout << "Enter phno:" << endl;
	getline(cin, phno);
	cout << "Enter age:" << endl;
	cin >> age;
	cout << "Admin registered, Login Now\n" << endl;
	Admin temp = Admin(name, age, phno, username, password);
	admindao.addAdmin(&temp);

}

void Utilities::addQuiz()
{
	int quizID;
	string type;
	string desc;
	Question questions[3];
	int max_score=0;
	bool active = true;
	cout << "Enter unique integer quiz ID:" << endl;
	cin >> quizID;
	//utilities.checkQuizUnique(quizID);
	cout << "Enter type of quiz:" << endl;
	getline(cin,type);
	cout << "Enter quiz description" << endl;
	getline(cin,desc);
	for (int i = 0; i < 3; i++) {
		int questionID = i;
		string quest;
		Option options[4];
		bool skipped;
		cout << "Enter Question: " << endl;
		getline(cin,quest);
		for (int j = 0; j < 4; j++) {
			string text;
			int score;
			cout << "Enter Option:" << endl;
			getline(cin,text);
			cout << "Enter integer score:" << endl;
			cin >> score;
			if (score > 0) {
				max_score += score;
			}
			options[j] = Option(quizID, questionID, j, text, score);
		}
		questions[i] = Question(quizID, i, quest, options);
	}
	Quiz quiz = Quiz(quizID, type, desc, questions, max_score, active);
	quizdao.addQuiz(&quiz);
	for (int i = 0; i < 3; i++) {
		questiondao.addQuestion(&questions[i]);
		Option* options = questions[i].getOptions();
		for (int j = 0; j < 4; j++) {
			optiondao.addOption(options[j]);

		}
	}
}

