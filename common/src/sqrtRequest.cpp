#include "sqrtRequest.hpp"

SqrtRequest::SqrtRequest(int codeReq) : Request(codeReq)
{}

double SqrtRequest::getSqrt()
{
	return this->m_sqrt;
}
void SqrtRequest::setSqurt(double s)
{
	this->m_sqrt = s;
}
