PROGRAM = main
CFLAGS = -I -Wall -g3
MODULES = ../modules
APPMOD = ./UserImpl
CC = gcc
OBJS = main.o

include $(MODULES)/Bitcoins.inc
include $(APPMOD)/make.inc

$(PROGRAM) : clean $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(PROGRAM)
clean :
	rm -rf $(PROGRAM) $(OBJS)
run : $(PROGRAM)
	./$(PROGRAM)
