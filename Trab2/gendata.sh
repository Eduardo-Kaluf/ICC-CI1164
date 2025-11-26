#!/bin/bash

# TODO change constants to use in UFPR (Ex. CPU should be 3)

# Constantes
PROG=cgSolver
CPU=0
DATA_DIR="data"
METRICAS="FLOPS_DP"
TAMANHOS="32 64"

# Cria diretório para saída do likwid
mkdir -p ${DATA_DIR}

# TODO rever, possivelmente nao funciona sem sudo
# echo "performance" > /sys/devices/system/cpu/cpufreq/policy${CPU}/scaling_governor

# Compila o programa e limpa diretórios
make purge
make lik
clear
rm -rf ${DATA_DIR}/*

for n in $TAMANHOS
do
    for m in ${METRICAS}
    do
        LIKWID_OUT="${DATA_DIR}/${m}_${n}.txt"
        echo "Rodando Métrica=$m para tamanho N=$n" > /dev/tty

        # Executa o likwid-perfctr e guarda os dados em LIKWID_OUT
        likwid-perfctr -O -C ${CPU} -g ${m} -o ${LIKWID_OUT} -m ./${PROG} ${n}
    done
done

# Geração dos .csv

echo "Gerando CSVs"

for m in ${METRICAS}
do
    #Criando CSV
    LIKWID_CSV="${DATA_DIR}/${m}.csv"

    # Define a string da métrica a ser procurada no arquivo .txt
    METRIC_TO_GREP=""
    if   [ "$m" = "L3" ]; then
        METRIC_TO_GREP="L3 bandwidth"
    elif [ "$m" = "L2CACHE" ]; then
        METRIC_TO_GREP="L2 miss ratio"
    elif [ "$m" = "FLOPS_DP" ]; then
        METRIC_TO_GREP="DP MFLOP/s"
    elif [ "$m" = "FLOPS_AVX" ]; then
        METRIC_TO_GREP="AVX DP MFLOP/s"
    fi

    echo -e "\nProcessando $m. \nMétrica: $METRIC_TO_GREP. \nSaída: $LIKWID_CSV\n" >/dev/tty

    # Escreve o cabeçalho no CSV final
    echo "N,gradiente_${m},residuo_${m}" > ${LIKWID_CSV}

    # Realiza a procura em cada um dos testes realizados
    for n in $TAMANHOS
    do
        LIKWID_OUT="${DATA_DIR}/${m}_${n}.txt"

        if [ ! -f "$LIKWID_OUT" ]; then
            echo "Arquivo não encontrado: $LIKWID_OUT" >/dev/tty
            continue
        fi

        # Extrai a métrica para GRADIENTE_CONJUGADO (somando todas as iterações)
        METRICS=$(grep "$METRIC_TO_GREP" "$LIKWID_OUT")
	
	METRIC_GRADIENTE=$(grep "scalar assumed" "$LIKWID_OUT" | sed -n '1p' | cut -d',' -f2)
	METRIC_RESIDUO=$(grep "scalar assumed" "$LIKWID_OUT" | sed -n '2p' | cut -d',' -f2)

        # Coloca 0 se a métrica não for encontrada
        if [ -z "$METRIC_GRADIENTE" ]; then METRIC_GRADIENTE="0"; fi
        if [ -z "$METRIC_RESIDUO"   ]; then METRIC_RESIDUO="0"; fi

        # Anexa os dados ao CSV
        echo "${n},${METRIC_GRADIENTE},${METRIC_RESIDUO}" >> ${LIKWID_CSV}
    done
done

TIME_CSV="${DATA_DIR}/Exec_time.csv"

echo "N,Tempo_Gradiente_ms,Tempo_Residuo_ms" > ${TIME_CSV}

for n in $TAMANHOS
do
    SAIDA=$(./$PROG $n)
    
    TIME_GRADIENTE=$(echo "$SAIDA" | sed -n '1p')
    TIME_RESIDUO=$(echo "$SAIDA" | sed -n '2p')
    
    echo "${n},${TIME_GRADIENTE},${TIME_RESIDUO}" >> ${TIME_CSV}
done


mkdir -p "${DATA_DIR}/likwid_results/"
mv "${DATA_DIR}"/*.txt "${DATA_DIR}/likwid_results/"


make purge

