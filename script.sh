#Nome: Felipe Augusto Dittert Noleto; GRR:20205689
#Nome: Matheus Branco Barreto dos Santos; GRR:20203906

#!/bin/bash

tamanhos=(64 128) # 200 256 512 600 800 1024 2000 3000 4098 6000 7000 10000 50000 100000 1000000 1000000 10000000)

grupos=("FLOPS_DP") # "L3" "L3CACHE" )

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

for size in "${tamanhos[@]}"; do
    for grp in "${grupos[@]}"; do
        ./perfctr.sh $CPU "$grp" "$size"
    done
done

# rm *.csv

# for size in "${tamanhos[@]}"; do
#     ./ajustePol "$size" > saida.txt
#     awk -v size="$size" -F'=' '{tempo = (tempo == "") ? $2: tempo ", " $2} END {print size ", " tempo}' ./saida.txt >> TEMPOS.csv
# done