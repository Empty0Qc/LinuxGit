/*  基于udp协议的简单网络通信程序
 *
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
int main()
{
    //1.创建套接字
    //int socket(int domain, int type, int protocol);
    //domain: 地址域
    //	AF_INET
    //type: 套接字类型（）
    //	SOCK_STREAM 流式套接字，默认协议TCP
    //	SOCK_DGRAM  数据报套接字，默认协议UDP
    //protocol:	协议
    //	IPPROTO_TCP 6
    //	IPPROTO_UDP 17
    //	返回值:	成功返回socket描述符(非负整数)	失败:	-1
    int	sockft = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(socket < 0)
    {
	perror("socket error");
	return -1;
    }
    //2.为套接字绑定地址信息
    //int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
    //sockfd:	套接字描述符
    //addr:	地址信息
    //addrlen:	地址信息长度
    //成功: 0	失败: -1
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    //uint16_t htons(uint16_t hostshort);
    //	2个字节整形数据的主机字节序到网络字节序的转换
    //	判断其大小端，是否需要字节序的转换，需要则转换，不需要则返回
    addr.sin_port = htons(9000);
    //int_addr_t inet_addr(const char *cp);
    //	将点分十进制字符串ip地址转换为网络字节序ip地址
    addr.sin_addr.s_addr = inet_addr("192.168.208.130");
    //uint32_t htonl(uint32_t hostshort);
    //	4个字节整型数据的字节序到网络字节序的转换
    //addr.sin_addr.s_addr = htonl(0xc0a8d082);
    socklen_t len = sizeof(struct sockaddr_in);
    int ret = bind(sockft,(struct sockaddr*)&addr,len);
    if(ret < 0)
    {
	perror("bind error");
	return -1;
    }
    while(1)
    {
	//3.接受数据
	//ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,struct sockaddr *src_addr, socklen_t *addrlen);
	//sockfd:	套接字描述符
	//buf:	要接收的数据
	//len:	要接收的数据长度
	//flags:	0-默认阻塞
	//	MSG_PEEK    接收数据，但是并不将数据移出缓冲区
	//src_addr:	数据的源地址信息
	//addrlen:	源地址信息长度(输入输出复合型参数)
	//	返回值: 成功:实际接收到的数据长度   失败: -1
	char buff[1024] = {0};
	struct sockaddr_in cli_addr;
	recvfrom(sockft,buff,1023,0,(struct sockaddr*)&cli_addr,&len);
	printf("client say:%s\n",buff);
	//4.发送数据
	//ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,const struct sockaddr *dest_addr, socklen_t addrlen);
	//sockfd:	套接字描述符
	//buf:	要发送的数据
	//len:	要发送的数据长度
	//flags:	0-默认阻塞
	//dest_addr:要发送的对端地址（客户端地址信息）    
	//addrlen:地址信息长度
	//	返回值: 成功:实际发送的字节长度	失败: -1
	memset(buff,0x00,1024);
	scanf("%s",buff);
	sendto(sockft,buff,strlen(buff),0,(struct sockaddr*)&cli_addr,len);
	printf("server say:%s\n",buff);
    }
    //5.关闭套接字
    close(sockft);
    return 0;
}
