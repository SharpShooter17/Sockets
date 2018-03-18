#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "request.hpp"

enum REQUEST { TIME, SQRT };

class Protocol
{
	public:
	static REQUEST getTypeOfRequest(Request req);
	static Request retreiveRequest(Request req);
	static Request assemblyRequest(Request req);
};
#endif
