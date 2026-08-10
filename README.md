# Firmware Test Solutions in C

Complete solutions for **two firmware test sets** — fully commented, compile-ready.

---

## 📁 Test Set 1 — `05_0_2026`

| # | Topic | File |
|---|-------|------|
| Q1 | Tower of Hanoi — Recursive | `Q1_Tower_Hanoi_Recursive/tower_hanoi_recursive.c` |
| Q2 | Tower of Hanoi — Linked List Stack | `Q2_Tower_Hanoi_LinkedList/tower_hanoi_linkedlist.c` |
| Q3 | Buddy Memory Allocation | `Q3_Buddy_Memory/buddy_memory.c` |
| Q4 | Linux Char Device Driver | `Q4_Char_Device_Driver/mychardev.c` |

---

## 📁 Test Set 2 — `06_08_2026`

| # | Topic | File |
|---|-------|------|
| Q1 | PSW Register — Union + Bit-fields | `Test2_06_08_2026/Q1_PSW_Union/psw_register.c` |
| Q2 | Sensor System — Union to Functions | `Test2_06_08_2026/Q2_Sensor_Union/sensor_union.c` |
| Q3 | Merge Sort — Array | `Test2_06_08_2026/Q3_MergeSort_Array/merge_sort_array.c` |
| Q4 | Merge Sort — Linked List | `Test2_06_08_2026/Q4_MergeSort_LinkedList/merge_sort_linkedlist.c` |

---

## 🚀 Quick Compile Guide

```bash
# Test Set 2 — Q1 PSW Register
gcc Test2_06_08_2026/Q1_PSW_Union/psw_register.c -o psw
./psw

# Test Set 2 — Q2 Sensor
gcc Test2_06_08_2026/Q2_Sensor_Union/sensor_union.c -o sensor
./sensor

# Test Set 2 — Q3 Merge Sort Array
gcc Test2_06_08_2026/Q3_MergeSort_Array/merge_sort_array.c -o msort
./msort

# Test Set 2 — Q4 Merge Sort Linked List
gcc Test2_06_08_2026/Q4_MergeSort_LinkedList/merge_sort_linkedlist.c -o msort_ll
./msort_ll

# Test Set 1 — Q1 Tower of Hanoi
gcc Q1_Tower_Hanoi_Recursive/tower_hanoi_recursive.c -o hanoi -lm
./hanoi

# Test Set 1 — Q3 Buddy Memory
gcc Q3_Buddy_Memory/buddy_memory.c -o buddy -lm
./buddy

# Test Set 1 — Q4 Device Driver
cd Q4_Char_Device_Driver && make && sudo insmod mychardev.ko
```

---

## 🧠 Concepts Covered

| Topic | Concepts |
|-------|---------|
| Union + Bit-fields | Memory sharing, register mapping, embedded C |
| Struct + Union + Functions | Pass-by-value vs pointer, modular design |
| Merge Sort (Array) | Divide & Conquer, O(n log n), recursion |
| Merge Sort (Linked List) | Slow/fast pointer, list splitting, merging |
| Tower of Hanoi | Recursion, stack behavior |
| Buddy Memory | Power-of-2, splitting, merging, fragmentation |
| Device Driver | Kernel module, file_operations, copy_to_user |

---

## 👨‍💻 Author

**Mayilvannan VB** | EEE Student | Embedded & System Programming  
