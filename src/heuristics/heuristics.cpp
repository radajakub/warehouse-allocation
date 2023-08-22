#include "./heuristics.h"

void heuristics::best_fixed_customer(Instance& i, Candidate& candidate, unsigned int customer) {
    Candidate x = candidate;
    for (unsigned int w = 0; w < i.get_N(); ++w) {
        x.assign_warehouse(customer, w);
        x.evaluate();
        if (isbetter(x, candidate)) candidate = x;
    }
}

void heuristics::best_random(Instance& i, Candidate& candidate) {
    heuristics::best_fixed_customer(i, candidate, i.random_customer());
}

void heuristics::improve_most_violating(Instance& i, Candidate& candidate) {
    unsigned int w_worst;
    unsigned int worst = std::numeric_limits<unsigned int>::min();
    for (unsigned int w = 0; w < i.get_N(); ++w) {
        if (candidate.get_constraints()[w] > worst) {
            w_worst = w;
            worst = candidate.get_constraints()[w];
        }
    }
    for (unsigned int c = 0; c < i.get_M(); ++c) {
        if (candidate.get_chromosome()[c] == w_worst) {
            Candidate x = candidate;
            x.mutate_one(c);
            x.evaluate();
            if (isbetter(x, candidate)) candidate = x;
        }
    }
}

void heuristics::improve_violating(Instance& i, Candidate& candidate) {
    for (unsigned int c = 0; c < i.get_M(); ++c) {
        if (candidate.get_constraints()[candidate.get_chromosome()[c]]) {
            Candidate x = candidate;
            x.mutate_one(c);
            x.evaluate();
            if (isbetter(x, candidate)) candidate = x;
        }
    }
}

void heuristics::best_swap_two(Instance& i, Candidate& candidate) {
    Candidate x = candidate;
    unsigned int to_swap = i.random_customer();
    for (unsigned int c = 0; c < i.get_M(); ++c) {
        x.swap_customers(c, to_swap);
        x.evaluate();
        if (isbetter(x, candidate)) candidate = x;
        x.swap_customers(c, to_swap);
    }
}

void heuristics::random_swap_two(Instance& i, Candidate& candidate) {
    unsigned int fst = i.random_customer();
    unsigned int snd = i.random_customer();
    candidate.swap_customers(fst, snd);
}

