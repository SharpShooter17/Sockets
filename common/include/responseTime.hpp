#ifndef REQUESTTIME_HPP
#define REQUESTTIME_HPP

#include "request.hpp"

class ResponseTime : public Request
{
	private:
	unsigned int m_timestamp;
	public:
	ResponseTime(unsigned int timestamp = 0);
	unsigned int getTimestamp();
	void setTimeStamp(unsigned int);
};

#endif
