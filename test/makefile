flags = -std=c99 -L../lib -lBurningBacon
paths = -I/home/calcifer/Documents/code/BurningBacon/src
dir = bin
dbg = -g

# the release option
all: bin vector

clean:
	rm -rf bin
	make all

debug:
	$(eval flags += $(dbg))
	$(eval dir = dbg)
	make vector

#math: math.c
#	gcc math.c -o bin/math $(paths) $(flags)

vector: vector.c
	gcc vector.c -o $(dir)/vector $(paths) $(flags)

bin:
	mkdir bin