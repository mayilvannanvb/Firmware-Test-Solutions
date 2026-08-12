
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int          data;
    struct Node *next;
} Node;
typedef struct {
    Node *top;
    char  name;
} Stack;
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
void moveDisk(Stack *src, Stack *dest, Stack *other)
{
    int disk = pop(src);
    push(dest, disk);
    printf("\nMove Disk %d from %c to %c\n", disk, src->name, dest->name);
    displayStack(src);
    displayStack(dest);
    displayStack(other);
}

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
}

    free(A); free(B); free(C);
    return 0;
}
