#include <stdio.h>
#include <stdlib.h>

#include "process.h"

typedef struct {
    struct Process *nodes;
    int len;
    int size;
} heap_t;

void push_by_duration(heap_t *h, struct Process *data) {
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = (struct Process *)realloc(h->nodes, h->size * sizeof (struct Process));
    }
    int i = h->len + 1;
    int j = i / 2;
    while ((i > 1 && h->nodes[j].remaining_duration > data->remaining_duration) || (h->nodes[j].remaining_duration == data->remaining_duration && h->nodes[j].pid > data->pid)) {
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }
    h->nodes[i] = *data;
    h->len++;
}

struct Process *pop_by_duration(heap_t *h) {
    int i, j, k;
    if (!h->len) {
        return NULL;
    }
    struct Process temp = h->nodes[1];
    struct Process *data = &temp;
    
    h->nodes[1] = h->nodes[h->len];
    
    h->len--;
    
    i = 1;
    while (i!=h->len+1) {
        k = h->len+1;
        j = 2 * i;
        if (j <= h->len && h->nodes[j].remaining_duration < h->nodes[k].remaining_duration) {
            k = j;
        }
        if (j + 1 <= h->len && h->nodes[j + 1].remaining_duration < h->nodes[k].remaining_duration) {
            k = j + 1;
        }
        h->nodes[i] = h->nodes[k];
        i = k;
    }
    return data;
}

void push_by_priority(heap_t *h, struct Process *data) {
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = (struct Process *)realloc(h->nodes, h->size * sizeof (struct Process));
    }
    int i = h->len + 1;
    int j = i / 2;
    while ((i > 1 && h->nodes[j].priority > data->priority) || (h->nodes[j].priority == data->priority && h->nodes[j].pid > data->pid)) {
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }
    h->nodes[i] = *data;
    h->len++;
}

struct Process *pop_by_priority(heap_t *h) {
    int i, j, k;
    if (!h->len) {
        return NULL;
    }

    struct Process temp = h->nodes[1];
    struct Process *data = &temp;
    
    h->nodes[1] = h->nodes[h->len];
    
    h->len--;
    
    i = 1;
    while (i != h->len + 1) {
        k = h->len + 1;
        j = 2 * i;
        if (j <= h->len && h->nodes[j].priority < h->nodes[k].priority) {
            k = j;
        }
        if (j + 1 <= h->len && h->nodes[j + 1].priority < h->nodes[k].priority) {
            k = j + 1;
        }
        h->nodes[i] = h->nodes[k];
        i = k;
    }
    return data;
}

void test_priority_queue(struct Process processes[], const unsigned short num_rows) {
    heap_t *p_queue = (heap_t *)calloc(1, sizeof (heap_t));

    printf("\n");
    for (int i = 0; i < num_rows; i++) {
        printf("pushing process %d to queue\n", processes[i].pid);
        push_by_priority(p_queue, &processes[i]);
        printf("queue length = %d, size = %d\n", p_queue->len, p_queue->size);
    }

    printf("\n");
    for (int i = 0; i < num_rows + 1; i++) {
        printf("process at index %d = %d\n", i, p_queue->nodes[i].pid);
    }

    printf("\n");
    for (int i = 0; i < num_rows; i++) {
        struct Process *current = pop_by_priority(p_queue);
        printf("popping from queue: %d\n", current->pid);
        printf("queue length = %d, size = %d\n", p_queue->len, p_queue->size);
    }

    free(p_queue);
}