#include "responseTime.hpp"

ResponseTime::ResponseTime(unsigned int timestamp) : 
	Request(),
	m_timestamp(timestamp)
{
}

unsigned int ResponseTime::getTimestamp()
{
	return this->m_timestamp;
}

void ResponseTime::setTimeStamp(unsigned int timestamp)
{
	this->m_timestamp = timestamp;
}
