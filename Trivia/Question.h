#pragma once

#include <iostream>
#include <vector>
#include <string>

using std::string;

#define NUM_OF_INCORRECT 3

class Question
{
public:
    /**
     * Default constructor for the Question class.
     */
    Question();

    /**
     * Constructor for the Question class with parameters.
     *
     * @param question The question text.
     * @param correct The correct answer.
     * @param incorecct An array containing incorrect answers.
     */
    Question(const string question, const string correct, const string incorecct[NUM_OF_INCORRECT]);

    /**
     * Destructor for the Question class.
     */
    ~Question();

    /**
     * Getter method to retrieve the question text.
     *
     * @return The question text.
     */
    string getQuestion() const;

    /**
     * Getter method to retrieve the possible answers.
     *
     * @return A vector containing the possible answers.
     */
    std::vector<string> getPossibleAnswers() const;

    /**
     * Getter method to retrieve the correct answer.
     *
     * @return The correct answer.
     */
    std::string getCorrentAnswer() const;

private:
    string _question;               // The question text
    std::vector<string> _possibleAnswers;  // Vector containing possible answers
    std::string _correctAnswer;     // The correct answer
};
