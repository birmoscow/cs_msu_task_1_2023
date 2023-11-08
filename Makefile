CC = cc
CFLAGS = -Wall -Werror
LD = -ldl
LDFLAGS = -rdynamic

.PHONY: all clean

all:
	$(CC) $(LDFLAGS) printrandom.c linear.c random.c $(CFLAGS) -o printrandom $(LD)

clean:
	$(RM) *~ *.o printrandom
