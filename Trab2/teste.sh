#!/bin/bash


TEMP_INPUT_FILE=$(mktemp)

trap 'rm -f -- "$TEMP_INPUT_FILE"' EXIT

cat > "$TEMP_INPUT_FILE"

# _____________ #

make all

./resolveEDO < "$TEMP_INPUT_FILE"

make purge

# _____________ #

make lik-all

likwid-perfctr -C 3 -g FLOPS_DP -m ./resolveEDO-likwid < "$TEMP_INPUT_FILE"| grep -e "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE"

make purge

