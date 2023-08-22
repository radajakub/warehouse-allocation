#ifndef HEURISTICS_H
#define HEURISTICS_H

#include <limits>
#include "../candidate/candidate.h"

namespace heuristics {

    void best_fixed_customer(Instance& i, Candidate& candidate, unsigned int customer);

    void best_random(Instance& i, Candidate& candidate);

    void improve_most_violating(Instance& i, Candidate& candidate);

    void improve_violating(Instance& i, Candidate& candidate);

    void best_swap_two(Instance& i, Candidate& candidate);
    
    void random_swap_two(Instance& i, Candidate& candidate);

}

#endif

