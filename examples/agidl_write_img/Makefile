CC = gcc
AGIDL_INCLUDE_DIR = -I"$(abspath $(dir $(lastword $(MAKEFILE_LIST)))/../../include)"
AGIDL_LIB_DIR = -L"$(abspath $(dir $(lastword $(MAKEFILE_LIST)))/../../lib)"
CFLAGS = -Wall -O2 $(AGIDL_INCLUDE_DIR)
LDFLAGS = $(AGIDL_LIB_DIR) -lagidl
OBJS = agidl_write_img.o
TARGET = main

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
	
clean:
	rm -f $(OBJS) $(TARGET) *~