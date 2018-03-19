#ifndef REQUESTTIME_HPP
#define REQUESTTIME_HPP

#include "request.hpp"

class ResponseTime : public Request
{
	private:
	unsigned int m_lenght;
	char m_timestamp[64];
	public:
	ResponseTime();
	~ResponseTime();
	unsigned long int getlenght();
	void setLenght(unsigned int);
	char * getTmestamp();
};
//void dumpHex(const void* data, unsigned int size);
#endif
