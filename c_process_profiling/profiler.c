#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct Process { // Comments indicates location
    int pid; // stat 0
    char executable_name[64]; // stat 1
    int ppid; // stat 3
    int pgrp; // stat 4
    char state; // stat 2
    double time_user_mode; // stat 13
    double time_kernal_mode; // stat 14
    long int virtual_memory; // statm 0
    int resident_pages; // statm 1
    int shared_pages; // statm 2
    short page_faults; // stat 11
};

int main(int argc, char *argv[]) {

    char *process_id;
    char file_path_stat[64];
    char file_path_statm[64];
    FILE *file_pointer;
    struct Process process;
    char buffer[256];
    char *token;

    if (argc != 2) {
        fprintf(stderr, "Incorrect number of args given.  Expected 1, got %d\n", argc - 1);
        exit(1);
    }

    process_id = argv[1];
    snprintf(file_path_stat, sizeof(file_path_stat), "/proc/%s/stat", process_id);
    snprintf(file_path_statm, sizeof(file_path_stat), "/proc/%s/statm", process_id);

    // Get contents of stat

    file_pointer = fopen(file_path_stat, "r");

    if (file_pointer == NULL) {
        fprintf(stderr, "file: 'stat' for given pid could not be opened -- process not active.");
        exit(2);
    }

    fgets(buffer, 256, file_pointer);
    token = strtok(buffer, " ");

    for (int i = 0; i < 15; i++) {

        switch(i) {
            case 0:
                process.pid = (int) atoi(token);
                break;
            case 1:
                strcpy(process.executable_name, token);
                break;
            case 2:
                process.state = *token;
                break;
            case 3:
                process.ppid = (int) atoi(token);
                break;
            case 4: 
                process.pgrp = (int) atoi(token);
                break;
            case 11:
                process.page_faults = (short) atoi(token);
                break;
            case 13:
                process.time_user_mode = (double) atoi(token) / sysconf(_SC_CLK_TCK);
                break;
            case 14:
                process.time_kernal_mode = (double) atoi(token) / sysconf(_SC_CLK_TCK);
                break;
        }
    
        token = strtok(NULL, " ");
    }

    // Get contents of statm

    file_pointer = fopen(file_path_statm, "r");

    if (file_pointer == NULL) {
        fprintf(stderr, "File: 'statm' for given pid could not be opened -- process not active");
        exit(2);
    }

    fgets(buffer, 256, file_pointer);
    token = strtok(buffer, " ");

    for (int i = 0; i < 3; i++) {

        switch (i) {
            case 0:
                process.virtual_memory = (long int) atoi(token);
                break;
            case 1: 
                process.resident_pages = (int) atoi(token);
                break;
            case 2: 
                process.shared_pages = (int) atoi(token);
                break;
        }

        token = strtok(NULL, " ");
    }

    fclose(file_pointer);

    // Print results

    printf("checking pid %d\n"
            "Executable:      %s\n"
            "ppid:            %d\n"
            "pgrp:            %d\n"
            "State:           %c\n"
            "User mode:       %.3f sec\n"
            "Kernal mode:     %.3f sec\n"
            "Virtual memory:  %ld bytes\n"
            "Resident pages:  %d\n"
            "Shared pages:    %d\n"
            "Page faults:     %d\n",
            process.pid, process.executable_name, process.ppid, process.pgrp, process.state,
            process.time_user_mode, process.time_kernal_mode, process.virtual_memory,
            process.resident_pages, process.shared_pages, process.page_faults);

    exit(0);
}