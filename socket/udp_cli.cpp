/*  基于udp协议的简单网络通信程序
 *  使用c++对udp socket进行封装
 */


#include<iostream>
#include<string>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

class UdpSocket
{
    private:
	int _sockfd;
    public:
	UdpSocket():_sockfd(-1){}
	bool Socket()
	{   
	    _sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	    if(_sockfd < 0)
	    {
		perror("socket error");
		return false;
	    }
	    return true;
	}
	bool Bind(std::string &ip,uint16_t port)
	{
	    sockaddr_in addr;
	    addr.sin_family = AF_INET;
	    addr.sin_port = htons(port);
	    addr.sin_addr.s_addr = inet_addr(ip.c_str());
	    socklen_t len = sizeof(sockaddr_in);
	    int ret = bind(_sockfd,(sockaddr*)&addr,len);
	    if(ret < 0)
	    {
		perror("bind error");
		return false;
	    }
	    return true;
	}
	ssize_t  Recv(char* buf, sockaddr_in *addr = NULL)
	{
	    sockaddr_in _addr;
	    ssize_t rlen;
	    socklen_t len = sizeof(sockaddr_in);
	    rlen = recvfrom(_sockfd,buf,1024,0,(sockaddr*)&_addr,&len);
	    if(rlen < 0)
	    {
		perror("recvfrom error");
		return -1;
	    }
	    if(addr)
	    {
		memcpy((void*)addr,(void*)&_addr,len);
	    }
	    return rlen;
	}
	bool Send(char *buf,size_t len,sockaddr_in &addr)
	{
	    int slen = 0;
	    slen = sendto(_sockfd,buf,len,0,(sockaddr*)&addr,sizeof(sockaddr));
	    if(slen < 0)
	    {
		perror("sendto error");
		return false;
	    }
	    return true;
	}
	bool Close()
	{
	    if(_sockfd >= 0)
	    {
		close(_sockfd);
		_sockfd = -1;
	    }
	    return true;
	}
};
#define CHECK_RET(q) if(q == false){return -1;}
int main()
{
    UdpSocket sock;
    CHECK_RET(sock.Socket());
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    addr.sin_addr.s_addr = inet_addr("192.168.208.130");
    //客户端程序是不需要手动绑定地址信息的，为防止绑定失败
    while(1)
    {
	char buff[1024] = {0};
	scanf("%s",buff);
	sock.Send(buff,strlen(buff),addr);
	printf("client say: %s\n",buff);
	memset(buff,0x00,1024);
	sock.Recv(buff);
	printf("server buff: %s\n",buff);
    }
    sock.Close();
    return 0;
}
