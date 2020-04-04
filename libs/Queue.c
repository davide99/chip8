#include "Queue.h"
#include <stdlib.h>

typedef struct Node *Link;

struct Node {
    void *item;
    Link next;
};

struct Queue_s {
    Link head, tail;
};

Queue queueInit() {
    Queue queue;

    queue = malloc(sizeof(struct Queue_s));

    queue->head->item = NULL;
    queue->head->next
}