#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "request.hpp"
#include "responseTime.hpp"

enum REQUEST { TIME, SQRT };

class Protocol
{
	public:
	static REQUEST getTypeOfRequest(Request req);
	
	static Request retreiveRequest(Request req);
	static Request assemblyRequest(Request req);
	
	static void retreiveReponseTime(ResponseTime* response);
	static void assemblyReponseTime(ResponseTime* response);
};
#endif

