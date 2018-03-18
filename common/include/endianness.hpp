#ifndef SOCKETS_ENDIANNESS_H
#define SOCKETS_ENDIANNESS_H

#include <stdint.h>

class Endianness
{
	public:
	static uint64_t htond(double);
	static double ntohd(uint64_t);
	private:
	static int is_big_endian();
};


#endif
