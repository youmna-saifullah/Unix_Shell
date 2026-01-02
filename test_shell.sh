#!/bin/bash

# 1. Compile the project
echo "--- Compiling MyShell ---"
gcc -Iinclude src/*.c src/builtins/*.c src/filesystem/*.c -o myshell

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Compilation successful. Starting tests..."
echo "---------------------------------------"

# 2. Define a list of commands to test
# Hum commands ko 'myshell' ke andar bhej rahe hain
./myshell << 'EOF'
help
pwd
mkdir test_dir
ls
cd test_dir
pwd
cd ..
echo "Testing echo command"
export MY_VAR=HelloShell
echo $MY_VAR
history
man ls
man kill
clear
exit
EOF

echo "---------------------------------------"
echo "Tests Completed!"
# Test directory ko saaf karne ke liye
rmdir test_dir
