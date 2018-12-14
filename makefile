CC = g++

DST_FILE = bin/converter

MAIN_FILE = src/converter.cpp
DEPENDENCIES = src/bmp.cpp src/dir.cpp src/threadproc.cpp

LIBS = -pthread

CFLAGS = #-m32

SRC_FILES = $(MAIN_FILE) $(DEPENDENCIES)

$(DST_FILE) : $(SRC_FILES)
	mkdir -p bin
	$(CC) $(LIBS) -o $(DST_FILE) $(SRC_FILES) $(CFLAGS)

clean:
	rm bin/*