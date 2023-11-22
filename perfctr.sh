#!/bin/bash

# Forma de uso:
#
#         perfctr <CORE_ID> <GRUPO_PERFORMANCE> <tamanho>
#
# Exemplo, para fazer as medições de performance de FLOPS_DP no core 3
#
#         perfctr 3 FLOPS_DP 64
#

cpu=$1
grupo=$2
tamanho=$3

LIKWID_CMD="likwid-perfctr -C "$cpu" -g "$grupo" -m -O --output ./tabelas/"$grupo""$tamanho".csv"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy"$cpu"/scaling_governor

echo "testando "$grupo" para o tamanho "$tamanho""
./gera_entrada "$tamanho" | ${LIKWID_CMD} ./ajustePol > saida.txt #executa likwid e salva csv em ./tabelas
cat saida.txt >> ./tabelas/"$grupo""$tamanho".csv

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy"$cpu"/scaling_governor

# Para obter topologia dos cpu's
#      likwid-topology -c -g

# Para obter lista de grupos de indicadores de performance:
#      likwid-perfctr -a

# Para obter lista de Eventos e Contadores
#      likwid-perfctr -e

