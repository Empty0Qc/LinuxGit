#include <iostream>
#include "ChatClient.hpp"

static void Usage(std::string proc)
{
	std::cout << "Usage: " << proc << " peer_ip " << std::endl;
}

// ./ChatClient ip
int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		Usage(argv[0]);
		exit(1);
	}
	ChatClient *cp = new ChatClient(argv[1]);
	cp->InitClient();
	if(cp->ConnectServer())
	{
		std::cout << "Connect Success" << std::endl;
	}
}
