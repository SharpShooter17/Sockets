#ifndef SQRTREQUEST_HPP
#define SQRTREQUEST_HPP

#include "request.hpp"

class SqrtRequest : public Request
{
	private:
	double m_sqrt;
	public: 
	SqrtRequest(int);
	double getSqrt();
	void setSqurt(double);
};


#endif
