

#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int          data;
    struct Node *next;
} Node;

Node *createNode(int data)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    return n;
}

void insertNode(Node **head, int data)
{
    Node *newn = createNode(data);
    if (!*head) { *head = newn; return; }
    Node *cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = newn;
}

void displayList(Node *head)
{
    while (head) {
        printf("%d", head->data);
        if (head->next) printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

void splitList(Node *head, Node **left, Node **right)
{
    if (!head || !head->next) {
        *left  = head;
        *right = NULL;
        return;
    }

    Node *slow = head;
    Node *fast = head->next;   
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *left       = head;
    *right      = slow->next;
    slow->next  = NULL;       
}


Node *mergeLists(Node *a, Node *b)
{
    if (!a) return b;
    if (!b) return a;

    if (a->data <= b->data) {
        a->next = mergeLists(a->next, b);
        return a;
    } else {
        b->next = mergeLists(a, b->next);
        return b;
    }
}

Node *mergeSort(Node *head)
{
    if (!head || !head->next)
        return head;

    Node *left, *right;
    splitList(head, &left, &right);

    left  = mergeSort(left);
    right = mergeSort(right);

    return mergeLists(left, right);
}

void freeList(Node *head)
{
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void)
{
    Node *head = NULL;
    int n, val;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        insertNode(&head, val);
    }

    printf("\nOriginal List: ");
    displayList(head);

    head = mergeSort(head);

    printf("Sorted List  : ");
    displayList(head);
}

    freeList(head);
    return 0;
}
