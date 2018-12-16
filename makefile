CC = g++

DST_FILE = bin/converter

MAIN_FILE = src/converter.cpp
DEPENDENCIES = src/bmp.cpp src/dir.cpp src/threadproc.cpp

LIBS = -pthread

CFLAGS = 

SRC_FILES = $(MAIN_FILE) $(DEPENDENCIES)

all: $(DST_FILE) libbmp.so

$(DST_FILE) : $(SRC_FILES)
	mkdir -p bin
	$(CC) $(LIBS) -o $(DST_FILE) $(SRC_FILES) $(CFLAGS)

libbmp.so : src/libbmp.cpp
	mkdir -p bin
	$(CC) -shared -fPIC -o bin/libbmp.so src/libbmp.cpp src/bmp.cpp

clean:
	rm bin/*