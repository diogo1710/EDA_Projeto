EXEC  = EDA_23795
CC = gcc
#replace 03 with -g to debug
CFLAGS= -c        \
    -g            \
    -W            \
    -Wall        \
    -pedantic
SRC    = $(wildcard *.c)
OBJ    = $(SRC:.c=.o)
LDFL    = #libs like math...

all: $(EXEC)

${EXEC}: $(OBJ)
    $(CC) -o $@ $^ $(LDFL)

%.o: %.c
    $(CC) -o $@ $< $(CFLAGS)

.PHONY: clean mrproper

clean:
    @rm -rf *.o

mrproper: clean
    @rm -rf $(EXEC)
