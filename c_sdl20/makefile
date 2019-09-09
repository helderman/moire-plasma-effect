CFLAGS = -I/usr/include/SDL2 -Wall -Wextra -pedantic

demo: plasma.o moire1.o moire2.o
	$(CC) $^ -lSDL2 -lSDL2_image -o $@

%.o: ../html5/%.png
	ld -r -b binary -o $@ $<

clean:
	$(RM) -f demo *.o
