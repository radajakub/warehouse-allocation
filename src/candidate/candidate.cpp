#include "./candidate.h"

Candidate::Candidate(Instance* instance) {
    this->instance = instance;
    this->N = instance->get_N();
    this->M = instance->get_M();
    this->chromosome.resize(M);
    this->constraints = std::vector<unsigned int>(this->N);
    this->demands = std::vector<unsigned int>(this->N);
    this->f = {
        .objective = std::numeric_limits<double>::infinity(),
        .constraint_violations = 0,
    };
}

void Candidate::print() {
    std::cout << "==== chromosome (customer : warehouse) ====" << std::endl << "[";
    for (unsigned int c = 0; c < this->M; ++c) {
        if (c) std::cout << ", ";
        std::cout << c << " : " << this->chromosome[c];
    }
    std::cout << "]" << std::endl;
    std::cout << "objective: " << this->f.objective << std::endl;
    std::cout << "constraint violations: " << this->f.constraint_violations << " [";
    for (unsigned int w = 0; w < this->N; ++w) {
        if (w) std::cout << ", ";
        std::cout << this->constraints[w];
    }
    std::cout << "] " << std::endl;
}

void Candidate::short_print() {
    std::cout << "objective: " << this->f.objective << std::endl;
    std::cout << "constraint violations: " << this->f.constraint_violations << std::endl;
}

void Candidate::short_print(std::ofstream& out) {
    out << "objective: " << this->f.objective << std::endl;
    out << "constraint violations: " << this->f.constraint_violations << std::endl;
}

void Candidate::print_chromosome() {
    std::cout << "[";
    for (unsigned int i = 0; i < this->chromosome.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << this->chromosome[i];
    }
    std::cout << "]" << std::endl;
}

void Candidate::random_init() {
    for (unsigned int c = 0; c < this->M; ++c) this->chromosome[c] = this->instance->random_warehouse();
}

void Candidate::best_init() {
    unsigned int w_best;
    double val;
    double val_best;
    for (unsigned int c = 0; c < this->M; ++c) {
        val_best = std::numeric_limits<double>::max();
        for (unsigned int w = 0; w < this->N; ++w) {
            val = this->instance->get_cost(c, w);
            if (val < val_best) {
                val_best = val;
                w_best = w;
            }
        }
        this->chromosome[c] = w_best;
    }
}

void Candidate::best_init(unsigned int k) {
    double val;
    double val_best;
    std::vector<unsigned int> bests(k);
    std::uniform_int_distribution<unsigned int> idx(0, k - 1);

    for (unsigned int c = 0; c < this->M; ++c) {

        std::fill(begin(bests), end(bests), this->N);

        for (unsigned int i = 0; i < k; ++i) {
            val_best = std::numeric_limits<double>::max();
            for (unsigned int w = 0; w < this->N; ++w) {
                val = this->instance->get_cost(c, w);
                if (val < val_best && std::find(begin(bests), end(bests), w) == end(bests)) {
                    val_best = val;
                    bests[i] = w;
                }
            }

        }
        this->chromosome[c] = bests[idx(gen)];
    }
}

void Candidate::evaluate() {
    this->f.constraint_violations = 0;
    this->f.objective = 0;
    this->demands = std::vector<unsigned int>(this->N, 0);
    unsigned int w;
    for (unsigned int c = 0; c < this->M; ++c) {
        w = this->chromosome[c];
        this->f.objective += this->instance->get_cost(c, w);
        this->demands[w] += this->instance->get_demand(c);
    }
    unsigned int capacity;
    unsigned int demands;
    unsigned int diff;
    for (unsigned int w = 0; w < this->N; ++w) {
        if (this->demands[w]) this->f.objective += this->instance->get_setup(w);
        capacity = this->instance->get_capacity(w);
        demands = this->demands[w];
        diff = demands <= capacity ? 0 : demands - capacity;
        this->constraints[w] = diff;
        this->f.constraint_violations += diff;
    }

    state.count_evaluations();
}


void Candidate::swap_customers(unsigned int c1, unsigned int c2) {
    unsigned int w1 = this->chromosome[c1];
    unsigned int w2 = this->chromosome[c1];
    this->assign_warehouse(c1, w2);
    this->assign_warehouse(c2, w1);
}

void Candidate::mutate_n(unsigned int num_to_switch) {
    for (unsigned int n = 0; n < num_to_switch; ++n) this->assign_warehouse(this->instance->random_customer(), this->instance->random_warehouse());
}

void Candidate::mutate_one(unsigned int client) {
    this->assign_warehouse(client, this->instance->random_warehouse());
}

void Candidate::mutate_probabilistic(double probability) {
    for (unsigned int c = 0; c < this->M; ++c) if (random_prob() < probability) this->assign_warehouse(c, this->instance->random_warehouse());
}

void Candidate::mutate_shuffle() {
    std::random_shuffle(begin(this->chromosome), end(this->chromosome));
}

void Candidate::mutate_worst() {
    double max_cost = std::numeric_limits<double>::min();
    unsigned int worst_c = 0;
    double cost;
    for (unsigned int c = 0; c < this->M; ++c) {
        cost = this->instance->get_cost(c, this->chromosome[c]);
        if (cost > max_cost) {
            max_cost = cost;
            worst_c = c;
        }
    }

    double min_cost = std::numeric_limits<double>::max();
    unsigned int best_w = 0;
    for (unsigned int w = 0; w < this->N; ++w) {
        cost = this->instance->get_cost(worst_c, w);
        if (cost < min_cost) {
            min_cost = cost;
            best_w = w;
        }
    }
    this->chromosome[worst_c] = best_w;
}

bool isbetter(fitness& f1, fitness& f2) {
    if (f1.constraint_violations == f2.constraint_violations) return f1.objective < f2.objective;
    else return f1.constraint_violations < f2.constraint_violations;
}

bool same(Candidate& c1, Candidate& c2) {
    for (unsigned int i = 0; i < c1.get_chromosome().size(); ++i) if (c1.get_chromosome()[i] != c2.get_chromosome()[i]) return false;
    return true;
}

