#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

int StringToInt(const char* string) {
    char *pointer;
    return strtol(string, &pointer, 10);
}

int main(int argc, char *argv[]) {
    if (argc != 6) { // Must be supplied 5 cl args 
        printf("Coordinator: Invalid number of args.  Exiting... \n");
	    exit(EXIT_FAILURE);
    }

    pid_t child_ID;
    pid_t process_IDs[4];
    int fd[2]; // File Descriptor -- 0 == Read, 1 == Write 
    int shared_memory_ID;
    int shared_memory_ID_array[4];
    int *shared_memory_pointer;

    for (int i = 2; i < argc; i++) {

        // Create Pipe
        pipe(fd); 

        child_ID = fork();

        if (child_ID == -1) { // Fork Error Handling
            perror("fork error");
	        exit(EXIT_FAILURE);
	    }

        if (child_ID == 0) { // If Child

            char fd_str[8]; // Convert file descriptor to string
            sprintf(fd_str, "%d", fd[0]); // Stores string fd[0] into buffer array
            execlp("./Checker", "Checker", argv[1], argv[i], fd_str, (char *) 0); // Passing args to Checker - divisor, dividend, and shared memory segment 
            exit(EXIT_SUCCESS);

        } else { // If Parent

            printf("Coordinator: forked process with ID %d.\n", child_ID);

            // Create Shared Memory Space
            shared_memory_ID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);

            // Store PID
            process_IDs[i - 2] = child_ID;

            // Stored Shared Memory Space ID
            shared_memory_ID_array[i - 2] = shared_memory_ID;

            close(fd[0]); // Closing Read end of pipe 
            write(fd[1], &shared_memory_ID, sizeof(shared_memory_ID)); // Write Shared Memory ID to pipe to send to Checker
            close(fd[1]); // Close Write end of pipe

            printf("Coordinator: wrote shm ID %d to pipe (4 bytes)\n", shared_memory_ID);
	    }
    }

    for (int i = 0; i < 4; i++) {
        printf("Coordinator: waiting on child process ID %d...\n", child_ID);
        waitpid(process_IDs[i], NULL, 0);

        // Pointer to Shared Memory Space
        shared_memory_pointer = (int*)shmat(shared_memory_ID_array[i], NULL, 0);

        if (*shared_memory_pointer == 1) {
            printf("Coordinator: result (1) read from shared memory: %d is divisible by %d.\n", StringToInt(argv[i + 2]), StringToInt(argv[1]));
        }
        else {
            printf("Coordinator: result (0) read from shared memory: %d is NOT divisible by %d.\n", StringToInt(argv[i + 2]), StringToInt(argv[1]));
        }   

        shmctl(shared_memory_ID_array[i], IPC_RMID, NULL); // Destroy shared memory
    }

    printf("Coordinator: exiting.\n");
    exit(EXIT_SUCCESS);
}


            
