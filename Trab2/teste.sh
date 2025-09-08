#!/bin/bash

# -lik-all
# -all

if [ -z "$1" ]; then
    echo "Erro: Forneça um argumento (-all ou -lik-all)."
    echo "Uso: $0 [-all | -lik-all]"
    exit 1
fi

while read -r n; do

    coefficients=()
    for ((i = 0; i < 5; i++)); do
        read -r line || break 2
        coefficients+=("$line")
    done

    case "$1" in
    -lik-all)
        {
            make lik-all

            echo "$n"
            printf "%s\n" "${coefficients[@]}"
        } | likwid-perfctr -C 3 -g FLOPS_DP -m ./resolveEDO | grep -e "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE" -e "DP MFLOP/s" | grep -v "AVX"
        ;;
    -all)
        {
            echo "$n"
            printf "%s\n" "${coefficients[@]}"
        } | ./resolveEDO
        ;;
    *)
        echo "Argumento inválido: $1. Use -all ou -lik-all."
        exit 1
        ;;
    esac

done < teste.dat
