#pragma once

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "json/json.h"
#include "Log.hpp"

#define BACKLOG 5



class Util{
	static bool RegisterEnter(std::string &n_,std::string &s_, std::string &passwd)
	{
		std::cout << "Please Enter Nick Name : ";
		std::cin >> n_;
		std::cout << "Please Enter School : ";
		std::cin >> s_;
		std::cout << "Please Enter Passwd: ";
		std::cin >> passwd;
		std::string again;
		std::cout << "Please Enter Passwd Again: ";
		if(passwd == again)	
		{
			return true;
		}
		return false;
	}
  static void Seralizer(Json::Value &root,std::string outString)
  {
    Json::FastWriter w;
    outString = w.write(root);
  }
  static void UnSeralizer(std::string &inString,Json::Value &root)
  {
    Json::Reader r;
    r.parse(inString, root, false);
  }
};


class Request{
	public:
	    std::string method; //REGISTER, LOGIN, LOGOUT
	    std::string content_length; //"Content-Length: 89"
	    std::string blank;
	    std::string text;
	public:
	    Request()
        :blank('\n')
      {}
	    ~Request() {}
};
class SocketApi{
public:
    	static int Socket(int type)
    	{
	    int sock = socket(AF_INET, type, 0);
            if(sock < 0)	
	    {
		LOG("socket error!",ERROR);
		exit(2);
	    }
	}
	static void Bind(int sock, int port)
	{
	    struct sockaddr_in local;
            local.sin_family = AF_INET;
            local.sin_addr.s_addr = htonl(INADDR_ANY);
	    local.sin_port = htons(port);

	    if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
            {
		LOG("Bind error",ERROR);
		exit(3);		
            }	
	}
	static void Listen(int sock)
	{
	    if(listen(sock,BACKLOG) < 0)
	    {
	    	LOG("Listen error", ERROR);
		exit(4);
	    }
	}	
	static int Accept(int listen_sock, std::string &out_ip, int &out_port)
	{
	    struct sockaddr_in peer;
	    socklen_t len = sizeof(peer);  
	    int sock = accept(listen_sock,(struct sockaddr*)&peer, &len);
	    if(sock < 0 )
	    {
		LOG("Accept error",WARNING);
		return -1;
	    }
	    out_ip = inet_ntoa(peer.sin_addr);
	    out_port = htons(peer.sin_port);
	    return sock;
	}
	static bool Connect(const int &sock, std::string peer_ip, const int &port)
	{
		struct sockaddr_in peer;
		peer.sin_family = AF_INET;
		peer.sin_addr.s_addr = inet_addr(peer_ip.c_str());
		peer.sin_port = htons(port);

		if(connect(sock, (struct sockaddr*)&peer, sizeof(peer)) < 0){
			LOG("connect error",WARNING);
			return false;
		};
		return true;
	}

	static void Send(int sock,Request &rq)
	{
		std::string &m_ = rq.method;
		std::string &cl_ = rq.content_length;
		std::string &t_ = rq.text;
		std::string &b_ = rq.blank;
		send(sock, m_.c_str(),m_.size(),0);
		send(sock, cl_.c_str(),cl_.size(),0);
		send(sock, b_.c_str(),b_.size(),0);
		send(sock, t_.c_str(),t_.size(),0);
	}

};

