CC = g++
CFLAGS  = -g -Wall -std=c++11
INCLUDES = -I../common/include
LFLAGS = -L../common/src

SRCS = ../common/src/request.cpp ../common/src/responseTime.cpp main.cpp
OBJS = $(SRCS:.c=.o)
MAIN = serverApp

default: all

.PHONY: depend clean

all: 	$(MAIN)
	@echo Build successful

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
