all: tcp_sev tcp_cli
tcp_sev:tcp_sev.cpp
	g++ $^ -o $@ -pthread
tcp_cli:tcp_cli.cpp
	g++ $^ -o $@ 
udp_serv:udp_serv.c
	gcc $^ -o $@
udp_cli:udp_cli.cpp
	g++ $^ -o $@
