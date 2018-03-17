#include "socket.hpp"

Socket::Socket()	
{
}

/**
* short family eg.: AF_INET
**/
Socket::Socket(short family, unsigned short port, std::string address)
{
	this->m_address.sin_family = family;
	this->m_address.sin_port = htons(port);
	inet_pton(family, address.c_str(), &this->m_address.sin_addr);
	this->m_socket = socket( family, SOCK_STREAM, 0);
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
	connect(this->m_socket, (struct sockaddr*) &this->m_address, len);
}

void Socket::closeSocket()
{
	close(this->m_socket);
}
