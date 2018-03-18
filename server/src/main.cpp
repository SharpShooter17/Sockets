#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "listener.hpp"
#include "const.hpp"
#include <iostream>
#include "connectionrefusedexception.hpp"
#include <pthread.h>
#include <memory>
#include "request.hpp"
#include "responseTime.hpp"
#include <string.h>
#include "protocol.hpp"
#include <time.h>


void* socket_handler(void* args)
{
	std::cout << "Socket handler" << std::endl;
	std::shared_ptr<Socket> client = *(std::shared_ptr<Socket>*)args;
	
	char* buffer = client->readBytes();
	Request req = *(Request*)buffer;
		
	req = Protocol::retreiveRequest(req);
	
	std::cout << "Request code: " << req.getRequestCode() << std::endl;

	if (req.getRequestCode() == 1)
	{
		ResponseTime response = ResponseTime();
		response.setRequestCode(10);
		response.setRequestId(req.getRequestId());
		int len = response.getlenght();
		dumpHex((void*)&response, sizeof(ResponseTime));
		Protocol::assemblyReponseTime(&response);
		dumpHex((void*)&response, sizeof(ResponseTime));
		client->writeBytes((char*)&response, sizeof(ResponseTime));
		//client->writeBytes(response.getTmestamp(), len);
	}
	
	delete buffer;
	client->closeSocket();
	
	return NULL;
}

int main()
{
	Listener listener(server_port, max_clients);
	listener.init();
	while(true)
	{	
		pthread_t current_thread;
	
		std::cout << "Server wait for client\n";
		std::shared_ptr<Socket> client = listener.acceptConnection();	
		pthread_create(&current_thread, NULL, socket_handler, &client);
		pthread_join(current_thread, NULL);	
	}
}
