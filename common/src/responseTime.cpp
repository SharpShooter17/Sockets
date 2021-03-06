#include "responseTime.hpp"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

ResponseTime::ResponseTime() : Request()
{
	time_t     now;
    struct tm  ts;
    time(&now);
    ts = *localtime(&now);
    strftime(this->m_timestamp, sizeof(this->m_timestamp), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    this->m_lenght = strlen(this->m_timestamp);
}
char* ResponseTime::getTmestamp()
{
	return this->m_timestamp;
}

void ResponseTime::setLenght(unsigned int len)
{
	this->m_lenght;
}

unsigned long int ResponseTime::getlenght()
{
	return this->m_lenght;
}

ResponseTime::~ResponseTime()
{
}
/*

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
*/
