/*
 * Question 2: Tower of Hanoi using Linked List Stack
 *
 * Each rod is a stack (linked list).
 * Displays all rod states after every move.
 *
 * Compile: gcc tower_hanoi_linkedlist.c -o hanoi_ll
 * Run    : ./hanoi_ll
 *
 * Concepts: Linked List, Stack ADT, Dynamic Memory, Recursion
 */

#include <stdio.h>
#include <stdlib.h>

/* ── Node ─────────────────────────────────────────────────── */
typedef struct Node {
    int          data;
    struct Node *next;
} Node;

/* ── Stack (represents one rod) ───────────────────────────── */
typedef struct {
    Node *top;
    char  name;
} Stack;

/* ── Stack operations ─────────────────────────────────────── */
Stack *createStack(char name)
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top   = NULL;
    s->name  = name;
    return s;
}

void push(Stack *s, int disk)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = disk;
    n->next = s->top;
    s->top  = n;
}

int pop(Stack *s)
{
    if (!s->top) { fprintf(stderr, "Underflow!\n"); exit(1); }
    Node *tmp  = s->top;
    int   disk = tmp->data;
    s->top     = tmp->next;
    free(tmp);
    return disk;
}

void displayStack(Stack *s)
{
    printf("%c : ", s->name);
    for (Node *cur = s->top; cur; cur = cur->next)
        printf("%d ", cur->data);
    printf("\n");
}

/* ── Move one disk and display all rods ───────────────────── */
void moveDisk(Stack *src, Stack *dest, Stack *other)
{
    int disk = pop(src);
    push(dest, disk);
    printf("\nMove Disk %d from %c to %c\n", disk, src->name, dest->name);
    /* show state of all three rods — caller passes the third */
    displayStack(src);
    displayStack(dest);
    displayStack(other);
}

/* ── Recursive Hanoi ──────────────────────────────────────── */
void towerOfHanoi(int n, Stack *src, Stack *aux, Stack *dest)
{
    if (n == 0) return;
    towerOfHanoi(n - 1, src, dest, aux);
    moveDisk(src, dest, aux);
    towerOfHanoi(n - 1, aux, src, dest);
}

int main(void)
{
    int n;
    printf("Enter number of disks: ");
    scanf("%d", &n);

    Stack *A = createStack('A');
    Stack *B = createStack('B');
    Stack *C = createStack('C');

    /* Push disks largest -> smallest into A */
    for (int i = n; i >= 1; i--)
        push(A, i);

    printf("\nInitial\n");
    displayStack(A);
    displayStack(B);
    displayStack(C);

    towerOfHanoi(n, A, B, C);

    printf("\n--- Final State ---\n");
    displayStack(A);
    displayStack(B);
    displayStack(C);

    free(A); free(B); free(C);
    return 0;
}
