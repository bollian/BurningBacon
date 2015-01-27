flags = -std=c99 -L../lib -lBurningBacon
paths = -I/home/calcifer/Documents/code/BurningBacon/src
dir = bin

# the release option
all: $(dir) vector

clean:
	rm -rf $(dir)

rebuild: clean
	make all

debug: flags += -g
debug: dir = dbg
debug: all

#math: math.c
#	gcc math.c -o bin/math $(paths) $(flags)

vector: vector.c
	gcc vector.c -o $(dir)/vector $(paths) $(flags)

bin:
	mkdir bin