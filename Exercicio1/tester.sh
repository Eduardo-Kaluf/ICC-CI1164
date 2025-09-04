#!/bin/bash

# -all 
# -run

make

while read -r n; do
    coefficients=()

    for ((i = 0; i < $n; i++)); do
        read -r x || break

        coefficients+=("$x")
    done

    read -r newLine || break

    case "$1" in
    -all)
        {
            echo "$n"
            printf "%s\n" "${coefficients[@]}"
        } | likwid-perfctr -C 3 -g FLOPS_DP  -m  ./perfSL | grep -e "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE" -e "DP MFLOP/s" | grep -v "AVX"
        ;;
    -run)
        {
            echo "$n"
            printf "%s\n" "${coefficients[@]}"
        } | ./perfSL
        ;;
    esac

done < sistemas.dat

echo "Script finished processing test.dat."
