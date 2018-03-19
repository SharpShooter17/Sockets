#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "request.hpp"
#include "responseTime.hpp"
#include "socket.hpp"
#include "sqrtRequest.hpp"

enum REQUEST { TIME, SQRT };

class Protocol
{
	public:
	static Request* getResponse(Socket & socket);
	
	static Request retreiveRequest(Request req);
	static Request assemblyRequest(Request req);
	
	static void retreiveReponseTime(ResponseTime* response);
	static void assemblyReponseTime(ResponseTime* response);
	
	static void retreiveSqrtRequest(SqrtRequest* response);
	static void assemblySqrtRequest(SqrtRequest* response);
	
	static void sendTimeRequest(Socket & socket);
	static void sendSqrtRequest(Socket & socket, double s);
	static char* getRestOfBytesAndBuildObject(Socket & socket, int restBytes, Request * req);
};
#endif

