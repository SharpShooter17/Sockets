#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

#include "socket.hpp"
#include "const.hpp"
#include <string.h>
#include <iostream>
#include "request.hpp"
#include "responseTime.hpp"
#include "protocol.hpp"


int main()
{
	std::cout << "TIME: " << sizeof(time_t) << " LONG INT: " << sizeof (unsigned long int) << " DOUBLE: " << sizeof(double)<< std::endl;
	Socket socket(AF_INET, server_port, inet_addr("127.0.0.1"));
	socket.connectToServer();
	
	Protocol::sendTimeRequest(socket);
	ResponseTime * t = (ResponseTime *)Protocol::getResponse(socket);
	printf("Time: %s\n", t->getTmestamp());
	std::cout << "len: " <<  t->getlenght() << " code: " << t->getRequestCode() << std::endl;

	socket.closeSocket();
	delete t;
	return 0;
}

