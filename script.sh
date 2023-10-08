#Nome: Felipe Augusto Dittert Noleto; GRR:20205689
#Nome: Matheus Branco Barreto dos Santos; GRR:20203906

#!/bin/bash

CPU=3

LIKWID_HOME=/usr/local
CFLAGS="-O3 -mavx -march=native -DLIKWID_PERFMON -I${LIKWID_HOME}/include"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

gcc ${CFLAGS} perfEG.c -o perfEG ${LFLAGS}

    likwid-perfctr -C ${CPU} -g FLOPS_DP -m ./perfEG | grep -e "[\|tgeraSL\|tsolSL\|  FLOPS"
    likwid-perfctr -C ${CPU} -g ENERGY -m ./perfEG | grep -e "Energy[J]"

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor