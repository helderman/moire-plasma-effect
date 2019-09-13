# Prerequisites (Ubuntu):
# sudo apt-get install gcc libsdl2-dev libsdl2-image-dev

TARGET = demo
OBJS = plasma.o moire1.o moire2.o
CFLAGS = -I/usr/include/SDL2 -Wall -Wextra -pedantic
LDLIBS = -lSDL2 -lSDL2_image

$(TARGET): $(OBJS)
	$(CC) $^ $(LDLIBS) -o $@

%.o: ../html5/%.png
	ld -r -b binary -o $@ $<

clean:
	$(RM) $(TARGET) $(OBJS)
