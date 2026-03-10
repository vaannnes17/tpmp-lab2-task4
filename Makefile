CC = gcc
CFLAGS = -Wall -Wextra -I./src -std=c99
TARGET_CREATE = program_create
TARGET_PROCESS = program_process
SRCDIR = src

SERVER_SRCS = $(SRCDIR)/pensioner.c
CLIENT_CREATE_SRCS = $(SRCDIR)/main_create.c
CLIENT_PROCESS_SRCS = $(SRCDIR)/main_process.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_CREATE_OBJS = $(CLIENT_CREATE_SRCS:.c=.o)
CLIENT_PROCESS_OBJS = $(CLIENT_PROCESS_SRCS:.c=.o)

all: $(TARGET_CREATE) $(TARGET_PROCESS)

$(TARGET_CREATE): $(SERVER_OBJS) $(CLIENT_CREATE_OBJS)
	$(CC) $^ -o $@

$(TARGET_PROCESS): $(SERVER_OBJS) $(CLIENT_PROCESS_OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SERVER_OBJS) $(CLIENT_CREATE_OBJS) $(CLIENT_PROCESS_OBJS)
	rm -f $(TARGET_CREATE) $(TARGET_PROCESS)
	rm -f data/*.txt

run_create: $(TARGET_CREATE)
	./$(TARGET_CREATE)

run_process: $(TARGET_PROCESS)
	./$(TARGET_PROCESS)

.PHONY: all clean run_create run_process
