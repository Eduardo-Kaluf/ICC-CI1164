#!/bin/bash

make
clear

likwid-perfctr -C 3 -g FLOPS_DP  -m  ./perfSL < test.dat | grep -e "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE" -e "DP"
 
make purge