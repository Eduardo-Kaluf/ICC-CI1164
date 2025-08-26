#!/bin/bash

make

if [ ! -f ./perfSL ]; then
    echo "Error: Compilation failed or the executable './perfSL' was not found."
    exit 1
fi

while read -r n; do
    coefficients=()

    for ((i = 0; i < $n; i++)); do
        read -r x || break

        coefficients+=("$x")
    done

    read -r newLine || break

    {
        echo "$n"
        printf "%s\n" "${coefficients[@]}"
    } | ./perfSL

done < sistemas.dat

echo "Script finished processing test.dat."
