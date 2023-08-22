#include "./ea.h"
#include <algorithm>

Candidate ea::evolve(Instance& instance, ea::settings& settings) {
    std::vector<Candidate> x = ea::init(instance, settings);
    ea::evaluate_population(x);

    Candidate bsf = ea::find_bsf(x, settings);

    for (unsigned int i = 0; i < state.iterations(); ++i) {

        std::vector<Candidate> xn = ea::breed(instance, x, settings);

        ea::evaluate_population(xn);

        if (state.enough()) break;

        Candidate xnbsf = ea::find_bsf(xn, settings);

        if (ea::comp(xnbsf, bsf, settings.penalty)) {
            bsf = xnbsf;
            i = 0;
        }

        x = ea::join(x, xn, settings);

        state.count();
    }

    return bsf;
}

std::vector<Candidate> ea::breed(Instance& instance, std::vector<Candidate>& population, ea::settings& s) {
    std::uniform_int_distribution<unsigned int> tournament(0, s.population_size - 1);
    // tournament selection
    std::vector<unsigned int> parents(s.select_n);
    for (unsigned int i = 0; i < s.select_n; ++i) {
        unsigned int winner = tournament(gen);
        for (unsigned int n = 1; n < s.tournament_size; ++n) {
            unsigned int contenstant = tournament(gen);
            if (ea::comp(population[contenstant], population[winner], s.penalty)) winner = contenstant;
        }
        parents[i] = winner;
    }


    // crossover
    std::uniform_int_distribution<unsigned int> position(1, s.dimension - 2);
    std::vector<Candidate> offsprings;
    offsprings.reserve(std::pow(s.select_n, 2));
    for (unsigned int i = 0; i < s.select_n - 1; ++i) {
        for (unsigned int j = i + 1; j < s.select_n; ++j) {
            Candidate o1(&instance);
            Candidate o2(&instance);
            ea::cross::single_point(population[parents[i]], population[parents[j]], o1, o2, position);
            offsprings.push_back(o1);
            offsprings.push_back(o2);
        }
    }

    // mutation
    for (unsigned int i = 0; i < offsprings.size(); ++i) {
        double p = random_prob();
        if (p < s.mutation_prob) {
            offsprings[i].mutate_n(1);
        } else if (p < s.mutation_prob + s.shuffle_prob) {
            offsprings[i].mutate_shuffle();
        }
    }

    return offsprings;
}

void ea::cross::single_point(Candidate& parent1, Candidate& parent2, Candidate& offspring1, Candidate& offspring2, std::uniform_int_distribution<unsigned int>& dist) {
            unsigned int point = dist(gen);

            std::vector<unsigned int> p1 = parent1.get_chromosome();
            std::vector<unsigned int> p2 = parent2.get_chromosome();

            std::vector<unsigned int> res1;
            std::vector<unsigned int> res2;

            res1.insert(res1.end(), p1.begin(), p1.begin() + point);
            res1.insert(res1.end(), p2.begin() + point, p2.end());
            res2.insert(res2.end(), p2.begin(), p2.begin() + point);
            res2.insert(res2.end(), p1.begin() + point, p1.end());

            offspring1.set_chromosome(res1);
            offspring2.set_chromosome(res2);
}

void ea::cross::two_point(Candidate& parent1, Candidate& parent2, Candidate& offspring1, Candidate& offspring2, std::uniform_int_distribution<unsigned int>& dist) {
            unsigned int one = dist(gen);
            unsigned int two = dist(gen);
            unsigned int left = std::min(one, two);
            unsigned int right = std::max(one, two);

            std::vector<unsigned int> res1;
            std::vector<unsigned int> res2;
            std::vector<unsigned int>& p1 = parent1.get_chromosome();
            std::vector<unsigned int>& p2 = parent2.get_chromosome();

            res1.insert(res1.end(), p1.begin(), p1.begin() + left);
            res1.insert(res1.end(), p2.begin() + left, p2.begin() + right);
            res1.insert(res1.end(), p1.begin() + right, p1.end());

            res2.insert(res2.end(), p2.begin(), p2.begin() + left);
            res2.insert(res2.end(), p1.begin() + left, p1.begin() + right);
            res2.insert(res2.end(), p2.begin() + right, p2.end());

            offspring1.set_chromosome(res1);
            offspring2.set_chromosome(res2);
}

std::vector<Candidate> ea::join(std::vector<Candidate>& population1, std::vector<Candidate>& population2, ea::settings& s) {
    std::vector<Candidate> replaced;
    replaced.reserve(s.population_size);
    replaced.insert(end(replaced), begin(population2), end(population2));
    Candidate bsf = find_bsf(population1, s);
    replaced.push_back(bsf);

    std::uniform_int_distribution<unsigned int> tournament(0, population1.size() - 1);
    while (replaced.size() < s.population_size) {
        unsigned int winner = tournament(gen);
        for (unsigned int n = 1; n < s.tournament_size; ++n) {
            unsigned int contenstant = tournament(gen);
            if (ea::comp(population1[contenstant], population1[winner], s.penalty)) winner = contenstant;
        }
        replaced.push_back(population1[winner]);
    }

    return replaced;
}

std::vector<Candidate> ea::init(Instance& instance, ea::settings& s) {
    std::vector<Candidate> population;
    population.reserve(s.population_size);

    for (unsigned int i = 0; i < s.population_size; ++i) {
        Candidate c(&instance);
        c.random_init();
        population.push_back(c);
    }

    return population;
}

Candidate ea::find_bsf(std::vector<Candidate>& population, ea::settings& s) {
    Candidate bsf = population[0];
    for (unsigned int i = 1; i < population.size(); ++i) if (ea::comp(population[i], bsf, s.penalty)) bsf = population[i];
    return bsf;
}

void ea::evaluate_population(std::vector<Candidate>& population) {
    for (unsigned int i = 0; i < population.size(); ++i) population[i].evaluate();
}

