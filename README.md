# Firmware Test Solutions in C

Solutions for all 4 firmware test questions — fully commented, compile-ready.

---

## Questions

| # | Topic | File | Compile |
|---|-------|------|---------|
| Q1 | Tower of Hanoi — Recursive | `Q1_Tower_Hanoi_Recursive/tower_hanoi_recursive.c` | `gcc ... -lm` |
| Q2 | Tower of Hanoi — Linked List Stack | `Q2_Tower_Hanoi_LinkedList/tower_hanoi_linkedlist.c` | `gcc ...` |
| Q3 | Buddy Memory Allocation | `Q3_Buddy_Memory/buddy_memory.c` | `gcc ... -lm` |
| Q4 | Linux Char Device Driver | `Q4_Char_Device_Driver/mychardev.c` | `make` |

---

## Q1 — Tower of Hanoi (Recursive)

```bash
gcc Q1_Tower_Hanoi_Recursive/tower_hanoi_recursive.c -o hanoi -lm
./hanoi
# Enter: 3
```

**Concepts:** Recursion, Divide & Conquer, `T(n) = 2^n - 1`

---

## Q2 — Tower of Hanoi (Linked List Stack)

```bash
gcc Q2_Tower_Hanoi_LinkedList/tower_hanoi_linkedlist.c -o hanoi_ll
./hanoi_ll
# Enter: 3
```

**Concepts:** Linked List, Stack ADT, Dynamic Memory, Recursion

---

## Q3 — Buddy Memory Allocation

```bash
gcc Q3_Buddy_Memory/buddy_memory.c -o buddy -lm
./buddy
```

**Menu:** Allocate | Free | Display | Exit  
**Concepts:** Power-of-2, Splitting, Merging, Internal Fragmentation

---

## Q4 — Linux Character Device Driver

```bash
# Install kernel headers
sudo apt install linux-headers-$(uname -r)

cd Q4_Char_Device_Driver
make
sudo insmod mychardev.ko

# Test
echo "Hello Driver" > /dev/mychardev
cat /dev/mychardev

# Remove
sudo rmmod mychardev
dmesg | tail -10
```

**Concepts:** Kernel Module, `file_operations`, `copy_to_user`, `copy_from_user`

---

## Author

**Mayilvannan VB** | EEE Student | Embedded & System Programming  
