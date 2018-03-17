#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "socket.hpp"

#include <signal.h>
#include <vector>

class Listener
{
	private:
	Socket m_server_socket;
	std::vector<Socket> m_clients;
	const unsigned int m_max_connections;

	public:
	Listener(unsigned short, unsigned int);

	void init();
	void acceptConnection();
};

#endif
