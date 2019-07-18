ser:server.cpp 
	g++ -std=c++11 $^ -o $@ -lpthread -L /usr/local/lib -lboost_filesystem -lboost_system
server:test_server.cpp
	g++ -std=c++11 $^ -o $@ -lpthread -g
.PHONY:clean
clean:
	rm server
