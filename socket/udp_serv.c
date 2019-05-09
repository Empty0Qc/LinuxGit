/*  基于udp协议的简单网络通信程序
 *
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>

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
    addr.sin_port = 9000;
    addr.sin_addr.s_addr = "192.168.122.135";
    socklen_t len = sizeof(struct sockaddr_in);
    int ret = bind(sockft,(struct sockaddr*)&addr,len);
    if(ret < 0)
    {
	perror("bind error");
	return -1;
    }
    //4858
    //3.接受数据
    //4.发送数据
    //5.关闭套接字
    return 0;
}
