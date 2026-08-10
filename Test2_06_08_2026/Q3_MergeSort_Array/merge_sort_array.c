/*
 * Question 3: Merge Sort Using Arrays
 *
 * Sorts N integers using Merge Sort.
 * Prints the array after every merge step.
 *
 * Compile : gcc merge_sort_array.c -o msort
 * Run     : ./msort
 *
 * Input  : 8 elements — 45 10 7 60 12 89 34 21
 * Output :
 *   Original Array: 45 10 7 60 12 89 34 21
 *   After Merge: 10 45
 *   After Merge: 7 60
 *   After Merge: 7 10 45 60
 *   ...
 *   Sorted Array: 7 10 12 21 34 45 60 89
 *
 * Complexity: Time O(n log n), Space O(n)
 * Concepts  : Divide & Conquer, Recursion, Arrays
 */

#include <stdio.h>
#include <stdlib.h>

/* ── Print a subarray arr[l..r] ──────────────────────────────── */
void printArray(int *arr, int l, int r)
{
    for (int i = l; i <= r; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/* ── Merge two sorted halves arr[l..m] and arr[m+1..r] ────────── */
void merge(int *arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    /* Temporary arrays */
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    /* Merge: pick smaller element each time */
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    /* Copy remaining elements */
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L); free(R);

    /* Show merged subarray */
    printf("After Merge: ");
    printArray(arr, l, r);
}

/* ── Recursive merge sort ────────────────────────────────────── */
void mergeSort(int *arr, int l, int r)
{
    if (l >= r) return;          /* base case: single element */

    int m = l + (r - l) / 2;    /* mid point (avoids overflow) */

    mergeSort(arr, l, m);        /* sort left half  */
    mergeSort(arr, m + 1, r);    /* sort right half */
    merge(arr, l, m, r);         /* merge both halves */
}

int main(void)
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nOriginal Array: ");
    printArray(arr, 0, n - 1);
    printf("\n--- Merge Steps ---\n");

    mergeSort(arr, 0, n - 1);

    printf("\nSorted Array: ");
    printArray(arr, 0, n - 1);

    free(arr);
    return 0;
}
