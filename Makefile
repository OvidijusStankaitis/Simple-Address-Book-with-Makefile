CFLAGS = -Wall -Wextra
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
BIN = addressBook

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN) $(OBJ)
