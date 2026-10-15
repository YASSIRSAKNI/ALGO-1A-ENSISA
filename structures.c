#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
 
/* ================= ARRAYS ================= */
 
int array_access(int a[], int i)        /* O(1) */
{
    return a[i];
}
 
void array_insert(int a[], int *n, int i, int x)   /* O(n) : shift right */
{
    for (int j = *n - 1; j >= i; j--)
        a[j + 1] = a[j];
    a[i] = x;
    (*n)++;
}
 
void array_delete(int a[], int *n, int i)          /* O(n) : shift left */
{
    for (int j = i; j <= *n - 2; j++)
        a[j] = a[j + 1];
    (*n)--;
}
 
void array_print(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}
 
/* ================= SINGLY LINKED LIST ================= */
 
void add_first(Node **head, int x)      /* O(1) */
{
    Node *n = malloc(sizeof(Node));
    n->value = x;
    n->next = *head;
    *head = n;
}
 
void add_last(Node **head, int x)       /* O(n) */
{
    Node *n = malloc(sizeof(Node));
    n->value = x;
    n->next = NULL;
 
    if (*head == NULL) {
        *head = n;
        return;
    }
    Node *cur = *head;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = n;
}
 
void remove_value(Node **head, int x)   /* O(n) */
{
    Node *cur = *head;
    Node *prev = NULL;
 
    while (cur != NULL && cur->value != x) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) return;                /* not found */
 
    if (prev == NULL) *head = cur->next;    /* it was the head */
    else prev->next = cur->next;
    free(cur);
}
 
void print_list(Node *head)
{
    while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}
 
void free_list(Node **head)
{
    while (*head != NULL) {
        Node *tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}
 
/* ================= DOUBLY LINKED LIST ================= */
 
void add_first_double(DNode **head, int x)
{
    DNode *n = malloc(sizeof(DNode));
    n->value = x;
    n->prev = NULL;
    n->next = *head;
    if (*head != NULL) (*head)->prev = n;
    *head = n;
}
 
void print_double(DNode *head)
{
    printf("NULL <-> ");
    while (head != NULL) {
        printf("%d <-> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}
 
void free_double(DNode **head)
{
    while (*head != NULL) {
        DNode *tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}
 
/* ================= CIRCULAR LINKED LIST ================= */
 
void add_circular(Node **head, int x)   /* adds at the end */
{
    Node *n = malloc(sizeof(Node));
    n->value = x;
 
    if (*head == NULL) {
        n->next = n;                    /* points to itself */
        *head = n;
        return;
    }
    Node *cur = *head;
    while (cur->next != *head)          /* find the last node */
        cur = cur->next;
    cur->next = n;
    n->next = *head;                    /* close the loop */
}
 
void print_circular(Node *head)
{
    if (head == NULL) return;
    Node *cur = head;
    do {
        printf("%d -> ", cur->value);
        cur = cur->next;
    } while (cur != head);              /* stop when back to start */
    printf("(back to %d)\n", head->value);
}
 
void free_circular(Node **head)
{
    if (*head == NULL) return;
    Node *cur = (*head)->next;
    while (cur != *head) {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(*head);
    *head = NULL;
}
 
/* ================= STACK ================= */
 
void init_stack(Stack *s)  { s->size = 0; }
int  stack_empty(Stack *s) { return s->size == 0; }
 
void push(Stack *s, int x)              /* O(1) */
{
    if (s->size < MAX)
        s->t[s->size++] = x;
}
 
int pop(Stack *s)  { return s->t[--s->size]; }      /* O(1), check stack_empty first */
int peek(Stack *s) { return s->t[s->size - 1]; }    /* O(1) */
 
/* ================= QUEUE ================= */
 
void init_queue(Queue *q)  { q->front = q->rear = NULL; }
int  queue_empty(Queue *q) { return q->front == NULL; }
 
void enqueue(Queue *q, int x)           /* O(1) : add at rear */
{
    Node *n = malloc(sizeof(Node));
    n->value = x;
    n->next = NULL;
    if (q->rear == NULL) q->front = n;
    else q->rear->next = n;
    q->rear = n;
}
 
int dequeue(Queue *q)                   /* O(1) : remove from front, check queue_empty first */
{
    Node *tmp = q->front;
    int x = tmp->value;
    q->front = tmp->next;
    if (q->front == NULL) q->rear = NULL;
    free(tmp);
    return x;
}
 
int front(Queue *q) { return q->front->value; }
 
/* ================= CIRCULAR QUEUE ================= */
 
void init_circ(CircQueue *q) { q->front = 0; q->size = 0; }
 
void enqueue_circ(CircQueue *q, int x)
{
    if (q->size == MAX) return;                     /* full */
    q->t[(q->front + q->size) % MAX] = x;           /* rear wraps around */
    q->size++;
}
 
int dequeue_circ(CircQueue *q)
{
    int x = q->t[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return x;
}
 
/* ================= PRIORITY QUEUE ================= */
 
void enqueue_prio(PNode **head, int x, int priority)   /* sorted insert, highest first */
{
    PNode *n = malloc(sizeof(PNode));
    n->value = x;
    n->priority = priority;
 
    if (*head == NULL || priority > (*head)->priority) {
        n->next = *head;
        *head = n;
        return;
    }
    PNode *cur = *head;
    while (cur->next != NULL && cur->next->priority >= priority)
        cur = cur->next;
    n->next = cur->next;
    cur->next = n;
}
 
int dequeue_prio(PNode **head)          /* the VIP is always at the head */
{
    PNode *tmp = *head;
    int x = tmp->value;
    *head = tmp->next;
    free(tmp);
    return x;
}
 
/* ================= HASH TABLE ================= */
 
int hash(char *key)                     /* sum of ASCII codes % SIZE */
{
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++)
        sum += key[i];
    return sum % SIZE;
}
 
void insert(Entry *table[], char *key, char *value)
{
    Entry *e = malloc(sizeof(Entry));
    strcpy(e->key, key);
    strcpy(e->value, value);
    int i = hash(key);
    e->next = table[i];                 /* collision : chaining */
    table[i] = e;
}
 
char *search(Entry *table[], char *key)
{
    for (Entry *e = table[hash(key)]; e != NULL; e = e->next)
        if (strcmp(e->key, key) == 0)
            return e->value;
    return NULL;
}
 
void delete_key(Entry *table[], char *key)
{
    int i = hash(key);
    Entry *cur = table[i];
    Entry *prev = NULL;
 
    while (cur != NULL && strcmp(cur->key, key) != 0) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) return;
 
    if (prev == NULL) table[i] = cur->next;
    else prev->next = cur->next;
    free(cur);
}