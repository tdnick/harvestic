CC=g++
CFLAGS= -std=c++17 -Wall -Wextra
CLIBS= -lpistache -ljsoncpp -lcrypto -lssl -lpthread
NAME=harvestic # name of executable

SRCS_CPP := $(wildcard ./*.cpp)
SRCS_HPP := $(wildcard ./*.hpp)
SRCS_O := $(SRCS:%.cpp=%)
	
compile: $(SRCS_CPP) $(SRCS_HPP)
	@$(CC) $(CFLAGS) $(SRCS_CPP) -o $(NAME) $(CLIBS)
	@echo "\nCompile finished"

run:
	./$(NAME)