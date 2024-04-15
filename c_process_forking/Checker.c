#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

bool IsDivisible(const int divisor, const int dividend) {
    if (dividend % divisor == 0) {
        return true;
    }
    return false;
}

int StringToInt(const char* string) {
    char *pointer;
    return strtol(string, &pointer, 10);
}

int main (int argc, char *argv[]) {
    if (argc != 3) {
        printf("Checker: Invalid number of args. Exiting... \n");
        exit(EXIT_FAILURE);
    }

    int divisor = StringToInt(argv[1]);
    int dividend = StringToInt(argv[2]);

    printf("Checker process [%d]: Starting. \n", getpid());

    if (IsDivisible(divisor, dividend)) {
        printf("Checker process [%d]: %d *IS* divisible by %d. \n", getpid(), dividend, divisor);
	printf("Checker process [%d]: Returning 1.\n", getpid());
	return 1;
    } else {
        printf("Checker process [%d]: %d *IS NOT* divisible by %d. \n", getpid(), dividend, divisor);
        printf("Checker process [%d]: Returning 0.\n", getpid());	
    }

    return 0;
}
