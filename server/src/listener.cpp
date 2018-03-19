#include "listener.hpp"
#include <iostream>

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

#include "connectionrefusedexception.hpp"
#include <errno.h>

Listener::Listener(unsigned short port, unsigned int maxClients) :
	m_server_socket(AF_INET, port, htonl(INADDR_ANY)), 
	m_max_connections(maxClients)
{
}

void Listener::init()
{
	socklen_t len = this->m_server_socket.getAddressLen();
	if (bind (this->m_server_socket.getSocket(), (struct sockaddr *) m_server_socket.getAddress(), len) < 0)
	{
		std::cerr << "bind() ERROR" << " ERRNO: " << errno << std::endl;
		exit(1);
	}
	if (listen(this->m_server_socket.getSocket(), this->m_max_connections) < 0)
	{
		std::cerr << "listen() ERROR";
		exit(1);
	}
	signal (SIGCHLD, SIG_IGN);
}

std::shared_ptr<Socket> Listener::acceptConnection()
{
	std::shared_ptr<Socket> client(new Socket());
	socklen_t len = sizeof(client->getAddress());
	int soc = accept(this->m_server_socket.getSocket(), (struct sockaddr*)client->getAddress(), &len);
	
	if (soc < 0)
	{
		throw ConnectionRefusedException();
	}

	client->setSocket( soc );
	return client;
}
