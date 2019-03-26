NAME = program1 program2 program3
CC = g++
CFLAG = -Wall -Wextra -DDEBUG -g -pedantic -std=c++14 
OPTION = $(CFLAG) -c

all: $(NAME)


program1.o: program1.cpp
	$(CC) $(OPTION) program1.cpp -o program1.o

program2.o: program2.cpp
	$(CC) $(OPTION) program2.cpp -o program2.o

program3.o: program3.cpp
	$(CC) $(OPTION) program3.cpp -o program3.o

clean:
	rm *.o $(NAME)

fullRun:
	./program1 filex.txt filey.txt output1.txt
	./program2 filex.txt filey.txt output2.txt
	./program3 filex.txt filey.txt output3.txt

checkmem: all
	valgrind ./$(NAME)
