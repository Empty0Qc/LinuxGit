#pragma once

#include <iostream>
#include <string>
#include "ProtocolUtil.hpp"

#define TCP_PORT 8080
#define UDP_PORT 8888

class ChatClient{
    private:
	int tcp_sock;
	int udp_sock;
	std::string peer_ip;
    public:
	ChatClient(std::string ip_):peer_ip(ip_)
	{
		tcp_sock = -1;
		udp_sock = -1;
	}

	void InitClient()
	{
		tcp_sock = SocketApi::Socket(SOCK_STREAM);
		udp_sock = SocketApi::Socket(SOCK_DGRAM);
	}
	bool ConnectServer()
	{
		return SocketApi::Connect(tcp_sock, peer_ip, TCP_PORT);
	}
	~ChatClient()
	{
	}
};
