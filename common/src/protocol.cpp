#include "protocol.hpp"
#include <arpa/inet.h>
#include <iostream>
#include "endianness.hpp"
#include <string.h>

char* Protocol::getRestOfBytesAndBuildObject(Socket & socket, int restBytes, Request * req)
{
	char * rest = socket.readBytes(restBytes);
	char * object = new char[sizeof(Request) + restBytes];
	memcpy(object, (const char*) req, sizeof(Request));
	memcpy((char*)(object + sizeof(Request)), rest, restBytes);
	delete[] rest;
	delete[] (char*)req;
	return object;
} 

Request * Protocol::getResponse(Socket & socket)
{
	Request * req = (Request*)socket.readBytes(sizeof(Request));
	Request r = *req;
	r = Protocol::retreiveRequest(r);
	dumpHex(&r, sizeof(Request));
	//Time response
	if (r.getRequestCode() == 10)
	{
		std::cout << "Time response\n";
		ResponseTime * time = (ResponseTime*)getRestOfBytesAndBuildObject(socket, sizeof(ResponseTime) - sizeof(Request), req);
		Protocol::retreiveReponseTime(time);
		return time;
	}
	else if (r.getRequestCode() == 20 )
	{
		std::cout << "SQRT response\n";
		SqrtRequest * sq = (SqrtRequest*)getRestOfBytesAndBuildObject(socket, sizeof(SqrtRequest) - sizeof(Request), req);
		Protocol::retreiveSqrtRequest(sq);
		return sq;
	} 
	else if (r.getRequestCode() == 2){
		std::cout << "SQRT request\n";
		SqrtRequest * sq = (SqrtRequest*)getRestOfBytesAndBuildObject(socket, sizeof(SqrtRequest) - sizeof(Request), req);
		Protocol::retreiveSqrtRequest(sq);
		return sq;
	} else if (r.getRequestCode() == 1)
	{
		std::cout << "Time request\n";
		*req = Protocol::retreiveRequest(*req);
		return req;
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

void Protocol::retreiveSqrtRequest(SqrtRequest* response)
{
	response->setRequestCode( ntohl(response->getRequestCode()) );
	response->setRequestId( ntohl(response->getRequestId()) );
	response->setSqurt( Endianness::ntohd(response->getSqrt()) );
}

void Protocol::assemblySqrtRequest(SqrtRequest* response)
{
	response->setRequestCode( htonl(response->getRequestCode()) );
	response->setRequestId( htonl(response->getRequestId()));
	response->setSqurt(Endianness::htond(response->getSqrt()));
}

void Protocol::sendTimeRequest(Socket & socket)
{
	Request time(1);
	time = Protocol::assemblyRequest(time);
	socket.writeBytes((char*)&time, sizeof(time));
}

void Protocol::sendSqrtRequest(Socket & socket, double s)
{
	SqrtRequest req(2);
	req.setSqurt(s);
	Protocol::assemblySqrtRequest(&req);
	dumpHex(&req, sizeof(SqrtRequest));
	socket.writeBytes((const char*)&req, sizeof(SqrtRequest));
}
