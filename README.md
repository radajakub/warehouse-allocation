# README

./data/ - contains instances of the problem and their description
./report/ - contains report .tex files, .pdf file and scripts for plotting or for transforming algorithm outputs into latex tables
./res/ - folder containing results of running algorithms
./src/ - contains source files of the algorithms

# compilation

To compile the code, create folder ./out/, `cd` into it and execute `cmake .. && make`.

# output options

The algorithms can output results into file or into `stdout`.
To change this, in each solver main file (./src/solvers/*.cpp), there is a macro TO_FILE which controls this output.

# running algorithms

Each algorithm can be run with one argument, to solve only one instance.
The argument is a string containing name of the instance, e.g. "wl_16_1"

When run without any argument, it runs experiments from the report.
(11 runs for each evaluation call limit for each problem instance)

