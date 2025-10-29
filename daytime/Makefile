CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = daytime_client
SOURCES = daytime_client.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) *.o

.PHONY: clean
