#Nome: Felipe Augusto Dittert Noleto; GRR:20205689
#Nome: Matheus Branco Barreto dos Santos; GRR:20203906

#!/bin/bash

CPU=3

mkdir tabelas #cria pasta tabelas

# Gera arquivos .csv com saida do likwid
for size in "${tamanhos[@]}"; do
    for grp in "${grupos[@]}"; do
        ./perfctr.sh $CPU "$grp" "$size"
    done
done

for size in "${tamanhos[@]}"; do
    awk -v size="$size" -F'=' '{tempo = (tempo == "") ? $2: tempo ", " $2} END {print size ", " tempo}' ./saida.txt >> TEMPOS.csv
done

# rm *.csv

# for size in "${tamanhos[@]}"; do
#     ./ajustePol "$size" > saida.txt
#     awk -v size="$size" -F'=' '{tempo = (tempo == "") ? $2: tempo ", " $2} END {print size ", " tempo}' ./saida.txt >> TEMPOS.csv
# done
entrada=$(cat $1)

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make

    echo $entrada | likwid-perfctr -C ${CPU} -g FLOPS_DP -m ./ajustePol | grep -B1 -e "\[[0-9]\|\([0-9]\)\{8\}e\|Group\|AVX DP"
    echo -e "\n"
    echo $entrada | likwid-perfctr -C ${CPU} -g ENERGY -m ./ajustePol | grep -e "Group\|Energy \["

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor