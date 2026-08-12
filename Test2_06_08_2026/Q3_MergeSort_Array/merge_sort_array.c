
#include <stdio.h>
#include <stdlib.h>

void printArray(int *arr, int l, int r)
{
    for (int i = l; i <= r; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void merge(int *arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L); free(R);

    printf("After Merge: ");
    printArray(arr, l, r);
}

void mergeSort(int *arr, int l, int r)
{
    if (l >= r) return;        

    int m = l + (r - l) / 2;    

    mergeSort(arr, l, m);        
    mergeSort(arr, m + 1, r);    
    merge(arr, l, m, r);         
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
}
    free(arr);
    return 0;
}
