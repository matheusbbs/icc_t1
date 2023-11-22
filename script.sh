#Nome: Felipe Augusto Dittert Noleto; GRR:20205689
#Nome: Matheus Branco Barreto dos Santos; GRR:20203906

#!/bin/bash

tamanhos=(64 128) # 200 256 512 600 800 1024 2000 3000 4098 6000 7000 10000 50000 100000 1000000 1000000 10000000)

grupos=("FLOPS_DP") # "L3" "L3CACHE" )

CPU=3

mkdir tabelas #cria pasta tabelas

# Gera arquivos .csv com saida do likwid para todos os grupos e tamanhos
for size in "${tamanhos[@]}"; do
    for grp in "${grupos[@]}"; do
        ./perfctr.sh $CPU "$grp" "$size"
    done
done

rm *.csv

for size in "${tamanhos[@]}"; do
    tempo=$(./gera_entrada "$size" | ./ajustePol)
    echo "$tempo" | awk -v size="$size" -F'=' '{tempo = (tempo == "") ? $2: tempo ", " $2} END {print size ", " tempo}' >> TEMPOS.csv
done