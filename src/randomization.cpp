#include "./randomization.h"

std::random_device rd {};
std::mt19937 gen { rd() };

std::uniform_real_distribution<double> prob(0, 1);

double random_prob() {
    return prob(gen);
}
