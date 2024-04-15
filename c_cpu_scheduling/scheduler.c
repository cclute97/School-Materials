#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "queue.h"

#define MAXCHAR 64

void swap(struct Process *x, struct Process *y) {
    struct Process temp = *x;
    *x = *y;
    *y = temp;
}

void bubble_sort_by_arrival(struct Process processes[], const unsigned short num_rows) {
    int i, j;
    bool swapped;

    for (i = 0; i < num_rows - 1; i++) {
        swapped = false;
        for (j = 0; j < num_rows - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                swap(&processes[j], &processes[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false) {
            break;
        }
    }
}

void test_file_data_print(const struct Process processes[], const unsigned short num_rows) {
    for (int i = 0; i < num_rows; i++) {
        printf("%d\n", processes[i].pid);
        printf("%d\n", processes[i].arrival_time);
        printf("%d\n", processes[i].burst_duration);
        printf("%d\n", processes[i].priority);
        printf("\n");
    }
}

void fcfs(struct Process processes[], const unsigned short num_rows) { 
    double cumulative_turnaround = 0;
    double cumulative_waiting_time = 0;
    unsigned short completion_time = 0;
    
    bubble_sort_by_arrival(processes, num_rows);

    // For each process -- calculate turnaround time and waiting time

    for (int i = 0; i < num_rows; i++) {
        if (processes[i].arrival_time > completion_time) {
            completion_time += processes[i].burst_duration + (processes[i].arrival_time - completion_time);
        } else {
            completion_time += processes[i].burst_duration;
        }        
        cumulative_turnaround += completion_time - processes[i].arrival_time;
        cumulative_waiting_time += (completion_time - processes[i].arrival_time) - processes[i].burst_duration;
    }

    printf("--- FCFS ---\n");
    printf("Average Turnaround Time: %.3f\n", cumulative_turnaround / num_rows);
    printf("Average Waiting Time: %.3f\n", cumulative_waiting_time / num_rows);
    printf("Throughput: %.3f\n", (double) num_rows / completion_time);
}

void sjf(struct Process processes[], const unsigned short num_rows) { // Preemptive
    double cumulative_turnaround = 0;
    double cumulative_waiting_time = 0;
    int total_duration = 0;
    struct Process *current_job;

    int i, j; // i = our current time

    for (i = 0; i < num_rows; i++) {
        total_duration += processes[i].burst_duration;
    }

    heap_t *p_queue = (heap_t *)calloc(1, sizeof (heap_t));
    current_job = NULL;

    for (i = 0; i < total_duration; i++) { // Check for every unit of time
        if (p_queue->len != 0 && current_job == NULL) { // if queue not empty and no current job
            current_job = pop_by_duration(p_queue);
        }
        for (j = 0; j < num_rows; j++) { // check every process
            if (i == processes[j].arrival_time) { // if current time is a processes arrival time
                if (current_job == NULL) { // if no current job
                    current_job = &processes[j];
                } else if (current_job->remaining_duration > processes[j].burst_duration) { // if new job shorter than current job
                    push_by_duration(p_queue, current_job);
                    current_job = &processes[j];
                } else { // if new job equal to or longer than current job
                    push_by_duration(p_queue, &processes[j]);
                }
            }
        }
        if (current_job != NULL) {
            current_job->remaining_duration--;
        }
        if (current_job->remaining_duration == 0) { // if current job finished
            cumulative_turnaround += (i + 1) - current_job->arrival_time;
            cumulative_waiting_time += ((i + 1) - current_job->arrival_time) - current_job->burst_duration;
            current_job = NULL;
        }
    }

    printf("--- SJFP ---\n");
    printf("Average Turnaround Time: %.3f\n", cumulative_turnaround / num_rows);
    printf("Average Waiting Time: %.3f\n", cumulative_waiting_time / num_rows);
    printf("Throughput: %.3f\n", (double) num_rows / total_duration);

    free(p_queue);
}

void priority(struct Process processes[], const unsigned short num_rows) { // Preemptive
    double cumulative_turnaround = 0;
    double cumulative_waiting_time = 0;
    int total_duration = 0;
    struct Process *current_job;

    int i, j; // i = our current time

    for (i = 0; i < num_rows; i++) {
        total_duration += processes[i].burst_duration;
    }

    heap_t *p_queue = (heap_t *)calloc(1, sizeof (heap_t));
    current_job = NULL;

    for (i = 0; i < total_duration; i++) { // Check for every unit of time
        if (p_queue->len > 0 && current_job == NULL) { // if queue not empty and no current job
            current_job = pop_by_priority(p_queue); 
        }
        for (j = 0; j < num_rows; j++) { // check every process
            if (i == processes[j].arrival_time) { // if current time is a processes arrival time
                if (current_job == NULL) { // if no current job
                    current_job = &processes[j];
                } else if (current_job->priority > processes[j].priority) { // if new job higher priority
                    push_by_priority(p_queue, current_job);
                    current_job = &processes[j];
                } else { // if new job equal to greater priority than current job
                    push_by_priority(p_queue, &processes[j]);
                }
            }
        }
        if (current_job != NULL) {
            current_job->remaining_duration--;
        }

        if (current_job->remaining_duration == 0) { // if current job finished
            cumulative_turnaround += (i + 1) - current_job->arrival_time;
            cumulative_waiting_time += ((i + 1) - current_job->arrival_time) - current_job->burst_duration;
            current_job = NULL;
        }
    }

    printf("--- Priority ---\n");
    printf("Average Turnaround Time: %.3f\n", cumulative_turnaround / num_rows);
    printf("Average Waiting Time: %.3f\n", cumulative_waiting_time / num_rows);
    printf("Throughput: %.3f\n", (double) num_rows / total_duration);

    free(p_queue);
} 

int main(int argc, char *argv[]) { // Takes file_name as arg

    char *file_name;
    FILE *file_pointer;
    struct Process *processes; 
    char row[MAXCHAR];
    char *token;
    unsigned short num_rows;

    if (argc != 2) {
        fprintf(stderr, "Incorrect number of args given.  Expected 1, got %d\n", argc);
        exit(1);
    }

    /* Read CSV                                     /
    /  1. Open file                                 /
    /  2. Count rows                                /
    /  3. Allocate space for entries in array       /
    /  4. Store values into structs in array       */  

    file_name = argv[1];
    file_pointer = fopen(file_name, "r");

    if (file_pointer == NULL) {
        fprintf(stderr, "File could not be opened.");
        exit(2);
    }

    num_rows = 0;

    while (feof(file_pointer) != true) {
        fgets(row, MAXCHAR, file_pointer);
        num_rows++;
    }
    rewind(file_pointer);

    processes = (struct Process *) malloc(num_rows * sizeof(struct Process)); 

    for (int i = 0; i < num_rows; i++) {
        fgets(row, MAXCHAR, file_pointer);
        token = strtok(row, ",");

        for (int j = 0; j < 4; j++) {

            switch (j) {
                case 0:
                    processes[i].pid = (unsigned short) atoi(token);
                    break;
                case 1:
                    processes[i].arrival_time = (unsigned short) atoi(token);
                    break;
                case 2:
                    processes[i].burst_duration = (unsigned short) atoi(token);
                    processes[i].remaining_duration = (unsigned short) atoi(token);
                    break;
                case 3:
                    if (token[strlen(token) - 1] == '\n') {
                        token[strlen(token) - 1] = '\0';
                    }
                    processes[i].priority = (unsigned short) atoi(token);
                    break;
            }

            token = strtok(NULL, ",");    
        }   
    }

    /* Call CPU Scheduling Algorithms       /
    /  1. First Come First Serve (FCFS)     /
    /  2. Shortest Job First (SJF)          /
    /  3. Priority Scheduling              */

    fcfs(processes, num_rows);
    sjf(processes, num_rows);

    // Reset remaining durations
    for (int i = 0; i < num_rows; i++) {
        processes[i].remaining_duration = processes[i].burst_duration;
    }

    priority(processes, num_rows);

    // Clean Up Resources // 

    fclose(file_pointer);
    free(processes);
    exit(0);
}