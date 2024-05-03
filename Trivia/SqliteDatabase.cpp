#include "SqliteDatabase.h"

SqliteDatabase::SqliteDatabase()
{
	open();
}

SqliteDatabase::~SqliteDatabase()
{
	close();
}

bool SqliteDatabase::doesUserExists(const string& username) 
{
	string sqlStatement = R"(select count(*) from users where username = "{}";)";
	sqlStatement = format(sqlStatement, { username });

	int count = 0;
	preformSqlRequest(sqlStatement, callbackNumber, &count);

	return count != 0;
}

bool SqliteDatabase::doesPasswordMatch(const string& username, const string& password)
{
	string sqlStatement = R"(select count(*) from users where username = "{}" and
								password = "{}";)";
	sqlStatement = format(sqlStatement, { username, password });

	int count = 0;
	preformSqlRequest(sqlStatement, callbackNumber, &count);

	return count != 0;
}

void SqliteDatabase::signup(const string& username, const string& password, const string& email, const string& address, const string& phoneNumber, const string& birthday)
{
	string sqlStatement = R"(insert into users values ("{}", "{}", "{}", "{}", "{}", "{}");)";
	sqlStatement = format(sqlStatement, { username, password, email, address, phoneNumber, birthday });

	preformSqlRequest(sqlStatement);
}

std::vector<Question> SqliteDatabase::getQuestions(const int numOfQuestions)
{
	std::vector<Question> questionsVector;
	string sqlStatement = "select * from questions where ROWID <= {};";
	sqlStatement = format(sqlStatement, { std::to_string(numOfQuestions) });

	preformSqlRequest(sqlStatement, callbackQuestion, &questionsVector);

	return questionsVector;
}

float SqliteDatabase::getPlayerAverageAnswerTime(const string& username)
{
	float avgAnsTime = 0;
	string sqlStatement = R"(select avgAnsTime from statistics where username = "{}";)";;
	sqlStatement = format(sqlStatement, { username });

	preformSqlRequest(sqlStatement, callbackFloat, &avgAnsTime);

	return avgAnsTime;
}

int SqliteDatabase::getNumOfCorrectAnswers(const string& username)
{
	int correctAns = 0;
	string sqlStatement = "select numOfRightAns from statistics where username == {};";
	sqlStatement = format(sqlStatement, { username });

	preformSqlRequest(sqlStatement, callbackNumber, &correctAns);

	return correctAns;
}

int SqliteDatabase::getNumOfWrongAnswers(const string& username)
{
	int wrongAns = 0;
	string sqlStatement = "select numOfWrongAns from statistics where username == {};";
	sqlStatement = format(sqlStatement, { username });

	preformSqlRequest(sqlStatement, callbackNumber, &wrongAns);

	return wrongAns;
}

int SqliteDatabase::getNumOfTotalAnswers(const string& username)
{
	return getNumOfCorrectAnswers(username) + getNumOfWrongAnswers(username);
}

int SqliteDatabase::getNumOfPlayerGames(const string& username)
{
	int gamesPlayed = 0;
	string sqlStatement = "select numOfGames from statistics where username == {};";
	sqlStatement = format(sqlStatement, { username });

	preformSqlRequest(sqlStatement, callbackNumber, &gamesPlayed);

	return gamesPlayed;
}

int SqliteDatabase::getPlayerScore(const string& username)
{
	// the score is the num of right answers, the higher the num is the higher the score
	int score;
	score = getNumOfCorrectAnswers(username);

	return score;
}

std::map<std::string, int> SqliteDatabase::getHighscores()
{
	std::map<std::string, int> highscoreList;
	std::string sqlStatement = "select username, numOfRightAns from statistics;";
	preformSqlRequest(sqlStatement, callbackHighScoresMap, &highscoreList);

	return highscoreList;
}

bool SqliteDatabase::open()
{
	string dbName = DB_FILENAME;
	int doesExist = _access(dbName.c_str(), 0);
	//check if there is error in opening the DB
	if (sqlite3_open(dbName.c_str(), &_db) != SQLITE_OK)
	{
		_db = nullptr;
		throw std::runtime_error("Failed to open DB!");
		return false;
	}

	if (doesExist != 0)
	{
		//check if init tables failed
		if (!initTables())
		{
			_db = nullptr;
			return false;
		}
	}
	return true;
}

void SqliteDatabase::close()
{
	sqlite3_close(_db);
	_db = nullptr;
}

bool SqliteDatabase::create_users_table()
{
	const string sqlStatement = R"(create table users (
		username text primary key not null,
		password text not null,
		email text not null,
		address text not null,
		phoneNumber text not null,
		birthday text not null);)";

	return preformSqlRequest(sqlStatement);
}

bool SqliteDatabase::create_statistics_table()
{
	const string sqlStatement = R"(create table statistics (
		username text primary key not null,
		numOfGames int not null,
		numOfRightAns int not null,
		numOfWrongAns int not null,
		avgAnsTime float not null);)";

	return preformSqlRequest(sqlStatement);
}

bool SqliteDatabase::create_questions_table()
{
	const string sqlStatementCreateTable = R"(create table questions (
		question text not null,
		correct text not null,
		incorrect1 text not null,
		incorrect2 text not null,
		incorrect3 text not null);)";

	return preformSqlRequest(sqlStatementCreateTable) && addQuestions();
}

bool SqliteDatabase::addQuestions()
{
	bool isSuccessful = true;

	// Write all the questions
	const string questions[NUM_QUESTIONS] =
	{
		"What is the capital of France?",
		"Who wrote 'To Kill a Mockingbird'?",
		"What is the chemical symbol for water?",
		"In which year did World War I begin?",
		"Who painted the Mona Lisa?",
		"What is the largest planet in our solar system?",
		"What is the square root of 144?",
		"Who discovered penicillin?",
		"What is the currency of Japan?",
		"Who is the author of 'The Great Gatsby'?"
	};

	// Write all the correct answers to each question accordingly
	const string corrects[NUM_QUESTIONS] =
	{
		"Paris",
		"Harper Lee",
		"H2O",
		"1914",
		"Leonardo da Vinci",
		"Jupiter",
		"12",
		"Alexander Fleming",
		"Yen",
		"F. Scott Fitzgerald"
	};

	// Write a 2D array of the incorrect answers
	const string incorrects[NUM_QUESTIONS][NUM_OF_INCORRECT] =
	{
		{"London", "Berlin", "Rome"},
		{"Ernest Hemingway", "F. Scott Fitzgerald", "Harper Lee"},
		{"CO2", "NaCl", "NH3"},
		{"1918", "1939", "1945"},
		{"Michelangelo", "Vincent van Gogh", "Pablo Picasso"},
		{"Mars", "Saturn", "Neptune"},
		{"10", "14", "16"},
		{"Albert Einstein", "Isaac Newton", "Marie Curie"},
		{"Dollar", "Euro", "Pound"},
		{"John Steinbeck", "Mark Twain", "Ernest Hemingway"}
	};

	for (int i = 0; i < NUM_QUESTIONS; i++)
	{
		if (!addQuestion(questions[i], corrects[i], incorrects[i]))
		{
			throw std::runtime_error("Failed to add question!");
			break;
		}
	}

	return true;
}


bool SqliteDatabase::addQuestion(const string question, const string correct, const string incorecct[NUM_OF_INCORRECT])
{
	string sqlStatement = R"(insert into questions (question, correct, incorrect1, incorrect2, incorrect3)
							 values ("{}", "{}", "{}", "{}", "{}");)";

	// The array includes only 3 answers numbered with index - 1
	sqlStatement = format(sqlStatement, { question, correct, incorecct[0], incorecct[1], incorecct[2]});

	return preformSqlRequest(sqlStatement);
}

bool SqliteDatabase::initTables()
{
	return create_users_table() && create_questions_table() && create_statistics_table();
}

bool SqliteDatabase::preformSqlRequest(string sql, int(*callback)(void*, int, char**, char**), void* data)
{
	char* errorMsg = nullptr;
	if (sqlite3_exec(_db, sql.c_str(), callback, data, &errorMsg) != SQLITE_OK)
	{
		std::cerr << "error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
		throw std::runtime_error ("Failed to preform SQL!");
		return false;
	}
	sqlite3_free(errorMsg);
	return true;
}

int SqliteDatabase::callbackNumber(void* data, int argc, char** argv, char** azColName)
{
	int* count = static_cast<int*>(data);

	if (argv[0] == NULL)
	{
		*count = 0;
		return 0;
	}

	*count = atoi(argv[0]);

	return 0;
}

int SqliteDatabase::callbackQuestion(void* data, int argc, char** argv, char** azColName)
{
	auto questions = static_cast<std::vector<Question>*>(data); // Revert back to question list from void

	string question, incorrect1, incorrect2, incorrect3, correct;

	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == QUESTION_COL)
		{
			question = argv[i];
		}
		else if (std::string(azColName[i]) == INCORRECT1_COL)
		{
			incorrect1 = argv[i];
		}
		else if (std::string(azColName[i]) == INCORRECT2_COL)
		{
			incorrect2 = argv[i];
		}
		else if (std::string(azColName[i]) == INCORRECT3_COL)
		{
			incorrect3 = argv[i];
		}
		else if (std::string(azColName[i]) == CORRECT_COL)
		{
			correct = argv[i];
		}
	}

	std::vector<std::string> incorrects = { incorrect1 ,incorrect2, incorrect3 };
	questions->push_back(Question(question, correct, incorrects));
	return 0;
}

int SqliteDatabase::callbackFloat(void* data, int argc, char** argv, char** azColName)
{
	if (argc > 0 && argv[0]) {
		double* result = static_cast<double*>(data);
		*result = std::stod(argv[0]);
	}
	return 0;
}

int SqliteDatabase::callbackHighScoresMap(void* data, int argc, char** argv, char** azColName)
{
	// Cast the data pointer back to the map type
	std::map<std::string, int>* resultMap = static_cast<std::map<std::string, int>*>(data);
	std::string username = "";
	int numOfRightAns = 0;

	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == USERNAME_COL)
		{
			username = argv[i];
		}
		else if (std::string(azColName[i]) == RIGHT_ANS_COL)
		{
			numOfRightAns = std::stoi(argv[i]);
		}

		// Populate the map with the retrieved data
		(*resultMap)[username] = numOfRightAns;
	}

	return 0;
}

string SqliteDatabase::format(string fmt, std::vector<string> args)
{
	std::stringstream ss;
	int i = fmt.find("{}");
	for (i; i != string::npos; i = fmt.find("{}"))
	{
		ss << fmt.substr(0, i);
		ss << args[0];
		//remove first value
		args.erase(args.begin());
		fmt = fmt.substr(i + 2);
	}
	ss << fmt;
	return ss.str();
}
