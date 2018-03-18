#include <stdint.h>
#include "endianness.hpp"

uint64_t Endianness::htond(double hostdouble) {
    char* data = (char*)&hostdouble;
    uint64_t result;
    char *dest = (char *)&result;
    if(!Endianness::is_big_endian()) {
        for (int i = 0; i < sizeof(double); i++)
            dest[i] = data[sizeof(double) - i - 1];
    } else {
        for (int i = 0; i < sizeof(double); i++)
            dest[i] = data[i];
    }
    return result;
}
double Endianness::ntohd(uint64_t netdouble) {
    char* data = (char*)&netdouble;
    double result;
    char *dest = (char *)&result;
    if(!Endianness::is_big_endian()) {
        for (int i = 0; i < sizeof(double); i++)
            dest[i] = data[sizeof(double) - i - 1];
    } else {
        for (int i = 0; i < sizeof(double); i++)
            dest[i] = data[i];
    }
    return result;
}

int Endianness::is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } e = { 0x01000000 };

    return e.c[0];
}
