#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/shm.h>
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
    if (argc != 4) { // Must be supplied 3 cl args
        printf("Checker: Invalid number of args. Exiting... \n");
        exit(EXIT_FAILURE);
    }

    printf("Checker process [%d]: starting. \n", getpid());

    int divisor = StringToInt(argv[1]);
    int dividend = StringToInt(argv[2]);

    int pipe_read_fd = atoi(argv[3]); // Reading in our Shared Memory Segment -- arg to int
    int shared_memory_seg_ID; 
    read(pipe_read_fd, &shared_memory_seg_ID, sizeof(shared_memory_seg_ID));

    int *shared_memory_seg_pointer = (int*)shmat(shared_memory_seg_ID, NULL, 0); // Allows this process to access our shared memory space - attaches to shared memory

    printf("Checker process [%d]: read 4 bytes containing shm ID %d\n", getpid(), shared_memory_seg_ID);

    if (IsDivisible(divisor, dividend)) {
        printf("Checker process [%d]: %d *IS* divisible by %d. \n", getpid(), dividend, divisor);
        *shared_memory_seg_pointer = 1;
	    printf("Checker process [%d]: wrote result (1) to shared memory.\n", getpid());
    } else {
        printf("Checker process [%d]: %d *IS NOT* divisible by %d. \n", getpid(), dividend, divisor);
        *shared_memory_seg_pointer = 0;	
        printf("Checker process [%d]: wrote result (0) to shared memory.\n", getpid());
    }

    // Detach from Shared Memory
    shmdt(shared_memory_seg_pointer);

    return 0;
}
