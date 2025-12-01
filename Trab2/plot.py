# Seu código de importação e carregamento de dados
# ... (deve permanecer como está)

import matplotlib.pyplot as plt
import numpy as np # Necessário para a escala logarítmica
import os
import csv

data_dir = "./data"
optimized = "Optimized"
nonOptimized = "NonOptimized"

allData = {
    "gradient": {
        "optimized": {},
        "nonOptimized": {}
    },
    "residue": {
        "optimized": {},
        "nonOptimized": {}
    }
}

metrics = []
for file in os.listdir(f"{data_dir}/{optimized}"):
    filename = os.fsdecode(file)
    if filename.endswith(".csv"):
        metrics.append(filename)

        for op in allData.keys():
            for ver in allData[op].keys():
                allData[op][ver][filename] = {}

        with open(f"{data_dir}/{optimized}/{filename}", mode ='r') as f:
            next(f)
            csvFile = csv.reader(f)
            for lines in csvFile:
                N = lines[0]
                allData["gradient"]["optimized"][filename][N] = float(lines[1])
                allData["residue"]["optimized"][filename][N] = float(lines[2])

        with open(f"{data_dir}/{nonOptimized}/{filename}", mode ='r') as f:
            next(f)
            csvFile = csv.reader(f)
            for lines in csvFile:
                N = lines[0]
                allData["gradient"]["nonOptimized"][filename][N] = float(lines[1])
                allData["residue"]["nonOptimized"][filename][N] = float(lines[2])

n_vals_str = ["32", "64", "128", "256", "512", "1000", "2000", "4000", "8000", "9000", "10000", "20000"]
n_vals = np.array([int(n) for n in n_vals_str])

OP_MAP = {
    "gradient": {"id": "op1", "label": "Gradiente", "color_opt": "blue", "color_nonopt": "red"},
    "residue": {"id": "op2", "label": "Resíduo", "color_opt": "green", "color_nonopt": "orange"}
}

for operation, op_info in OP_MAP.items():

    for metric in metrics:
        metric_title = str.title(metric[0:-4].replace("_", " "))

        values_opt = [allData[operation]["optimized"][metric][n] for n in n_vals_str]
        values_nonopt = [allData[operation]["nonOptimized"][metric][n] for n in n_vals_str]

        fig, axs = plt.subplots(1, 1, figsize=(12, 6))

        fig.suptitle(f"{metric_title} por Tamanho do SL - {op_info['label']} ", fontsize=14)

        axs.plot(n_vals, values_opt,
                 marker='o', linestyle='-', color=op_info['color_opt'],
                 label ='v2 - Otimizada')

        axs.plot(n_vals, values_nonopt,
                 marker='x', linestyle='--', color=op_info['color_nonopt'],
                 label ='v1 - Não Otimizada')

        axs.set_xlabel('Tamanho do Sistema Linear (N)', fontsize=12)
        axs.set_ylabel(metric_title, fontsize=12)

        axs.set_xscale('log')

        axs.set_xticks(n_vals)
        axs.set_xticklabels(n_vals)

        axs.grid(True, which="both", ls="--", linewidth=0.5) # Adiciona um grid
        axs.legend(title="Versão do Código")

        plt.tight_layout(rect=[0, 0.03, 1, 0.95]) # Ajusta para o título
        filename = f"{op_info['id']}_{operation}_{metric_title.replace(' ', '_')}.png"

        plt.savefig(f"graphs/{filename}", dpi=300)

        plt.close(fig)
