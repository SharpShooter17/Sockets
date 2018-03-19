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
	Protocol::sendSqrtRequest(socket, 9);
	
	int requestsSended = 2;
	while (requestsSended != 0)
	{
		Request * r = (Request*)Protocol::getResponse(socket);
		dumpHex(r, sizeof(Request));
		if (r->getRequestCode() == 10) 
		{
			ResponseTime * time = (ResponseTime*)r;
			std::cout << "len: " <<  time->getlenght() << " code: " << time->getRequestCode() << " TIME: " << time->getTmestamp() <<std::endl;
			requestsSended--;
			delete[] (char*)time;
		}
		else if (r->getRequestCode() == 20)
		{
			SqrtRequest * sr = (SqrtRequest*)r;
			std::cout << "Pierwiastek z liczby 9 to: " << sr->getSqrt() << std::endl;
			requestsSended--;
			delete[] (char*)time;
		}
	}	

	socket.closeSocket();
	return 0;
}

