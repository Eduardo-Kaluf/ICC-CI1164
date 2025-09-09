#!/bin/bash

# EDUARDO KALUF - GRR 20241770

TEMP_INPUT_FILE=$(mktemp)
VOID_FILE="VOID_FILE"

trap 'rm -f -- "$TEMP_INPUT_FILE"' EXIT
trap 'rm -f -- "$VOID_FILE"' EXIT

cat > "$TEMP_INPUT_FILE"

# _____________ #

make all &> "$VOID_FILE"

./resolveEDO < "$TEMP_INPUT_FILE"

make purge

# _____________ #

make lik-all &> "$VOID_FILE"

likwid-perfctr -C 3 -g FLOPS_DP -m ./resolveEDO-likwid < "$TEMP_INPUT_FILE"| grep -e "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE"

make purge

