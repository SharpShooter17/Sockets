CC = g++
CFLAGS  = -g -Wall -std=c++11 -pthread
INCLUDES = -I../common/include -I./include
LFLAGS = -L../common/src -L/src

SRCS = ../common/src/request.cpp ../common/src/responseTime.cpp ../common/src/socket.cpp  ../common/src/protocol.cpp src/main.cpp src/listener.cpp
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
