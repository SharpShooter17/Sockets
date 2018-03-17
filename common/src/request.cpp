#include "request.hpp"

Request::Request(unsigned int requestCode) : 
	m_request_code(requestCode),
	m_request_id(nextRequest())
{
}

unsigned int Request::getRequestCode()
{
	return this->m_request_code;
}

void Request::setRequestCode(unsigned int requestCode)
{
	this->m_request_code = requestCode;
}

unsigned int Request::getRequestId()
{
	return this->m_request_id;
}

void Request::setRequestId(unsigned int id)
{
	this->m_request_id = id;
}

unsigned int nextRequest()
{
	return m_request_id_counter++;
}
