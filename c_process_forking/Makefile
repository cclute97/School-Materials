CC = gcc
CFLAGS = -Wall -Wextra -g

SRC_CHECKER = Checker.c
SRC_COORDINATOR = Coordinator.c

EXEC_CHECKER = Checker
EXEC_COORDINATOR = Coordinator

all: $(EXEC_CHECKER) $(EXEC_COORDINATOR)

$(EXEC_CHECKER): $(SRC_CHECKER)
	$(CC) $(CFLAGS) $< -o $@

$(EXEC_COORDINATOR): $(SRC_COORDINATOR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXEC_CHECKER) $(EXEC_COORDINATOR)


