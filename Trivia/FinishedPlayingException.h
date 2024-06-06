#pragma once

#include <exception>


class FinishedPlayingException : public std::exception
{
public:
	const char* what() const noexcept override;
};
