# How to run the program

To run just only one test case with likwid do:
```yaml
make
likwid-perfctr -C 3 -g FLOPS_DP  -m ./perfSL < test.dat > test.log
```

test.dat should contain the linear system that you want to use.

---
To test for all inputs with LIKWID:
```yaml
./tester.sh -all
```
---
To test for all inputs without LIKWID:
```yaml
./teste.sh -run
```
This script greps just "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE" and "DP MFLOP/s", if you're in a different archtecture you should delete the grep from the teste.sh file and look for what event matter to you

## Likwid example result

make + likwid-perfctr -C 3 -g FLOPS_DP  -m ./perfSL < test.dat > test.log

test.log on Intel:
<pre>
--------------------------------------------------------------------------------
CPU name:	Intel(R) Core(TM) i5-7500 CPU @ 3.40GHz
CPU type:	Intel Coffeelake processor
CPU clock:	3.41 GHz
--------------------------------------------------------------------------------
EG: 
0.000723 ms
0.999999999999 0.999999999999 1.000000000000 
0.000000000000 0.000000000000 0.000000000000 

GS [ 19 iterações ]: 
0.001975 ms
1.000032632550 0.999972136666 0.999969752058 
-0.000156008926 0.000081205392 -0.000000000000 

TESTE ENDED

--------------------------------------------------------------------------------
Region EG_TEST, Group 1: FLOPS_DP
+-------------------+----------+
|    Region Info    |  Core 3  |
+-------------------+----------+
| RDTSC Runtime [s] | 0.000013 |
|     call count    |        1 |
+-------------------+----------+

+------------------------------------------+---------+--------+
|                   Event                  | Counter | Core 3 |
+------------------------------------------+---------+--------+
|             INSTR_RETIRED_ANY            |  FIXC0  |  24366 |
|           CPU_CLK_UNHALTED_CORE          |  FIXC1  |  49184 |
|           CPU_CLK_UNHALTED_REF           |  FIXC2  |  44162 |
| FP_ARITH_INST_RETIRED_128B_PACKED_DOUBLE |   PMC0  |      0 |
|    FP_ARITH_INST_RETIRED_SCALAR_DOUBLE   |   PMC1  |     63 |
| FP_ARITH_INST_RETIRED_256B_PACKED_DOUBLE |   PMC2  |      0 |
+------------------------------------------+---------+--------+

+----------------------+--------------+
|        Metric        |    Core 3    |
+----------------------+--------------+
|  Runtime (RDTSC) [s] | 1.331289e-05 |
| Runtime unhalted [s] | 1.443201e-05 |
|      Clock [MHz]     |    3795.5286 |
|          CPI         |       2.0186 |
|      DP MFLOP/s      |       4.7323 |
|    AVX DP MFLOP/s    |            0 |
|    Packed MUOPS/s    |            0 |
|    Scalar MUOPS/s    |       4.7323 |
|  Vectorization ratio |            0 |
+----------------------+--------------+

Region GS_TEST, Group 1: FLOPS_DP
+-------------------+----------+
|    Region Info    |  Core 3  |
+-------------------+----------+
| RDTSC Runtime [s] | 0.000005 |
|     call count    |        1 |
+-------------------+----------+

+------------------------------------------+---------+--------+
|                   Event                  | Counter | Core 3 |
+------------------------------------------+---------+--------+
|             INSTR_RETIRED_ANY            |  FIXC0  |  31140 |
|           CPU_CLK_UNHALTED_CORE          |  FIXC1  |  29377 |
|           CPU_CLK_UNHALTED_REF           |  FIXC2  |  25986 |
| FP_ARITH_INST_RETIRED_128B_PACKED_DOUBLE |   PMC0  |      0 |
|    FP_ARITH_INST_RETIRED_SCALAR_DOUBLE   |   PMC1  |    515 |
| FP_ARITH_INST_RETIRED_256B_PACKED_DOUBLE |   PMC2  |      0 |
+------------------------------------------+---------+--------+

+----------------------+--------------+
|        Metric        |    Core 3    |
+----------------------+--------------+
|  Runtime (RDTSC) [s] | 5.373279e-06 |
| Runtime unhalted [s] | 8.620060e-06 |
|      Clock [MHz]     |    3852.6997 |
|          CPI         |       0.9434 |
|      DP MFLOP/s      |      95.8446 |
|    AVX DP MFLOP/s    |            0 |
|    Packed MUOPS/s    |            0 |
|    Scalar MUOPS/s    |      95.8446 |
|  Vectorization ratio |            0 |
+----------------------+--------------+
</pre>
