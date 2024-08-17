#include "Question.h"

// Create a random device
std::random_device rd;

Question::Question()
	:_correctAnserID(0)
{
}

Question::Question(const std::string question, const std::string correct, const std::vector<std::string> incorrectAnswers)
{
	this->_question = question;
	this->_correctAnswer = correct;
	this->_incorrects = incorrectAnswers;

	// Create a uniform distribution between 1 and x
	std::uniform_int_distribution<int> dist(1, _incorrects.size() + 1);
	_correctAnserID = dist(rd);
}

Question::~Question()
{
}

std::string Question::getQuestion() const
{
	return this->_question;
}

std::map<unsigned int, std::string> Question::getPossibleAnswers() const
{
	std::map<unsigned int, std::string> answers;
	unsigned int i = 1;

	for (auto& it : _incorrects)
	{
		if (i == _correctAnserID)
		{
			//skip that number
			i++;
		}
		answers.insert({ i++, it });
	}

	answers.insert({ _correctAnserID, _correctAnswer });
	return answers;
}

unsigned int Question::getCorrectAnserID() const
{
	return this->_correctAnserID;
}

std::string Question::getCorrectAnswer() const
{
	return this->_question;
}
