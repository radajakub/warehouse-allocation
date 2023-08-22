#ifndef SPECIALIZED_H
#define SPECIALIZED_H

#include <algorithm>
#include <cmath>
#include <random>
#include <vector>
#include "../randomization.h"
#include "../candidate/candidate.h"
#include "../state.h"
#include "../heuristics/heuristics.h"
#include "../local_search/local_search.h"

namespace specialized {

    struct settings {
        double penalty;
        unsigned int dimension;
        unsigned int population_size;
        unsigned int tournament_size;
        unsigned int select_n;
        double cross_prob;
        double mutation_prob;
        double shuffle_prob;
        unsigned int local_search;
    };

    inline bool comp(Candidate& c1, Candidate& c2, double penalty) { return c1.total(penalty) < c2.total(penalty); }

    Candidate evolve(Instance& instance, settings& settings);

    std::vector<Candidate> breed(Instance& instance, std::vector<Candidate>& population, settings& s);

    std::vector<Candidate> init(Instance& instance, settings& s);

    Candidate find_bsf(std::vector<Candidate>& population, settings& s);

    void evaluate_population(std::vector<Candidate>& population);

    std::vector<Candidate> join(std::vector<Candidate>& population1, std::vector<Candidate>& population2, settings& s);

    namespace cross {
        void single_point(Candidate& parent1, Candidate& parent2, Candidate& offspring1, Candidate& offspring2, std::uniform_int_distribution<unsigned int>& dist);
        void two_point(Candidate& parent1, Candidate& parent2, Candidate& offspring1, Candidate& offspring2, std::uniform_int_distribution<unsigned int>& dist);
        void uniform(Candidate& parent1, Candidate& parent2, Candidate& offspring1, Candidate& offspring2);
    };

};

#endif

