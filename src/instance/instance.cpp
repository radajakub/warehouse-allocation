#include "./instance.h"

Instance::Instance() {}

void Instance::print() {
    std::cout << "warehouses (N) : " << this->N << std::endl;
    std::cout << "customers  (M) : " << this->M << std::endl;
    for (unsigned int w = 0; w < this->N; ++w) std::cout << "warehouse " << w << " : " << this->get_capacity(w) << " (capacity) " << this->get_setup(w) << " (set-up cost)" << std::endl;
    for (unsigned int c = 0; c < this->M; ++c) {
        std::cout << "customer " << c << " : " << this->get_demand(c) << " (demand)" << std::endl << "    ";
        for (unsigned int w = 0; w < this->N; ++w) std::cout << this->get_cost(c, w) << " ";
        std::cout << std::endl;
    }
}

void Instance::init(unsigned int M, unsigned int N) {
    this->M = M;
    this->N = N;
    this->cap_w.resize(N);
    this->s_w.resize(N);
    this->d_c.resize(M);
    this->t_cw.resize(M);
    for (std::vector<double>& v : this->t_cw) v.resize(N);
    this->range = std::uniform_int_distribution<unsigned int>(0, N - 1);
    this->positions = std::uniform_int_distribution<unsigned int>(0, M - 1);
}

void load(std::string file, Instance& instance) {
    std::ifstream f(file);
    if (!f.is_open()) {
        std::cerr << "specified file does not exist" << std::endl;
    } else {
        // load warehouse and customer counts
        unsigned int N;
        unsigned int M;
        f >> N >> M;
        instance.init(M, N);

        // load warehouse properties
        unsigned int cap;
        double setup_cost;
        for (unsigned int w = 0; w < N; ++w) {
            f >> cap >> setup_cost;
            instance.add_capacity(w, cap);
            instance.add_setup(w, setup_cost);
        }

        // load customer properties
        unsigned int demand;
        double delivery_cost;
        for (unsigned int c = 0; c < M; ++c) {
            f >> demand;
            instance.add_demand(c, demand);
            for (unsigned int w = 0; w < N; ++w) {
                f >> delivery_cost;
                instance.add_cost(c, w, delivery_cost);
            }
        }
    }
}

