# htgen

PROJ=hcgen
CC=gcc
CFLAGS=
LDFLAGS=

SRC = hcgen.c

all: $(PROJ)

$(PROJ): 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC)
	
clean:
	rm -f $(PROJ)
	

