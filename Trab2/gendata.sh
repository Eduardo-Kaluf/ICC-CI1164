#!/bin/bash

PROG=cgSolver
CPU=3

DATA_DIR="data/"

mkdir -p ${DATA_DIR}

echo "Configurando CPU governor para 'performance'..."
echo "performance" > /sys/devices/system/cpu/cpufreq/policy${CPU}/scaling_governor

# Compila o programa (assumindo que seu 'make lik' faz isso)
make purge
make lik

# Métricas solicitadas: MEM (fallback L3), L2CACHE (fallback L1CACHE), FLOPS_DP, FLOPS_AVX
# Adicionei L3 explicitamente para garantir que os arquivos de tempo possam ser gerados
METRICAS="L3 L2CACHE FLOPS_DP"
TAMANHOS="32"

# Remove a coleta de tempo antiga via printf
# O tempo será extraído do LIKWID
rm -f ${DATA_DIR}/Tempos.csv

for n in $TAMANHOS
do
    for m in ${METRICAS}
    do
        LIKWID_OUT="${DATA_DIR}/${m}_${n}.txt"
        echo "--->> Rodando N=$n, Métrica=$m" >/dev/tty

        # Executa o likwid-perfctr
        # Removemos '>> ${TEMPOS}' pois a saída printf do C não é CSV
        likwid-perfctr -O -C ${CPU} -g ${m} -o ${LIKWID_OUT} -m ./${PROG} ${n}
    done
done

# --- Início da Seção de Pós-Processamento ---

echo "Iniciando pós-processamento dos resultados do LIKWID..."

for m in ${METRICAS}
do
    # Arquivo CSV final para esta métrica
    LIKWID_CSV="${DATA_DIR}/${m}.csv"
    rm -f ${LIKWID_CSV}

    # Define a string da métrica a ser procurada no arquivo .txt
    METRIC_TO_GREP=""
    if [ "$m" = "L3" ]; then
        METRIC_TO_GREP="L3 bandwidth"
    elif [ "$m" = "L2CACHE" ]; then
        METRIC_TO_GREP="L2 miss ratio"
    elif [ "$m" = "FLOPS_DP" ]; then
        METRIC_TO_GREP="DP MFLOP/s"
    elif [ "$m" = "FLOPS_AVX" ]; then
        METRIC_TO_GREP="AVX DP MFLOP/s"
    fi

    if [ -z "$METRIC_TO_GREP" ]; then
        echo "Grupo $m não tem métrica definida para CSV. Pulando." >/dev/tty
        continue
    fi

    echo "Processando grupo: $m. Métrica: $METRIC_TO_GREP. Saída: $LIKWID_CSV" >/dev/tty

    # Escreve o cabeçalho no CSV final
    echo "N,gradiente_${m},residuo_${m}" > ${LIKWID_CSV}

    for n in $TAMANHOS
    do
        LIKWID_OUT="${DATA_DIR}/${m}_${n}.txt"

        if [ ! -f "$LIKWID_OUT" ]; then
            echo "Arquivo não encontrado: $LIKWID_OUT" >/dev/tty
            continue
        fi

        # Extrai a métrica para GRADIENTE_CONJUGADO (somando todas as iterações)
        METRIC_OP1=$(awk -v metric="$METRIC_TO_GREP" '
            BEGIN { region_found=0; total=0 }
            /Region GRANDIENTE_CONJUGADO_/ { region_found=1; }
            /Region / && !/Region GRANDIENTE_CONJUGADO_/ { region_found=0; }
            (region_found==1) && ($0 ~ metric) {
                gsub(/\|/, "");
                total += $NF;
            }
            END { print total }
        ' ${LIKWID_OUT})

        # Extrai a métrica para RESIDUO (valor único)
        METRIC_OP2=$(awk -v metric="$METRIC_TO_GREP" '
            BEGIN { region_found=0; val="NA" }
            /Region RESIDUO_/ { region_found=1; }
            /Region / && !/Region RESIDUO_/ { region_found=0; }
            (region_found==1) && ($0 ~ metric) {
                gsub(/\|/, "");
                val = $NF;
            }
            END { print val }
        ' ${LIKWID_OUT})

        # Coloca 0 se a métrica não for encontrada (total=0)
        if [ -z "$METRIC_OP1" ]; then METRIC_OP1="0"; fi
        if [ "$METRIC_OP2" = "NA" ]; then METRIC_OP2="0"; fi

        # Anexa os dados ao CSV
        echo "${n},${METRIC_OP1},${METRIC_OP2}" >> ${LIKWID_CSV}
    done
done

# --- Nova Seção: Geração de Tempo de Execução ---
echo "Gerando arquivo de tempos (Tempos_em_ms.csv) a partir dos dados do LIKWID (L3)..."

TIME_CSV="${DATA_DIR}/Tempos_em_ms.csv"
METRIC_TO_GREP="Runtime (RDTSC) \[s\]"
REF_METRIC_GROUP="L3" # Usamos L3 como referência para extrair o tempo

echo "N,Tempo_Gradiente_ms,Tempo_Residuo_ms" > ${TIME_CSV}

for n in $TAMANHOS
do
    LIKWID_OUT="${DATA_DIR}/${REF_METRIC_GROUP}_${n}.txt"

    if [ ! -f "$LIKWID_OUT" ]; then
        echo "Arquivo de referência não encontrado: $LIKWID_OUT. Pulando N=$n para tempos." >/dev/tty
        continue
    fi

    # Extrai o TEMPO para GRADIENTE_CONJUGADO (somando todas as iterações e convertendo para ms)
    TIME_OP1=$(awk -v metric="$METRIC_TO_GREP" '
        BEGIN { region_found=0; total_s=0 }
        /Region GRANDIENTE_CONJUGADO_/ { region_found=1; }
        /Region / && !/Region GRANDIENTE_CONJUGADO_/ { region_found=0; }
        (region_found==1) && ($0 ~ metric) {
            gsub(/\|/, "");
            total_s += $NF; # Soma o tempo em segundos
        }
        END { print total_s * 1000 } # Converte para milissegundos
    ' ${LIKWID_OUT})

    # Extrai o TEMPO para RESIDUO (valor único e convertendo para ms)
    TIME_OP2=$(awk -v metric="$METRIC_TO_GREP" '
        BEGIN { region_found=0; val_s=0 }
        /Region RESIDUO_/ { region_found=1; }
        /Region / && !/Region RESIDUO_/ { region_found=0; }
        (region_found==1) && ($0 ~ metric) {
            gsub(/\|/, "");
            val_s = $NF; # Pega o tempo em segundos
        }
        END { print val_s * 1000 } # Converte para milissegundos
    ' ${LIKWID_OUT})

    echo "${n},${TIME_OP1},${TIME_OP2}" >> ${TIME_CSV}
done


echo "--- Processamento Concluído ---"

echo "Restaurando CPU governor para 'powersave'..."
echo "powersave" > /sys/devices/system/cpu/cpufreq/policy${CPU}/scaling_governor

make purge