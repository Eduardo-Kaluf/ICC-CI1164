#!/bin/bash

input=10000

make
result1=$(echo "$input" | ./cgSolver)
make purge

cd ./Trab1Copy

make
result2=$(echo "$input" | ./cgSolver)
make purge

cd ..

clear

echo "Trab 1 (from ./Trab1Copy)"
echo "$result2"
echo "Trab 2 (from .)"
echo "$result1"
