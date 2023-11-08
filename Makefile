CC = cc
CFLAGS = -Wall -Werror
LD = cc
LDFLAGS = -rdynamic

.PHONY: all clean

all: printrandom.o linear.o random.o
	$(CC) $(CFLAGS) -rdynamic  printrandom.o linear.o random.o -o printrandom -ldl

printrandom.o:
	$(LD) $(LDFLAGS) -rdynamic printrandom.c -c

linear.o:
	$(LD) $(LDFLAGS) -rdynamic linear.c -c

random.o:
	$(LD) $(LDFLAGS) -rdynamic random.c -c

clean:
	$(RM) *~ *.o printrandom
