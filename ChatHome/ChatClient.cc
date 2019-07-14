#include <iostream>
#include "ChatClient.hpp"

static void Usage(std::string proc)
{
	std::cout << "Usage: " << proc << " peer_ip " << std::endl;
}

static void menu(int &s)
{
	std::cout << "*************************" << endl;
	std::cout << "*****   1. Register *****" << endl;
	std::cout << "*************************" << endl;
	std::cout << "*****   2. Login    *****" << endl;
	std::cout << "*************************" << endl;
	std::cout << "*****   3. Exit     *****" << endl;
	std::cout << "*************************" << endl;
	std::cout << "Please Select:> " << endl;
	std::cin >> s;
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
	int select = 0;
	Menu(select);
	while(1)
	{
	switch(select)
	{
	    case 1://Register
	        cp->Register();
		break;
	    case 2://Login
	       if(cp->Login())
	       {
		       cp->Chat();
	       }
	       break;
	    case 3:
	       exit(0);
	       break;
	    default:
	       exit(1);
	       break;
	}
	}
	ChatClient *cp = new ChatClient(argv[1]);
	cp->InitClient();
	if(cp->ConnectServer())
	{
		std::cout << "Connect Success" << std::endl;
	}
}
