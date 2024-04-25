#pragma once

#include <iostream>
#include <vector>
#include <string>

class Question
{
public:
	Question();
	~Question();

	std::string getQuestion() const;
	std::vector<std::string> getPossibleAnswers() const;
	std::string getCorrentAnswer() const;
	unsigned int getCorrectAnswerId() const;

private:
	std::string _question;
	std::vector<std::string> _possibleAnswers;
};
