import sys
from os import listdir
from os.path import isfile, join
from statistics import median

ranges = [1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000]
problems = ["wl_16_1", "wl_25_2", "wl_50_1", "wl_100_4", "wl_200_1", "wl_500_1", "wl_1000_1", "wl_2000_1"]

if __name__ == "__main__":
    alg = sys.argv[1]
    for p in problems:
        print("\\begin{table}")
        print("    \\centering")
        print("    \\tiny")
        print("    \\begin{tabular}{ c | c | c | c | c | c }")
        print("        evaluations & generations & time & violations & objective & ratio with optimum \\\\")
        print("        \\hline")

        for r in ranges:
            print("        \\hline")
            file = "../res/" + alg + "_" + str(r) + "_" + p
            row = [""] * 6
            rows = []
            values = []
            with open(file, "r") as f:
                for line in f.readlines():
                    if line == '\n':
                        rows.append(row.copy())
                    else:
                        parts = line.split(": ")
                        if len(parts) == 1:
                            row[5] = parts[0].strip()
                        elif parts[0] == "objective":
                            value = float(parts[1].strip())
                            row[4] = str(value)
                            values.append(value)
                        elif parts[0] == "constraint violations":
                            row[3] = parts[1].strip()
                        elif parts[0] == "time":
                            row[2] = parts[1].strip()
                        elif parts[0] == "iterations":
                            row[1] = parts[1].strip()
                        elif parts[0] == "evaluations":
                            row[0] = parts[1].strip()
            med = median(values)
            for rowrow in rows:
                if float(rowrow[4]) == med:
                    print("        \\rowcolor{lightgray} " + " & ".join(rowrow) + " \\\\")
                else:
                    print("        " + " & ".join(rowrow) + " \\\\")

        print("    \\end{tabular}")
        print("    \\caption{" + p + "}")
        print("\\end{table}")

