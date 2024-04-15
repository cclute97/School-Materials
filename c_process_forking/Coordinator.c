#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Coordinator: Invalid number of args.  Exiting... \n");
	exit(EXIT_FAILURE);
    }

    for (int i = 2; i < argc; i++) {

	int status;
        pid_t childid = fork();

        if (childid == -1) {
            perror("fork error");
	    exit(EXIT_FAILURE);
	}

	if (childid == 0) {
	    execlp("./Checker", "Checker", argv[1], argv[i], (char *) 0);
	    exit(1);
	} else {
	    printf("Coordinator: forked process with ID %d.\n", childid);
            printf("Coordinator: waiting for process [%d].\n", childid);
            wait(&status);

	    if (WIFEXITED(status)) { // If child ended normally
                printf("Coordinator: child process %d returned %d.\n", childid, WEXITSTATUS(status));
	    }
	}
    }

    printf("Coordinator: exiting.\n");
    exit(EXIT_SUCCESS);
}
