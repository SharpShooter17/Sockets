#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#include <stdio.h>
#include <unistd.h>

#include <string>

class Socket 
{
	private:
		sockaddr_in m_address;
		int m_socket;
	public:
	Socket();
	Socket(short, unsigned short, std::string);
	~Socket();

	int getSocket();
	void setSocket(int);
	socklen_t getAddressLen();

	sockaddr_in const * getAddress();
	void setAdderss(sockaddr_in);	

	void connectToServer();
	void closeSocket();
	
	char* readBytes();
	void writeBytes(const char*, int);
};

#endif
