#pragma once
#include <exception>

struct SDLexception : public std::exception
{
	const char * const msg;

	SDLexception(const char * msg) : msg(msg) {}
	const char * what() const throw () { return msg; }
};

