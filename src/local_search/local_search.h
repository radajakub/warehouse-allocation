#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include <algorithm>
#include <cmath>
#include "../candidate/candidate.h"
#include "../heuristics/heuristics.h"
#include "../instance/instance.h"
#include "../randomization.h"
#include "../state.h"

namespace ls {

    inline bool comp(Candidate& c1, Candidate &c2, double penalty) { return c1.total(penalty) < c2.total(penalty); }

    Candidate search(Instance& instance, double penalty);
    Candidate search(Instance& instance, Candidate &init, double penalty);

};

#endif

