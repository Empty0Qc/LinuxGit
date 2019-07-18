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

	unsigned int id;
	std::string passwd;
	std::string nick_name;
	std::string school;
    public:
	ChatClient(std::string ip_):peer_ip(ip_)
	{
		id = 0;
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
	void Register()
	{
		if(Util::RegisterEnter(nick_name, school, passwd) && ConnectServer())
		{
			Request rq;
			rq.method = "REGISTER\n";
			
      Json::Value root;
      root["name"] = nick_name;
      root["school"] = school;
      root["passwd"] = passwd;

		  Util::Seralizer(root, rq.text);
      rq.content_length = "Content-Length: ";
      rq.content_length += Util::IntToString((rq.text).size());
      rq.content_length += "\n";
			SocketApi::Send(tcp_sock, rq);


		}
	}
	bool Login()
	{}
	void Chat()
	{}
	~ChatClient()
	{
	}
};
