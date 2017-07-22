SRCS := $(wildcard *.c)
TARGETS := $(SRCS:.c=.out)
LFLAG := -L ../Library -lindexer
CFLAG := -I ../Include

all : ${TARGETS}

%.out : %.c
	gcc $^ ${LFLAG} ${CFLAG} -o $@

clean :
	rm ${TARGETS} 
	
