#ifndef STRUCTURES_H
#define STRUCTURES_H
 
/* ---------- Arrays ---------- */
int  array_access(int a[], int i);
void array_insert(int a[], int *n, int i, int x);
void array_delete(int a[], int *n, int i);
void array_print(int a[], int n);
 
/* ---------- Singly linked list ---------- */
typedef struct Node {
    int value;
    struct Node *next;
} Node;
 
void add_first(Node **head, int x);
void add_last(Node **head, int x);
void remove_value(Node **head, int x);
void print_list(Node *head);
void free_list(Node **head);
 
/* ---------- Doubly linked list ---------- */
typedef struct DNode {
    int value;
    struct DNode *prev;
    struct DNode *next;
} DNode;
 
void add_first_double(DNode **head, int x);
void print_double(DNode *head);
void free_double(DNode **head);
 
/* ---------- Circular linked list ---------- */
void add_circular(Node **head, int x);
void print_circular(Node *head);
void free_circular(Node **head);
 
/* ---------- Stack (LIFO) ---------- */
#define MAX 100
 
typedef struct {
    int t[MAX];
    int size;
} Stack;
 
void init_stack(Stack *s);
int  stack_empty(Stack *s);
void push(Stack *s, int x);
int  pop(Stack *s);
int  peek(Stack *s);
 
/* ---------- Queue (FIFO) ---------- */
typedef struct {
    Node *front;
    Node *rear;
} Queue;
 
void init_queue(Queue *q);
int  queue_empty(Queue *q);
void enqueue(Queue *q, int x);
int  dequeue(Queue *q);
int  front(Queue *q);
 
/* ---------- Circular queue ---------- */
typedef struct {
    int t[MAX];
    int front;
    int size;
} CircQueue;
 
void init_circ(CircQueue *q);
void enqueue_circ(CircQueue *q, int x);
int  dequeue_circ(CircQueue *q);
 
/* ---------- Priority queue ---------- */
typedef struct PNode {
    int value;
    int priority;
    struct PNode *next;
} PNode;
 
void enqueue_prio(PNode **head, int x, int priority);
int  dequeue_prio(PNode **head);
 
/* ---------- Hash table ---------- */
#define SIZE 10
 
typedef struct Entry {
    char key[32];
    char value[32];
    struct Entry *next;
} Entry;
 
int   hash(char *key);
void  insert(Entry *table[], char *key, char *value);
char *search(Entry *table[], char *key);    /* NULL if absent */
void  delete_key(Entry *table[], char *key);
 

#endif