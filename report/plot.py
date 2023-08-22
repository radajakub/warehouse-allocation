from statistics import mean
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import sys

ranges = [1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000]
rangelabels = ["1e3", "5e3", "1e4", "5e4", "1e5", "5e5", "1e6", "5e6"]
algorithms = ["ls", "ea", "specialized"]
labels = ["local search", "evolution algorithm", "memetic algorithm", "optimal fitness value"]
colors = ["red", "green", "blue", "black"]

optima = {
    "wl_16_1": 976738.625,
    "wl_25_2": 796648.438,
    "wl_50_1": 793439.562,
    "wl_100_4": 17765201.949,
    "wl_200_1": 2686.479,
    "wl_500_1": 2608.148,
    "wl_1000_1": 5283.757,
    "wl_2000_1": 10069.803,
}

if __name__ == "__main__":
    rangelabels.insert(0, '')
    rangelabels.append('')
    for problem in optima.keys():

        plt.figure(figsize=(10, 15))

        for alg in range(len(algorithms)):
            values = []
            means = []

            for r in range(len(ranges)):
                subvalues = []
                file = "../res/" + algorithms[alg] + "_" + str(ranges[r]) + "_" + problem
                with open(file, "r") as f:
                    for line in f.readlines():
                        parts = line.split(": ")
                        if parts[0] == "objective":
                            value = float(parts[1].strip())
                            subvalues.append(value)
                values.append(subvalues)
                means.append(mean(subvalues))

            xes = [x for x in range(1, len(ranges) + 1)]
            plt.plot(xes, means, color=colors[alg], marker='', linestyle='-')
            box = plt.boxplot(values, sym="")

            plt.setp(box['boxes'], color=colors[alg])
            plt.setp(box['caps'], color=colors[alg])
            plt.setp(box['whiskers'], color=colors[alg], linestyle="--")
            plt.setp(box['medians'], color=colors[alg], linestyle="--")

        x = [x for x in range(len(ranges) + 2)]
        plt.plot([min(x), max(x)], [optima[problem], optima[problem]], color="black")

        plt.grid(True, axis='y')
        plt.title(problem)
        plt.ylabel('fitness function')
        plt.xlabel('calls of evaluate function')

        plt.xticks(x, rangelabels)

        plt.legend(loc="upper right", handles=[mpatches.Patch(color=colors[i], label=labels[i]) for i in range(len(algorithms) + 1)])


        plt.savefig("./images/" + problem + ".png", dpi=200)

