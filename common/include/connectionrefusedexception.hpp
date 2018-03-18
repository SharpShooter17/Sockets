#ifndef CONNECTIONREFUSEDEXCEPTION_HPP
#define CONNECTIONREFUSEDEXCEPTION_HPP

#include <exception>

class ConnectionRefusedException : public std::exception
{
	public:
	const char * what() const throw()
	{
		return "Connection refused exception.";
	}
};

#endif
