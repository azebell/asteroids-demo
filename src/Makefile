#Mark Gomes
#Makefile for Asteroids group project
#This Makefile compiles all the files in this project
# To use this Makefile, you type:
#
#        make
#                   
# A binary named [run] will be produced

CC = gcc
C++ = g++ 
LIBDIRS = -L/usr/lib64
INCDIRS = -I/usr/include
LDLIBS =  -lglut -lGL -lGLU -lX11 -lm

INCLUDES   = includes.h
HEADERS    = constants.h structs.h glFuncs.h clipoctagon.h asteroid.h
PROTOTYPES = prototypes.h
GLOBALS    = globals.h
OBJS 	   = glFuncs.o clipoctagon.o asteroid.o input.o gamemanager.o

all : run

run: main.o $(INCLUDES) $(HEADERS) $(PROTOTYPES) $(GLOBALS) $(OBJS) 
	$(C++) -o run main.o $(OBJS) $(INCDIRS) $(LIBDIRS) $(LDLIBS) 

glFuncs.o : glFuncs.cpp $(INCLUDES) $(HEADERS) $(PROTOTYPES) $(GLOBALS)
	$(C++) -c glFuncs.cpp

clipoctagon.o : clipoctagon.cpp $(INCLUDES) $(HEADERS) $(PROTOTYPES) $(GLOBALS)
	$(C++) -c clipoctagon.cpp

asteroid.o : asteroid.cpp $(INCLUDES) $(HEADERS) $(PROTOTYPES) $(GLOBALS)
	$(C++) -c asteroid.cpp

gamemanager.o : gamemanager.cpp $(INCLUDES) $(HEADERS) $(PROTOTYPES) $(GLOBALS)
	$(C++) -c gamemanager.cpp

input.o : input.cpp $(INCLUDES) $(HEADERS) $(GLOBALS)
	$(C++) -c input.cpp

main.o : main.cpp $(INCLUDES) $(HEADERS) $(PROTOTYPES) $(OBJS) 
	$(C++) -c main.cpp 

clean :
	rm *.o

pristine :
	rm *.o
	rm run
