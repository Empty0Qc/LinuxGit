cc=g++
server=ChatServer
client=ChatClient
LDFLAGS=-lpthread

.PHONY:all
all:$(server) $(client)

$(server):ChatServer.cc
	$(cc) -o -std=c++11 $@ $^ $(LDFLAGS)
$(client):ChatClient.cc
	$(cc) -o $@ $^

.PHONY:clean
clean:
	rm -f $(server) $(client)
