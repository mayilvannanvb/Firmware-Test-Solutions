
#include <stdio.h>
#include <math.h>

void towerOfHanoi(int n, char src, char aux, char dest)
{
    if (n == 0)
        return;

    towerOfHanoi(n - 1, src, dest, aux);         
    printf("Move Disk %d from %c to %c\n", n, src, dest); 
    towerOfHanoi(n - 1, aux, src, dest);           
}

int main(void)
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    printf("\n--- Tower of Hanoi (N=%d) ---\n\n", n);
    towerOfHanoi(n, 'A', 'B', 'C');
    printf("\nTotal Moves = %d\n", (int)pow(2, n) - 1);

    return 0;
}
