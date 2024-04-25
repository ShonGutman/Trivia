#include "Question.h"

Question::Question()
{
}

Question::Question(const string question, const string correct, const string incorecct[NUM_OF_INCORRECT])
{
	this->_question = question;
	this->_correctAnswer = correct;

	for (int i = 0; i < NUM_OF_INCORRECT; i++)
	{
		this->_possibleAnswers.push_back(incorecct[i]);
	}
}

Question::~Question()
{
}

string Question::getQuestion() const
{
	return this->_question;
}

std::vector<string> Question::getPossibleAnswers() const
{
	return this->_possibleAnswers;
}

std::string Question::getCorrentAnswer() const
{
	return this->_question;
}
