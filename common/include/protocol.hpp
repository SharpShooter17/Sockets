#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "request.hpp"
#include "responseTime.hpp"
#include "socket.hpp"

enum REQUEST { TIME, SQRT };

class Protocol
{
	public:
	static Request* getResponse(Socket & socket);
	
	static Request retreiveRequest(Request req);
	static Request assemblyRequest(Request req);
	
	static void retreiveReponseTime(ResponseTime* response);
	static void assemblyReponseTime(ResponseTime* response);
	
	static void sendTimeRequest(Socket & socket);
};
#endif

