# Prerequisites (Ubuntu):
# sudo apt-get install gcc libsdl1.2-dev libsdl-image1.2-dev

TARGET = demo
OBJS = plasma.o moire1.o moire2.o
CFLAGS = -I/usr/include/SDL -Wall -Wextra -pedantic
LDLIBS = -lSDL -lSDL_image

$(TARGET): $(OBJS)
	$(CC) $^ $(LDLIBS) -o $@

%.o: ../html5/%.png
	ld -r -b binary -o $@ $<

clean:
	$(RM) $(TARGET) $(OBJS)
