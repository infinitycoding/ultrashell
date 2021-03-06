SRCS = $(shell find -name '*.c')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

L_CFLAGS = -m32 -Wall -fno-stack-protector -fno-builtin -nostdinc -I ../../libs/mercury/include -I include
L_LDFLAGS = -muniverse_i386 -flto -T ../link.ld

ultrashell: ../../libs/mercury/crt/crt0.o $(OBJS) ../../libs/mercury/libc.a
	@$(LD) $(L_LDFLAGS) -o $@ $^
	cp ultrashell $(PREFIX)/ultrashell

host: 
	gcc -I include -o ultrashell $(SRCS)

%.o: %.c
	@$(CC) $(L_CFLAGS) -c -o $@ $^

clean:
	@rm $(OBJS) -f
	@rm ultrashell -f

.PHONY: clean




