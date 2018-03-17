#include "listener.hpp"
#include <iostream>

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

Listener::Listener(unsigned short port, unsigned int maxClients) :
	m_server_socket(AF_INET, port, "127.0.0.1"), 
	m_max_connections(maxClients)
{
}

void Listener::init()
{
	int len = sizeof (*m_server_socket.getAddress());
	bind (this->m_server_socket.getSocket(), (struct sockaddr *) this->m_server_socket.getAddress(), len);
	listen(this->m_server_socket.getSocket(), this->m_max_connections);
	signal (SIGCHLD, SIG_IGN);
}

void Listener::acceptConnection()
{
	Socket socket;
	socklen_t len = this->m_server_socket.getAddressLen();
	socket.setSocket( accept(this->m_server_socket.getSocket(), (struct sockaddr*)socket.getAddress(), &len) );

	if (fork() == 0)
	{
		this->m_clients.push_back(socket);
		std::cout << "New client" << std::endl;
	}
	else 
	{
		std::cerr << "Connection failied" << std::endl;
		close(socket.getSocket());
	}
}
