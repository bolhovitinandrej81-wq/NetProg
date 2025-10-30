CC = gcc
CFLAGS = -Wall -Wextra -std=c99
CLIENT_TARGET = echo_client
SERVER_TARGET = echo_server
CLIENT_SOURCES = echo_client.c
SERVER_SOURCES = echo_server.c

all: $(CLIENT_TARGET)

$(CLIENT_TARGET): $(CLIENT_SOURCES)
	$(CC) $(CFLAGS) -o $(CLIENT_TARGET) $(CLIENT_SOURCES)

$(SERVER_TARGET): $(SERVER_SOURCES)
	$(CC) $(CFLAGS) -o $(SERVER_TARGET) $(SERVER_SOURCES)

clean:
	rm -f $(CLIENT_TARGET) $(SERVER_TARGET) *.o

.PHONY: clean all
