import os



for file in "./Dados":
    f = file.open(f, "r")

    lines = f.readlines()


    if (file[0:5] == "ENERGY"):
        for line in lines:
            if line[0:10] == "Energy [J]":
                

    else if (file[0:5] == "FLOPS"):

    else if (file[0:7] == "L3CACHE"):
