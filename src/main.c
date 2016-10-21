/*********************************************************
>File Name	: main.c
>Finction	:
>Auther		: 编程改变世界!
> mail		: 1477963911@qq.com 
>Created Time: 2016年10月21日 星期五 03时27分02秒
********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"make_log.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		printf("缺少参数:command file\n");
	}
	char* logs = "logs";
	int pipefd[2] = {0};
	char buf[1024] = {0};
	int ret = pipe(pipefd);
	if(ret != 0)
	{
		LOG("main()",logs, "func pipe() err");
		return ret;
	}

	int pid = fork();
	if(pid == 0)
	{
		close(pipefd[0]);
		int fd = open(argv[1],"S_IRUSR");
		if(fd == -1)
		{
			LOG("子进程",logs, "func open() err");
			return -1;
		}

		while(1)
		{
			int n = read(fd,buf,1024);
			if(n == -1)
			{
				 LOG("子进程",logs,__LINE__ ,"func read() err");
				 return -1;
			}
			if(n == 0)
			{
				break;
			}

			write(pipefd[1],buf,n);
		}
	}
	else
	{
		close(pipefd[1]);
		while(1)
		{
			int n = read(pipefd[0],buf,1024);
			if(n == 0)
			{
				break;
			}
			write(stdout,buf,n);
		}
	}

	return 0;
}
