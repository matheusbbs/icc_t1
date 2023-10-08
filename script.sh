#Nome: Felipe Augusto Dittert Noleto; GRR:20205689
#Nome: Matheus Branco Barreto dos Santos; GRR:20203906

#!/bin/bash

CPU=3

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make

    likwid-perfctr -C ${CPU} -g FLOPS_DP -m ./ajustePol | grep -e "[\| FLOPS"
    likwid-perfctr -C ${CPU} -g ENERGY -m ./ajustePol #| grep -e "Energy[J]"

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor