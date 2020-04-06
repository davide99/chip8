#include "KBQueue.h"
#include <stdlib.h>

typedef struct Node *Link;

struct Node {
    uint8_t c;
    Link next, prev;
};

struct KBQueue_s {
    Link head, tail;
};

KBQueue kbQueueInit() {
    KBQueue kbQueue;

    kbQueue = malloc(sizeof(struct KBQueue_s));
    kbQueue->tail = malloc(sizeof(struct Node));
    kbQueue->head = malloc(sizeof(struct Node));

    kbQueue->tail->c = 0;
    kbQueue->tail->next = NULL;
    kbQueue->head->c = 0;
    kbQueue->head->prev = NULL;
    kbQueue->head->next = kbQueue->tail;
    kbQueue->tail->prev = kbQueue->head;

    return kbQueue;
}

int kbQueueIsEmpty(KBQueue queue) {
    return queue->head->next == queue->tail;
}

void kbQueueEnqueue(KBQueue kbQueue, uint8_t c) {
    Link l;

    l = malloc(sizeof(struct Node));

    l->c = c;
    l->next = kbQueue->head->next;
    l->prev = kbQueue->head;
    kbQueue->head->next = l;
    l->next->prev = l;
}

uint8_t kbQueueDequeue(KBQueue kbQueue) {
    struct Node node = {.c=255};

    if (!kbQueueIsEmpty(kbQueue)) {
        node = *kbQueue->tail->prev;
        free(kbQueue->tail->prev);

        kbQueue->tail->prev = node.prev;
        kbQueue->tail->prev->next = kbQueue->tail;
    }

    return node.c;
}

void kbQueueFree(KBQueue kbQueue) {
    Link l;

    if (kbQueueIsEmpty(kbQueue))
        return;

    for (l = kbQueue->head->next; l != kbQueue->tail; l = l->next)
        free(l);

    free(kbQueue->head);
    free(kbQueue->tail);
    free(kbQueue);
}