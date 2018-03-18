#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

#include "socket.hpp"
#include "const.hpp"
#include <string.h>
#include <iostream>
#include "request.hpp"
#include "responseTime.hpp"
#include "protocol.hpp"

void dumpHex(const void* data, unsigned int size) {
	char ascii[17];
	unsigned int i, j;
	ascii[16] = '\0';
	for (i = 0; i < size; ++i) {
		printf("%02X ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			printf(" ");
			if ((i+1) % 16 == 0) {
				printf("|  %s \n", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}

int main()
{
	Socket socket(AF_INET, server_port, inet_addr("127.0.0.1"));
	socket.connectToServer();

	Request time(1);
	time = Protocol::assemblyRequest(time);
	socket.writeBytes((char*)&time, sizeof(time));
	
	socket.closeSocket();
	return 0;
}

