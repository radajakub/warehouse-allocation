#include "./local_search.h"

Candidate ls::search(Instance& instance, double penalty) {
    Candidate x(&instance);
    x.best_init();
    return ls::search(instance, x, penalty);
}

Candidate ls::search(Instance& instance, Candidate& init, double penalty) {
    init.evaluate();
    Candidate x = init;

    for (unsigned int i = 0; i < state.iterations(); ++i) {

        x = init;

        if (x.f.constraint_violations) heuristics::improve_violating(instance, x);
        else x.mutate_n(1);

        x.evaluate();

        if (ls::comp(x, init, penalty)) {
            init = x;
            i = 0;
        }
        if (state.enough()) break;

        state.count();
    }

    return init;
}

