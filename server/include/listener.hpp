#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "socket.hpp"

#include <signal.h>
#include <memory>

class Listener
{
	private:
	Socket m_server_socket;
	const unsigned int m_max_connections;

	public:
	Listener(unsigned short, unsigned int);

	void init();
	std::shared_ptr<Socket> acceptConnection();
};

#endif
