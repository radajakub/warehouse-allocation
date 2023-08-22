#ifndef INSTANCE_H
#define INSTANCE_H

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../randomization.h"

class Instance {
    private: 
        unsigned int N; // warehouses
        unsigned int M; // customers
        std::vector<unsigned int> cap_w; // capacity
        std::vector<double> s_w; // set-up cost
        std::vector<unsigned int> d_c; // customer demands
        std::vector<std::vector<double>> t_cw; // cost of delievering to i-th customer from j-th warehouse

        std::uniform_int_distribution<unsigned int> range;
        std::uniform_int_distribution<unsigned int> positions;

    public:
        Instance();

        void print();
        void init(unsigned int N, unsigned int M);

        inline unsigned int random_warehouse() { return this->range(gen); }
        inline unsigned int random_customer() { return this->positions(gen); }

        inline unsigned int get_N() { return this->N; }
        inline unsigned int get_M() { return this->M; }

        inline void add_capacity(unsigned int warehouse, unsigned int capacity) { this->cap_w[warehouse] = capacity; }
        inline unsigned int get_capacity(unsigned int warehouse) { return this->cap_w[warehouse]; }

        inline void add_setup(unsigned int warehouse, double setup) { this->s_w[warehouse] = setup; }
        inline double get_setup(unsigned int warehouse) { return this->s_w[warehouse]; }

        inline void add_demand(unsigned int customer, unsigned int demand) { this->d_c[customer] = demand; }
        inline unsigned int get_demand(unsigned int customer) { return this->d_c[customer]; }

        inline void add_cost(unsigned int customer, unsigned int warehouse, double cost) { this->t_cw[customer][warehouse] = cost; }
        inline double get_cost(unsigned int customer, unsigned int warehouse) { return this->t_cw[customer][warehouse]; }
};

void load(std::string file, Instance& instance);

#endif

