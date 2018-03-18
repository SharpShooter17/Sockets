#include "protocol.hpp"
#include <arpa/inet.h>
#include <iostream>
#include "endianness.hpp"

REQUEST Protocol::getTypeOfRequest(Request req)
{
	if (req.getRequestCode() == 1)
	{
		return REQUEST::TIME;
	} else if (req.getRequestCode() == 2)
	{
		return REQUEST::SQRT;
	}
}
	
Request Protocol::retreiveRequest(Request req)
{
	req.setRequestCode( ntohl(req.getRequestCode()) );
	req.setRequestId( ntohl(req.getRequestId()));
	return req;
}

Request Protocol::assemblyRequest(Request req)
{
	req.setRequestCode( htonl(req.getRequestCode()) );
	req.setRequestId( htonl(req.getRequestId()));
	return req;
}

void Protocol::retreiveReponseTime(ResponseTime* response)
{
	response->setRequestCode( ntohl(response->getRequestCode()) );
	response->setRequestId( ntohl(response->getRequestId()));
	response->setLenght(ntohl(response->getlenght()));
}

void Protocol::assemblyReponseTime(ResponseTime* response)
{
	response->setRequestCode( htonl(response->getRequestCode()) );
	response->setRequestId( htonl(response->getRequestId()));
	response->setLenght(htonl(response->getlenght()));
}
