cmake_minimum_required(VERSION 3.21)
project(eoa)

set(cmake_cxx_standard 17)

set(cmake_cxx_flags "${cmake_cxx_flags} -O3 -fopenmp")

add_executable(
    ls
    src/solvers/ls.cpp
    src/instance/instance.cpp
    src/problems.cpp
    src/heuristics/heuristics.cpp
    src/local_search/local_search.cpp
    src/candidate/candidate.cpp
    src/randomization.cpp
    src/state.cpp
    src/out.cpp
)

add_executable(
    ea
    src/solvers/ea.cpp
    src/instance/instance.cpp
    src/problems.cpp
    src/heuristics/heuristics.cpp
    src/ea/ea.cpp
    src/candidate/candidate.cpp
    src/randomization.cpp
    src/state.cpp
    src/out.cpp
)

add_executable(
    specialized
    src/solvers/specialized.cpp
    src/instance/instance.cpp
    src/problems.cpp
    src/heuristics/heuristics.cpp
    src/local_search/local_search.cpp
    src/specialized/specialized.cpp
    src/candidate/candidate.cpp
    src/randomization.cpp
    src/state.cpp
    src/out.cpp
)

