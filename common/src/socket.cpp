#include "socket.hpp"
#include <string.h>
#include <iostream>
#include <errno.h>
#include <fcntl.h>

Socket::Socket()	
{
	bzero(&this->m_address, sizeof(this->m_address));
	this->m_socket = -1;
}

/**
* short family eg.: AF_INET
**/
Socket::Socket(int family, unsigned short port, long address)
{
	this->m_socket = socket( family, SOCK_STREAM, 0);
	if (this->m_socket < 0)
	{
		std::cerr << "socket() ERROR";
		this->closeSocket();
		exit(1);
	}

	this->m_address.sin_family = family;
	this->m_address.sin_port = htons(port);
	this->m_address.sin_addr.s_addr = address;	
	//inet_pton
	int opts = fcntl(this->m_socket, F_GETFL);
	opts = opts & (~O_NONBLOCK);
	fcntl(this->m_socket, F_SETFL, opts);

}

Socket::~Socket()
{
	this->closeSocket();
}

int Socket::getSocket()
{
	return this->m_socket;
}

void Socket::setSocket(int socket)
{
	this->m_socket = socket;
}

socklen_t Socket::getAddressLen()
{
	return sizeof(this->m_address);
}

sockaddr_in const * Socket::getAddress()
{
	return &m_address;
}

void Socket::setAdderss(sockaddr_in address)
{
	this->m_address = address;
}

void Socket::connectToServer()
{
	socklen_t len = sizeof(this->m_address);
	if (connect(this->m_socket, (struct sockaddr*) &m_address, len) < 0)
	{
		std::cerr << "connect() ERROR";
		exit(1);
	}
}

void Socket::closeSocket()
{
	shutdown(this->m_socket, 2);
	//close(this->m_socket);
}

char* Socket::readBytes()
{
	std::cout << "SOCKET: " << this->m_socket << std::endl;
	int size = 1024;
	char* results = new char[size];
	bzero(results, size);
	int bytes;
	bytes = recv(this->m_socket, results, size, 0);	
	std::cout << "Read bytes: " << bytes << std::endl;
	if (bytes < 0)
	{
		perror("readbytes() ERRNO: ");
		exit(1);
	}
	return results;
}

void Socket::writeBytes(const char * bytes, int size)
{
	int c;
	c = send(this->m_socket, bytes, size, 0);
	std::cout << "BYTES SEND: " << c << " socket: " << this->m_socket << std::endl;
}
