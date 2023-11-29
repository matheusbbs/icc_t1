#Nome: Felipe Augusto Dittert Noleto; GRR:20205689
#Nome: Matheus Branco Barreto dos Santos; GRR:20203906

#!/bin/bash

tamanhos=(64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000) # 1000000 10000000 100000000)

grupos=("FLOPS_DP" "L3" "L2CACHE" )

CPU=3

mkdir -p tabelas #cria pasta tabelas
mkdir -p dados #cria pasta para dados das tabelas
mkdir -p graficos # pasta com graficos

# Gera arquivos .csv com saida do likwid para todos os grupos e tamanhos
for size in "${tamanhos[@]}"; do
    for grp in "${grupos[@]}"; do
        ./perfctr.sh $CPU "$grp" "$size"
    done
done

rm ./dados/*.csv
rm ./graficos/*.png

# gera TEMPOS.csv
for size in "${tamanhos[@]}"; do
    tempo=$(./gera_entrada "$size" | ./ajustePol)
    echo "$tempo" | awk -v size="$size" -F'=' '{tempo = (tempo == "") ? $2: tempo ", " $2} END {print size ", " tempo}' >> ./dados/TEMPOS.csv
done

# gera a tabela de L3 bandwidth
for size in "${tamanhos[@]}"; do
    awk -v size="$size" -F',' '$1 == "L3 bandwidth [MBytes/s]" {bandwidth = (bandwidth == "") ? $2: bandwidth ", " $2} END {print size ", " bandwidth}' ./tabelas/L3"$size".csv >> ./dados/L3.csv
done

# gera a tabela de L2 miss ratio
for size in "${tamanhos[@]}"; do
    awk -v size="$size" -F',' '$1 == "L2 miss ratio" {miss = (miss == "") ? $2: miss ", " $2} END {print size ", " miss}' ./tabelas/L2CACHE"$size".csv >> ./dados/L2CACHE.csv
done

# gera a tabela de FLOPS e AVX
for size in "${tamanhos[@]}"; do
     awk -v size="$size" -F',' '/^DP/  || /AVX DP/ {DP = (DP == "") ? $2: DP ", " $2} END {print size ", " DP}' ./tabelas/FLOPS_DP"$size".csv >> ./dados/FLOPS_DP.csv
done

# gera o grafico dos flops da Geracao do Sistema Linear
gnuplot << EOF
set datafile separator ","
set title "Flops Geração do Sistema Linear"
set xlabel "Tamanho"
set ylabel "MFLOP/s"
set xrange [0:5000]
set yrange [0:10000]
set terminal png
set output "./graficos/FlopsGeraSL.png"
plot "./dados/FLOPS_DP.csv" using 1:2 with linespoints title "DP Geração Sistema Linear", \
    "./dados/FLOPS_DP.csv" using 1:3 with linespoints title "AVX Geração Sistema Linear", \
    "./dados/FLOPS_DP.csv" using 1:8 with linespoints title "DP  Geração Sistema Linear Otimizado", \
    "./dados/FLOPS_DP.csv" using 1:9 with linespoints title "AVX Geração Sistema Linear Otimizado"
set output
exit
EOF

# gera o grafico dos flops da Solucao do Sistema Linear
gnuplot << EOF
set datafile separator ","
set title "Flops Solucao do Sistema Linear"
set xlabel "Tamanho"
set ylabel "MFLOP/s"
set xrange [0:5000]
set yrange [0:10000]
set terminal png
set output "./graficos/FlopsSolSL.png"
plot "./dados/FLOPS_DP.csv" using 1:4 with linespoints title "DP Solução Sistema Linear", \
    "./dados/FLOPS_DP.csv" using 1:5 with linespoints title "AVX Solução Sistema Linear", \
    "./dados/FLOPS_DP.csv" using 1:10 with linespoints title "DP Solução Sistema Linear Otimizado", \
    "./dados/FLOPS_DP.csv" using 1:11 with linespoints title "AVX Solução Sistema Linear Otimizado"
set output
exit
EOF


# gera o grafico dos flops do Calculo dos Residuos 
gnuplot << EOF
set datafile separator ","
set title "Flops Solucao do Sistema Linear"
set xlabel "Tamanho"
set ylabel "MFLOP/s"
set xrange [0:5000]
set yrange [0:10000]
set terminal png
set output "./graficos/FlopsResi.png"
plot "./dados/FLOPS_DP.csv" using 1:6 with linespoints title "DP  Calculo Residuos", \
    "./dados/FLOPS_DP.csv" using 1:7 with linespoints title "AVX Calculo Residuos", \
    "./dados/FLOPS_DP.csv" using 1:12 with linespoints title "DP  Calculo Residuos Otimizado", \
    "./dados/FLOPS_DP.csv" using 1:13 with linespoints title "AVX Calculo Residuos Otimizado"
set output
exit
EOF


# gera o grafico dos Tempos Geração Sistema linear
gnuplot << EOF
set datafile separator ","
set title "Tempos Geração Sistema Linear"
set xlabel "Tamanho"
set ylabel "ms"
set xrange [0:5000]
set yrange [0:800000]
set terminal png
set output "./graficos/TemposGeraSL.png"
plot "./dados/TEMPOS.csv" using 1:2 with linespoints title "Geração Sistema Linear", \
    "./dados/TEMPOS.csv" using 1:5 with linespoints title "Geração Sistema Linear Otimizado"
set output
exit
EOF

# gera o grafico dos Tempos Solução Sistema linear
gnuplot << EOF
set datafile separator ","
set title "Tempos Solução Sistema Linear"
set xlabel "Tamanho"
set ylabel "ms"
set xrange [0:5000]
set yrange [0:800000]
set terminal png
set output "./graficos/TemposSolSl.png"
plot "./dados/TEMPOS.csv" using 1:3 with linespoints title "Solução Sistema Linear", \
    "./dados/TEMPOS.csv" using 1:6 with linespoints title "Solução Sistema Linear Otimizado"
set output
exit
EOF

# gera o grafico dos Tempos do Calculo dos residuos
gnuplot << EOF
set datafile separator ","
set title "Tempos Calculo dos residuos"
set xlabel "Tamanho"
set ylabel "ms"
set xrange [0:5000]
set yrange [0:800000]
set terminal png
set output "./graficos/TemposResi.png"
plot "./dados/TEMPOS.csv" using 1:4 with linespoints title "Calculo Residuos", \
    "./dados/TEMPOS.csv" using 1:7 with linespoints title "Calculo Residuos Otimizado"
set output
exit
EOF


# gera o grafico do L2 miss ratio Geração Sistema Linear
gnuplot << EOF
set datafile separator ","
set title "Cache miss ratio Geração Sistema Linear"
set xlabel "Tamanho"
set ylabel "Porcentagem"
set xrange [0:5000]
set yrange [0:1]
set terminal png
set output "./graficos/L2MissGeraSL.png"
plot "./dados/L2CACHE.csv" using 1:2 with linespoints title "Geração Sistema Linear", \
    "./dados/L2CACHE.csv" using 1:5 with linespoints title "Geração Sistema Linear Otimizado"
set output
exit
EOF

# gera o grafico do L2 miss ratio Solução Sistema Linear
gnuplot << EOF
set datafile separator ","
set title "Cache miss ratio Solução Sistema Linear"
set xlabel "Tamanho"
set ylabel "Porcentagem"
set xrange [0:5000]
set yrange [0:1]
set terminal png
set output "./graficos/L2MissSolSL.png"
plot "./dados/L2CACHE.csv" using 1:3 with linespoints title "Solução Sistema Linear", \
    "./dados/L2CACHE.csv" using 1:6 with linespoints title "Solução Sistema Linear Otimizado"
set output
exit
EOF

# gera o grafico do L2 miss ratio Calculo dos Residuos
gnuplot << EOF
set datafile separator ","
set title "Cache miss ratio Calculo dos Residuos"
set xlabel "Tamanho"
set ylabel "Porcentagem"
set xrange [0:5000]
set yrange [0:1]
set terminal png
set output "./graficos/L2MissResi.png"
plot "./dados/L2CACHE.csv" using 1:4 with linespoints title "Calculo dos Residuos", \
    "./dados/L2CACHE.csv" using 1:7 with linespoints title "Calculo dos Residuos Otimizado"
set output
exit
EOF

# gera o grafico de Memory bandwidth Geração Sistema Linear
gnuplot << EOF
set datafile separator ","
set title "Memory bandwidth Geração Sistema Linear"
set xlabel "Tamanho"
set ylabel "MBytes/s"
set xrange [0:5000]
set yrange [0:100000]
set terminal png
set output "./graficos/L3GeraSL.png"
plot "./dados/L3.csv" using 1:2 with linespoints title "Geração Sistema Linear", \
    "./dados/L3.csv" using 1:5 with linespoints title "Geração Sistema Linear"
set output
exit
EOF

# gera o grafico de Memory bandwidth Solução Sistema Linear
gnuplot << EOF
set datafile separator ","
set title "Memory bandwidth Solução Sistema Linear"
set xlabel "Tamanho"
set ylabel "MBytes/s"
set xrange [0:5000]
set yrange [0:100000]
set terminal png
set output "./graficos/L3SolSL.png"
plot "./dados/L3.csv" using 1:3 with linespoints title "Solução Sistema Linear", \
    "./dados/L3.csv" using 1:6 with linespoints title "Solução Sistema Linear Otimizado"
set output
exit
EOF

# gera o grafico de Memory bandwidth Calculo dos Residuos
gnuplot << EOF
set datafile separator ","
set title "Memory bandwidth Calculo dos Residuos"
set xlabel "Tamanho"
set ylabel "MBytes/s"
set xrange [0:5000]
set yrange [0:100000]
set terminal png
set output "./graficos/L3Resi.png"
plot "./dados/L3.csv" using 1:2 with linespoints title "Calculo dos Residuos", \
    "./dados/L3.csv" using 1:3 with linespoints title "Calculo dos Residuos Otimizado"
set output
exit
EOF
