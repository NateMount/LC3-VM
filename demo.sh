#!/bin/bash

# Define File Path
FILE="LC3/2024.obj"

# If file does not exist then download it
if [ ! -f "$FILE" ]; then
    curl https://www.jmeiners.com/lc3-vm/supplies/2048.obj --output "$FILE"
fi

gcc LC3/main.c -o lc3-vm
./lc3-vm LC3/2048.obj
rm -f lc3-vm