#include "listener.hpp"
#include <iostream>

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

#include "connectionrefusedexception.hpp"
#include <errno.h>

Listener::Listener(unsigned short port, unsigned int maxClients) :
	m_server_socket(AF_INET, port, "127.0.0.1"), 
	m_max_connections(maxClients)
{
}

void Listener::init()
{
	socklen_t len = this->m_server_socket.getAddressLen();
	if (bind (this->m_server_socket.getSocket(), (struct sockaddr *) this->m_server_socket.getAddress(), len) < 0)
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

Socket Listener::acceptConnection()
{
	Socket socket;
	socklen_t len = this->m_server_socket.getAddressLen();
	int soc = accept(this->m_server_socket.getSocket(), (struct sockaddr*)socket.getAddress(), &len);
	
	if (soc < -1)
	{
		std::cerr << "accept() ERROR";
		exit(1);
	}
	
	socket.setSocket( soc );

	if (fork() == 0)
	{
		std::cout << "New client" << std::endl;
	}
	else 
	{
		close(socket.getSocket());
		throw ConnectionRefusedException();
	}
	return socket;
}
