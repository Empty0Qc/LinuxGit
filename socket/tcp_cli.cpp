#include "tcp_com.h"

class TcpClient
{
    private:
	TcpSocket sock;
    public:
	bool Start(std::string &ip,uint16_t port)
	{
	    CHECK_RET(sock.Socket());
	    CHECK_RET(sock.Connect(ip,port));
	    while(1)
	    {
		char buff[1024] = {0};
		scanf("%s",buff);
		sock.Send(buff,strlen(buff));
		memset(buff,0x00,1024);
		sock.Recv(buff,1023);
		printf("server say:%s\n",buff);
	    }
	    CHECK_RET(sock.Close());
	    return true;   
	}
};

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
	printf("usage: ./tcp_cli ip port\n");
	return -1;
    }
    uint16_t port = atoi(argv[2]);
    std::string ip = argv[1];
    TcpClient client;
    client.Start(ip,port);
    return 0;
}

