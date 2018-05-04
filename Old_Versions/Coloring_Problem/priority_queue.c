#include <stdio.h>

#include <stdlib.h>
#include <time.h>
 

typedef struct heapNode {

    int value;

} heapNode;

 

typedef struct Priority_Queue {

    heapNode* heap;

    int size;

} Priority_Queue;

 

void insert(heapNode aNode, heapNode* heap, int size) {

    int idx;

    heapNode tmp;

    idx = size + 1;

    heap[idx] = aNode;

    while (heap[idx].value < heap[idx/2].value && idx >= 1) {

        tmp = heap[idx];

        heap[idx] = heap[idx/2];

        heap[idx/2] = tmp;

        idx /= 2;

    }

}

 

void shiftdown(heapNode* heap, int size, int idx) {

    int cidx;        //index for child

    heapNode tmp;

    for (;;) {

        cidx = idx*2;

        if (cidx > size) {

            break;   //it has no child

        }

        if (cidx < size) {

            if (heap[cidx].value > heap[cidx+1].value) {

                ++cidx;

            }

        }

        //swap if necessary

        if (heap[cidx].value < heap[idx].value) {

            tmp = heap[cidx];

            heap[cidx] = heap[idx];

            heap[idx] = tmp;

            idx = cidx;

        } else {

            break;

        }

    }

}

 

heapNode removeMin(heapNode* heap, int size) {

    int cidx;

    heapNode rv = heap[0];

    //printf("%d:%d:%dn", size, heap[1].value, heap[size].value);

    heap[0] = heap[size];
    --size;

    shiftdown(heap, size, 0);

    return rv;

}

void enqueue(heapNode node, Priority_Queue *q) {

    insert(node, q->heap, q->size);

    ++(q)->size;

}

 

heapNode dequeue(Priority_Queue *q) {

   heapNode rv = removeMin(q->heap, q->size);

   --(q)->size;

   return rv; 

}

 

void initQueue(Priority_Queue *q, int n) {

   q->size = 0;

   q->heap = (heapNode*)malloc(sizeof(heapNode)*(n));

}

 

int main(int argc, char **argv) {

    int n; 

    int i;

    Priority_Queue q;

    heapNode hn;
    if(argc<2){
      printf("Must enter how many elements\n");
      exit(0);
    }
    n = atoi(argv[1]);

    initQueue(&q, n);

    srand(time(NULL));

    for (i = 0; i < n; ++i) {

        hn.value = rand()%20;

        printf("enqueue node with value: %d\n", hn.value);

        enqueue(hn, &q);

    }

    for (int i = 0; i <= q.size; ++i)
    {
        printf("%d ",q.heap[i].value);
    }
    printf("\n");

    printf("ndequeue all values:\n");

    for (i = 0; i < n; ++i) {

        hn = dequeue(&q);

        printf("dequeued node with value: %d, queue size after removal: %d\n", hn.value, q.size);

    }

}