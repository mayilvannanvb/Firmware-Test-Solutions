#!/bin/bash
# test.sh — Test mychardev driver
# Run after: sudo insmod mychardev.ko

echo "=== mychardev Driver Test ==="

echo "--- Writing ---"
echo "Embedded Linux" | sudo tee /dev/mychardev

echo ""
echo "--- Reading ---"
cat /dev/mychardev

echo ""
echo "--- Kernel Log ---"
sudo dmesg | tail -10
