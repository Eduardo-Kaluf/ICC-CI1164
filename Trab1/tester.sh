#!/bin/sh

make all

while true; do
    read line1 || brea
    read line2 || break
    read line3 || break
    read line4 || break

    printf "${line1}\n${line2}\n${line3}\n" | ./labZero
done < polinomios.dat