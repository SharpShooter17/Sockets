#include "socket.hpp"
#include "const.hpp"
#include <string.h>
#include <iostream>
#include "request.hpp"
#include "responseTime.hpp"
#include "protocol.hpp"

int main()
{
	Socket socket(AF_INET, server_port, inet_addr("127.0.0.1"));
	socket.connectToServer();
	
	Protocol::sendTimeRequest(socket);
	Protocol::sendSqrtRequest(socket, 9);
	
	int requestsSended = 2;
	while (requestsSended != 0)
	{
		Request * r = (Request*)Protocol::getResponse(socket);

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
			delete[] (char*)sr;
		}
	}	

	socket.closeSocket();
	return 0;
}

