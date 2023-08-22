#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include "../instance/instance.h"
#include "../state.h"

struct fitness {
    double objective;
    unsigned int constraint_violations;
};

class Candidate {
    private:
        Instance* instance;

        unsigned int N; // warehouse count
        unsigned int M; // customer count

        /* warehouse assigned to each customer */
        std::vector<unsigned int> chromosome; // length M, domain {0, ..., M-1}

        /*
         * represents individual violations of constraints
         * sum of demands of customers assigned to a warehouse does not exceed its capacity
         */
        std::vector<unsigned int> constraints;
        std::vector<unsigned int> demands;

    public:
        Candidate(Instance* instance);

        fitness f;

        inline unsigned int get_violations() { return this->f.constraint_violations; }
        inline unsigned int get_objective() { return this->f.objective; }

        inline std::vector<unsigned int>& get_chromosome() { return this->chromosome; }
        inline void set_chromosome(std::vector<unsigned int>& chromosome) { this->chromosome = chromosome; }

        inline std::vector<unsigned int>& get_constraints() { return this->constraints; }

        void print();
        void short_print();
        void short_print(std::ofstream& out);
        void print_chromosome();

        void random_init();
        void best_init();
        void best_init(unsigned int k);

        void evaluate();

        inline double total(double penalty) { return this->f.objective + penalty * this->f.constraint_violations; }

        inline void assign_warehouse(unsigned int customer, unsigned int warehouse) { this->chromosome[customer] = warehouse; }

        void mutate_n(unsigned int num_to_switch);
        void mutate_one(unsigned int client);
        void mutate_probabilistic(double probability);
        void mutate_shuffle();
        void mutate_worst();

        void swap_customers(unsigned int c1, unsigned int c2);
};

bool isbetter(fitness& f1, fitness& f2);
inline bool isbetter(Candidate& c1, Candidate& c2) { return isbetter(c1.f, c2.f); }

bool same(Candidate& c1, Candidate& c2);

#endif
