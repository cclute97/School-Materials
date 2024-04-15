CC=gcc
SRC_FILES=Driver.c MemoryManager.c
OBJ_FILES=$(SRC_FILES:.c=.o)
OUT_EXE=a.out

all: $(OUT_EXE)

$(OUT_EXE): $(OBJ_FILES)
	$(CC) -o $@ $(OBJ_FILES)

%.o: %.c
	$(CC) -c -o $@ $<

clean:
	rm -f *.o $(OUT_EXE)