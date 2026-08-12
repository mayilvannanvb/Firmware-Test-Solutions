#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TOTAL_MEM   1024
#define MAX_BLOCKS  256
#define PID_LEN     16

typedef struct {
    int  size;
    int  start;
    int  allocated;
    char pid[PID_LEN];
} Block;

Block memory[MAX_BLOCKS];
int   block_count    = 0;
int   failed_allocs  = 0;
int   total_alloc    = 0;
int   internal_frag  = 0;
int nextPow2(int n)
{
    int p = 1;
    while (p < n) p <<= 1;
    return p;
}

void initializeMemory(void)
{
    block_count         = 1;
    memory[0].size      = TOTAL_MEM;
    memory[0].start     = 0;
    memory[0].allocated = 0;
    strcpy(memory[0].pid, "FREE");
    printf("Memory initialized: %d KB\n", TOTAL_MEM);
}
void splitBlock(int idx)
{
    int half = memory[idx].size / 2;
    for (int i = block_count; i > idx + 1; i--)
        memory[i] = memory[i - 1];
    block_count++;
    memory[idx].size          = half;
    memory[idx+1].size        = half;
    memory[idx+1].start       = memory[idx].start + half;
    memory[idx+1].allocated   = 0;
    strcpy(memory[idx+1].pid, "FREE");
}

void allocateMemory(void)
{
    char pid[PID_LEN];
    int  req;

    printf("Enter Process ID : "); scanf("%s", pid);
    printf("Enter Size (KB)  : "); scanf("%d", &req);

    int needed = nextPow2(req);
    int found = -1;
    for (int i = 0; i < block_count; i++) {
        if (!memory[i].allocated && memory[i].size >= needed)
            if (found == -1 || memory[i].size < memory[found].size)
                found = i;
    }

    if (found == -1) {
        printf("Allocation FAILED: no block of %d KB available\n", needed);
        failed_allocs++;
        return;
    }
    while (memory[found].size > needed)
        splitBlock(found);

    memory[found].allocated = 1;
    strncpy(memory[found].pid, pid, PID_LEN - 1);

    int frag = needed - req;
    internal_frag += frag;
    total_alloc   += needed;

    printf("Allocated %d KB to %s (req=%d KB, frag=%d KB)\n",
           needed, pid, req, frag);
}
void mergeBuddy(void)
{
    int merged = 1;
    while (merged) {
        merged = 0;
        for (int i = 0; i < block_count - 1; i++) {
            if (!memory[i].allocated &&
                !memory[i+1].allocated &&
                memory[i].size == memory[i+1].size &&
                memory[i].start + memory[i].size == memory[i+1].start &&
                (memory[i].start % (memory[i].size * 2)) == 0)
            {
                memory[i].size *= 2;
                for (int j = i + 1; j < block_count - 1; j++)
                    memory[j] = memory[j+1];
                block_count--;
                merged = 1;
                break;
            }
        }
    }
}

void freeMemory(void)
{
    char pid[PID_LEN];
    printf("Enter Process ID to free: "); scanf("%s", pid);

    int found = 0;
    for (int i = 0; i < block_count; i++) {
        if (memory[i].allocated && strcmp(memory[i].pid, pid) == 0) {
            memory[i].allocated = 0;
            strcpy(memory[i].pid, "FREE");
            total_alloc -= memory[i].size;
            printf("Freed %d KB from %s\n", memory[i].size, pid);
            found = 1;
        }
    }
    if (!found) printf("Process %s not found\n", pid);
    mergeBuddy();
}

void displayMemory(void)
{
    printf("\n%-10s %-8s %-8s %-12s %s\n",
           "Size(KB)","Start","End","Status","PID");
    printf("%-10s %-8s %-8s %-12s %s\n",
           "--------","-----","---","------","---");
    for (int i = 0; i < block_count; i++)
        printf("%-10d %-8d %-8d %-12s %s\n",
               memory[i].size, memory[i].start,
               memory[i].start + memory[i].size - 1,
               memory[i].allocated ? "Allocated" : "Free",
               memory[i].pid);
    printf("\nAllocated: %d KB | Free: %d KB | Frag: %d KB | Failed: %d\n",
           total_alloc, TOTAL_MEM - total_alloc, internal_frag, failed_allocs);
}

int main(void)
{
    int choice;
    initializeMemory();

    do {
        printf("\n=== Buddy Memory Allocator ===\n");
        printf("1. Allocate  2. Free  3. Display  4. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: allocateMemory(); break;
            case 2: freeMemory();     break;
            case 3: displayMemory();  break;
            case 4: printf("Bye!\n"); break;
            default: printf("Invalid\n");
        }
    } while (choice != 4);

    return 0;
}
