#####################################################
# File Name	: make.sh
# Finction	:
# Auther	: 编程改变世界!
# mail		: 1477963911@qq.com 
# Created Time: 2016年10月21日 星期五 01时04分54秒
##################################################

.PHONY:clean all
WORKDIR=.
CC = gcc
VPATH = ./src ./test
CFLAGS = -Wall -g -I$(WORKDIR)/include/

BIN = fdfs_client_test main

all:$(BIN)

fdfs_client_test:make_log.o fdfs_client_test.o
	$(CC) -lpthread  $^ -o $@

main:make_log.o main.o
	$(CC) -lpthread  $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
