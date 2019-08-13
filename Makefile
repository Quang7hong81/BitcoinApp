PROGRAM = main
CFLAGS = -I -Wall -g3 -I./UserInterface
MODULES = ./modules
APPMOD = ./UserInterface/UserImpl
CC = gcc
OBJS = ./UserInterface/main.o

include $(MODULES)/Bitcoins.inc
include $(APPMOD)/make.inc

$(PROGRAM) : clean $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(PROGRAM)
clean :
	rm -rf $(PROGRAM) $(OBJS)
run : $(PROGRAM)
	./$(PROGRAM)
