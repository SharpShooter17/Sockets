#include "listener.hpp"
#include "const.hpp"
#include <iostream>
#include <pthread.h>
#include "request.hpp"
#include "responseTime.hpp"
#include <string.h>
#include "protocol.hpp"
#include <cmath>


void* socket_handler(void* args)
{
	std::shared_ptr<Socket> client = *(std::shared_ptr<Socket>*)args;
	int requests = 2;
	while(requests != 0)
	{
		Request * r = (Request*)Protocol::getResponse(*client);

		if (r->getRequestCode() == 1)
		{			
			ResponseTime response = ResponseTime();
			response.setRequestCode(10);
			response.setRequestId(r->getRequestId());
			int len = response.getlenght();
			Protocol::assemblyReponseTime(&response);
			client->writeBytes((char*)&response, sizeof(ResponseTime));
			delete[] (char*)r;
			requests--;
		} 
		else if (r->getRequestCode() == 2)
		{
			SqrtRequest * sr = (SqrtRequest *)r;
			sr->setRequestCode(20);
			sr->setSqurt(std::sqrt(sr->getSqrt()));
			Protocol::assemblySqrtRequest(sr);
			client->writeBytes((char*)sr, sizeof(SqrtRequest));
			requests--;
			delete[] (char*)sr;
		}
	}
	
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
