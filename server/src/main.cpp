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

void dumpHex(const void* data, unsigned int size) {
	char ascii[17];
	unsigned int i, j;
	ascii[16] = '\0';
	for (i = 0; i < size; ++i) {
		printf("%02X ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			printf(" ");
			if ((i+1) % 16 == 0) {
				printf("|  %s \n", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}

void* socket_handler(void* args)
{
	std::cout << "Socket handler" << std::endl;
	std::shared_ptr<Socket> client = *(std::shared_ptr<Socket>*)args;
	
	char* buffer = client->readBytes();
	Request req = *(Request*)buffer;
		
	req = Protocol::retreiveRequest(req);
	
	std::cout << "Request code: " << req.getRequestCode() << std::endl;
	
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
