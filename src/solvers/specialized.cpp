#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "../candidate/candidate.h"
#include "../instance/instance.h"
#include "../specialized/specialized.h"
#include "../problems.h"
#include "../timer.h"
#include "../state.h"
#include "../out.h"

#define TO_FILE (true)

int main(int argc, char** argv) {

    Timer t;

    specialized::settings settings = {
        .penalty = 1000,
        .dimension = 0,
        .population_size = 20,
        .tournament_size = 4,
        .select_n = 5,
        .mutation_prob = 0.2,
        .shuffle_prob = 0.6,
        .local_search = 100,
    };

    if (argc > 1) {

        std::string problem = argv[1];

        std::stringstream name;
        name << "../data/" << problem;

        Instance instance;
        load(name.str(), instance);

        settings.dimension = instance.get_M();

        state.reset();
        state.set_limit(10000);

        t.start();

        Candidate bsf = specialized::evolve(instance, settings);

        t.stop();

        #if TO_FILE
        to_file("specialized", problem, bsf, t);
        #else
        to_stdout(problem, bsf, t);
        #endif

    } else {

        std::vector<unsigned int> limits = {1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000};

        for (unsigned int l : limits) {
            state.set_limit(l);

            for (std::string problem : files) {

                for (unsigned int i = 0; i < 1; ++i) {
                    state.reset();

                    std::cout << "solving specialized " << problem << " " << l << " " << i << std::endl;

                    std::stringstream name;
                    name << "../data/" << problem;

                    Instance instance;
                    load(name.str(), instance);

                    settings.dimension = instance.get_M();

                    t.start();
                    Candidate bsf = specialized::evolve(instance, settings);
                    t.stop();

                    #if TO_FILE
                    to_file("specialized", problem, bsf, t);
                    #else
                    to_stdout(problem, bsf, t);
                    #endif
                }
            }
        }
    }

    return 0;
}
