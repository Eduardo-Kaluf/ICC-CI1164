#!/bin/bash

make all

while read -r n; do

    coefficients=()
    for ((i = 0; i < 5; i++)); do
        read -r line || break 2
        coefficients+=("$line")
    done

    likwid-perfctr -C 3 -g FLOPS_DP -m ./resolveEDO-likwid | tee >(grep -e "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE")

done < teste.dat
