CC = gcc -Wall -O0
MAIN = test

SRCS = main.c quaternion.c rutinas_clock.c

DEPS = quaternion.h rutinas_clock.h

OBJS = $(SRCS:.c=.o)

$(MAIN): $(OBJS)
	rm -f $(MAIN)
	rm -rf objects/
	$(CC) -o $(MAIN) $(OBJS)
	mkdir objects/
	mv *.o objects/

%.o: %.c $(DEPS)
	$(CC) -c $< 

clean:
	rm -f $(MAIN)
	rm -rf objects/
