CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 #options gcc
LDLIBS  = -lcrypto	#liste des options librairie pour gcc

SRCS    = src/main.c src/mode_g.c src/mode_l.c src/binary_tree.c #liste des fichiers source à compiler
OBJS    = $(SRCS:.c=.o)

all: t3c

t3c: $(OBJS)
	$(CC) $(CFLAGS) -o t3c $(OBJS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f t3c $(OBJS)

.PHONY: all clean

#gcc -Wall -Wextra -std=c11  -c src/mode_g.c -o src/mode_g.o
#gcc -Wall -Wextra -std=c11  -c src/mode_l.c -o src/mode_l.o
#gcc -Wall -Wextra -std=c11  -o t3c src/main.o src/mode_g.o src/mode_l.o -lcrypto