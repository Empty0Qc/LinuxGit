#include <iostream>
#include "ChatServer.hpp"

static void Usage(std::string proc)
{
	std::cout << "Usage: " << proc << " tcp_port udp_port" << std::endl;
}
// ./ChatServer tcp_port:处理注册登录和注销的  udp_port:进行通信
int main(int argc, char *argv[])
{
	//argc != 3 正确传参
	if(argc != 3)
	{
		Usage(argv[0]);
		exit(1);
	}

	int tcp_port = atoi(argv[1]);
	int udp_port = atoi(argv[2]);

	ChatServer *sp = new ChatServer(tcp_port, udp_port);
	sp->InitServer();
	sp->Start();
    	return 0;
}
