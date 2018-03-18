#include "socket.hpp"
#include <string.h>
#include <iostream>
#include <errno.h>

Socket::Socket()	
{
	bzero(&this->m_address, sizeof(this->m_address));
	this->m_socket = -1;
}

/**
* short family eg.: AF_INET
**/
Socket::Socket(short family, unsigned short port, std::string address)
{
	this->m_address.sin_family = family;
	this->m_address.sin_port = htons(port);
	this->m_address.sin_addr.s_addr = inet_addr(address.c_str());
		
	this->m_socket = socket( family, SOCK_STREAM, 0);
	if (this->m_socket < 0)
	{
		std::cerr << "socket() ERROR";
		exit(1);
	}
	//bind(this->m_socket, (struct sockaddr*) &this->m_address, len);
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
	return &this->m_address;
}

void Socket::setAdderss(sockaddr_in address)
{
	this->m_address = address;
}

void Socket::connectToServer()
{
	socklen_t len = sizeof(this->m_address);
	if (connect(this->m_socket, (struct sockaddr*) &this->m_address, len) == -1)
	{
		std::cerr << "connect() ERROR";
		exit(1);
	}
}

void Socket::closeSocket()
{
	close(this->m_socket);
}

char* Socket::readBytes()
{
	int size = 1024;
	char*  results = new char[size];
	bzero(results, size);
	int bytes;
	bytes = recv(this->m_socket, results, size, 0);	
	std::cout << "Readed bytes: " << bytes << std::endl;
	if (bytes < 0)
	{
		std::cerr << "ERRNO: " << errno;
		exit(1);
	}
	return results;
}

void Socket::writeBytes(const char* bytes, int size)
{
	send(this->m_socket, bytes, size, 0);
}
