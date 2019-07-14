#pragma once

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "Log.hpp"

#define BACKLOG 5

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

};
