#include"stdio.h"
#include "stdlib.h"

#include "redis_op.h"

int main(int argc,char* argv[])
{
	printf("command [ip] [port]\n");
	printf("Default [127.0.0.1] [6379]\n");
	redisContext* redis_context = NULL;
	char* ip = NULL;
	char* port = NULL;
	
	if(argc < 2)
	{
			ip = "127.0.0.1";
			port = "6379";
	}
	else if(argc == 2)
	{
			IP = argv[1];
			port = "6379";
	}
	else if(argc == 3)
	{
			IP = argv[1];
			port = argv[2];
	}
	else
	{
			printf("args err\ncommand [ip] [port]");
			return -1;
	}
	
	redis_context = rop_connectdb_nopwd(ip, port);
	if(redis_context == NULL)
	{
			
	}
	
	void rop_disconnect(redisContext* conn);
	
	return 0;
}