/*
 * Question 1: Tower of Hanoi - Recursive
 *
 * Compile: gcc tower_hanoi_recursive.c -o hanoi -lm
 * Run    : ./hanoi
 *
 * Sample Output (N=3):
 *   Move Disk 1 from A to C
 *   Move Disk 2 from A to B
 *   Move Disk 1 from C to B
 *   Move Disk 3 from A to C
 *   Move Disk 1 from B to A
 *   Move Disk 2 from B to C
 *   Move Disk 1 from A to C
 *   Total Moves = 7
 *
 * Concepts: Recursion, Divide & Conquer, Stack behavior
 *           Recurrence: T(n) = 2^n - 1
 */

#include <stdio.h>
#include <math.h>

/*
 * towerOfHanoi()
 *   n    - number of disks
 *   src  - source rod      (A)
 *   aux  - auxiliary rod   (B)
 *   dest - destination rod (C)
 *
 * Logic:
 *   1. Move top (n-1) disks: src -> aux  (using dest)
 *   2. Move disk n          : src -> dest
 *   3. Move top (n-1) disks: aux -> dest (using src)
 */
void towerOfHanoi(int n, char src, char aux, char dest)
{
    if (n == 0)
        return;

    towerOfHanoi(n - 1, src, dest, aux);          /* step 1 */
    printf("Move Disk %d from %c to %c\n", n, src, dest);  /* step 2 */
    towerOfHanoi(n - 1, aux, src, dest);           /* step 3 */
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
