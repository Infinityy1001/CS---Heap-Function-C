CC=gcc
CFLAGS=-shared -fPIC
TARGET=lib_my_malloc.so
SOURCE=heap_lib.c
DEST=/usr/local/lib

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

install:
	sudo cp $(TARGET) $(DEST)
	sudo ldconfig

clean:
	rm -f $(TARGET)