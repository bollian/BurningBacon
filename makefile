# file paths
proj_dir = $(shell dirname $(abspath $(MAKEFILE_LIST)))
o_path = $(proj_dir)/obj
lib_path = $(proj_dir)/lib
src_path = $(proj_dir)/src

# compiler options
CC = clang
flags = -c -std=c99
#paths = -I/home/calcifer/Documents/code/C/BurningBacon/$(src_path)
paths = -I$(src_path)

all: $(lib_path) $(o_path) vector math system string
	ar -cvr $(lib_path)/libBurningBacon.a $(o_path)/*.o

clean:
	rm -rf $(o_path)
	rm -rf $(lib_path)

rebuild: clean
	make all

debug: flags += -g
debug: o_path = dbg
debug: all

math: $(src_path)/bbmath.h $(src_path)/bbmath.c
	$(CC) $(src_path)/bbmath.c -o $(o_path)/math.o $(flags) $(paths)

vector: $(src_path)/bbvector.c $(src_path)/bbvector.h
	$(CC) $(src_path)/bbvector.c -o $(o_path)/vector.o $(flags) $(paths)

system: $(src_path)/bbsystem.c $(src_path)/bbsystem.h
	$(CC) $(src_path)/bbsystem.c -o $(o_path)/system.o $(flags) $(paths)

string: $(src_path)/bbstring.c $(src_path)/bbstring.h
	$(CC) $(src_path)/bbstring.c -o $(o_path)/string.o $(flags) $(paths)

$(lib_path):
	mkdir $(lib_path)

$(o_path):
	mkdir $(o_path)
