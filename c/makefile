CFLAGS = -I/usr/include/SDL -Wall -Wextra

demo: plasma.o moire1.o moire2.o
	$(CC) $^ -lSDL -lSDL_image -o $@

%.o: ../html5/%.png
	objcopy --input binary --output elf32-i386 --binary-architecture i386 $< $@
