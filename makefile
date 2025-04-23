# Numele fișierului executabil
EXEC = tema1

# Compilatorul folosit
CC = gcc

# Flag-uri de compilare (poți adăuga -Wall pentru warnings)
CFLAGS = -g -Wall -Wextra -g -std=c11


# Target implicit
all: $(EXEC)

# Cum se compilează programul
$(EXEC): main.c
	$(CC) $(CFLAGS) -o $(EXEC) main.c

# Curățare fișiere generate
clean:
	rm -f $(EXEC)
