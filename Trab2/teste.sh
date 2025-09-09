#!/bin/bash

make lik-all

likwid-perfctr -C 3 -g FLOPS_DP -m ./resolveEDO-likwid | tee >(grep -e "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE")

make purge
