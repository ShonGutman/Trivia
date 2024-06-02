#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <random>

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
    Question(const std::string question, const std::string correct, const std::vector<std::string> incorecct);

    /**
     * Destructor for the Question class.
     */
    ~Question();

    /**
     * Getter method to retrieve the question text.
     *
     * @return The question text.
     */
    std::string getQuestion() const;

    /**
     * Getter method to retrieve the possible answers.
     *
     * @return A vector containing the possible answers.
     */
    std::vector<std::string> getPossibleAnswers() const;

    /**
     * Getter method to retrieve the correct answer.
     *
     * @return The correct answer.
     */
    std::string getCorrentAnswer() const;

private:
    std::string _question;               // The question text
    std::vector<std::string> _incorrects;  // Vector containing incorrect answers
    std::string _correctAnswer;     // The correct answer
    unsigned int _correctAnserID;
};
