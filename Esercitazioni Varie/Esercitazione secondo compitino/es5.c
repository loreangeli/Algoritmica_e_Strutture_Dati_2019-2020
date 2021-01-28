#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define SIZE 40

typedef struct e {
	int ne; //dimensione lista di adiacenza di un nodo
	int * edge; //array che contiene la lista di adiacenza di un nodo
	int d;
} edges; 

struct queue {
    int items[SIZE];
    int front;
    int rear;
};

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);
struct queue* createQueue() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}


int isEmpty(struct queue* q) {
    if(q->rear == -1) 
        return 1;
    else 
        return 0;
}

void ENQUEUE(struct queue* q, int value){
    if(q->rear == SIZE-1)
       return; //printf("\nQueue is Full!!");
    else {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int DEQUEUE(struct queue* q){
    int item;
    if(isEmpty(q)){
        //printf("Queue is empty");
        item = -1;
    }
    else{
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear){
            //printf("Resetting queue");
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printQueue(struct queue *q) {
    int i = q->front;

    if(isEmpty(q)) {
        //printf("Queue is empty");
    } else {
        //printf("\nQueue contains \n");
        for(i = q->front; i < q->rear + 1; i++) {
                printf("%d ", q->items[i]);
        }//for
    }  //else  
}


int BFS (edges* G, int n, int* C) {
	int u; int i; int dest; int dmax=-1;
	struct queue* Q = createQueue();

	for (i=0;i<n;i++) {
		C[i]=0;
		G[i].d=10000;
	}

	C[0]=1;
	G[0].d=0;
	ENQUEUE (Q, 0);

	while (!isEmpty(Q)) {
	
		u=DEQUEUE (Q);

		for (i=0;i<G[u].ne;i++) {
			dest=G[u].edge[i];
			if (C[dest]==0) {
				C[dest]=1;
				G[dest].d=G[u].d+1;
				if (dmax < G[dest].d) dmax=G[dest].d;
				ENQUEUE (Q, dest);
			}//if
		}//for		
	C[u]=2;
	}//while 

	return dmax;
}

void printC(int *C, int n) {
	for (int i=0;i<n;i++)
		printf ("%d", C[i]);
}


int main() {

int n, i, valore, j;
int cont=0;

scanf ("%d", &n);

edges* G= malloc (n * sizeof(struct e));

int *C= (int*) malloc (sizeof(int)*n);

//creo lista di adiacenza
for (i=0;i<n;i++) {
	scanf ("%d", &G[i].ne);
	G[i].edge= malloc (G[i].ne * sizeof(int));

	for (j=0;j<G[i].ne;j++) {
		scanf ("%d", &valore);
		G[i].edge[j]=valore;
	}
}
//

int dmax=BFS (G, n, C);
//conta nodi a distanza massima
for (i=0;i<n;i++) {
	if (G[i].d==dmax) 
		cont++;

}

printf("%d", cont);


return 0;
}

