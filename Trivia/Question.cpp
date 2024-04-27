#include "Question.h"

Question::Question()
{
}

Question::Question(const std::string question, const std::string correct, const std::vector<std::string> incorrectAnswers)
{
	this->_question = question;
	this->_correctAnswer = correct;
	this->_incorrects = incorrectAnswers;
}

Question::~Question()
{
}

std::string Question::getQuestion() const
{
	return this->_question;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
	return this->_incorrects;
}

std::string Question::getCorrentAnswer() const
{
	return this->_question;
}
