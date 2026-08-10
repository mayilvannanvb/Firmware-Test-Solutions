/*
 * Question 4: Merge Sort Using Singly Linked List
 *
 * Sorts a singly linked list using Merge Sort.
 * Uses slow/fast pointer technique to find the middle node.
 * No array conversion — pure linked list operations.
 *
 * Compile : gcc merge_sort_linkedlist.c -o msort_ll
 * Run     : ./msort_ll
 *
 * Input  : 45 10 7 60 12 89 34 21
 * Output :
 *   Original: 45 -> 10 -> 7 -> 60 -> 12 -> 89 -> 34 -> 21
 *   Sorted  : 7 -> 10 -> 12 -> 21 -> 34 -> 45 -> 60 -> 89
 *
 * Concepts: Linked List, Slow/Fast pointer, Recursion,
 *           Divide & Conquer, Merge Sort O(n log n)
 */

#include <stdio.h>
#include <stdlib.h>

/* ── Node ─────────────────────────────────────────────────────── */
typedef struct Node {
    int          data;
    struct Node *next;
} Node;

/* ── Create a new node ───────────────────────────────────────── */
Node *createNode(int data)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    return n;
}

/* ── Insert at end ───────────────────────────────────────────── */
void insertNode(Node **head, int data)
{
    Node *newn = createNode(data);
    if (!*head) { *head = newn; return; }
    Node *cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = newn;
}

/* ── Display list ────────────────────────────────────────────── */
void displayList(Node *head)
{
    while (head) {
        printf("%d", head->data);
        if (head->next) printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

/*
 * splitList(): find midpoint using slow/fast pointer,
 * split list into two halves.
 *
 * slow moves 1 step, fast moves 2 steps.
 * When fast reaches end, slow is at midpoint.
 */
void splitList(Node *head, Node **left, Node **right)
{
    if (!head || !head->next) {
        *left  = head;
        *right = NULL;
        return;
    }

    Node *slow = head;
    Node *fast = head->next;   /* fast starts one ahead */

    /* Advance until fast hits the end */
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    /* slow is now at midpoint — split here */
    *left       = head;
    *right      = slow->next;
    slow->next  = NULL;        /* cut the link */
}

/*
 * mergeLists(): merge two sorted linked lists.
 * Picks smaller head each time — no extra space needed.
 */
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

/* ── Recursive Merge Sort ────────────────────────────────────── */
Node *mergeSort(Node *head)
{
    /* Base case: empty or single element */
    if (!head || !head->next)
        return head;

    Node *left, *right;
    splitList(head, &left, &right);

    left  = mergeSort(left);
    right = mergeSort(right);

    return mergeLists(left, right);
}

/* ── Free the list ───────────────────────────────────────────── */
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

    freeList(head);
    return 0;
}
