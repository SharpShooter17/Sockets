#include "protocol.hpp"
#include <arpa/inet.h>
#include <iostream>
#include "endianness.hpp"
#include <string.h>


Request * Protocol::getResponse(Socket & socket)
{
	Request * req = (Request*)socket.readBytes(sizeof(Request));
	Request r = *req;
	r = Protocol::retreiveRequest(r);
	dumpHex(&r, sizeof(Request));
	//Time response
	if (r.getRequestCode() == 10)
	{
		
		ResponseTime * time = new ResponseTime;
		strncpy((char*)time, (const char *)req, sizeof(Request));
		//delete req;
		int restOfBytes = sizeof(ResponseTime) - sizeof(Request);
		char * buff = socket.readBytes(restOfBytes);
		strncpy((char*)(time + sizeof(Request)), buff, restOfBytes);
		Protocol::retreiveReponseTime(time);
		return time;
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

void Protocol::sendTimeRequest(Socket & socket)
{
	Request time(1);
	time = Protocol::assemblyRequest(time);
	socket.writeBytes((char*)&time, sizeof(time));
}
