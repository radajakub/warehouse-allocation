#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "../candidate/candidate.h"
#include "../instance/instance.h"
#include "../local_search/local_search.h"
#include "../problems.h"
#include "../timer.h"
#include "../state.h"
#include "../out.h"

#define TO_FILE (true)

int main(int argc, char** argv) {

    Timer t;

    if (argc > 1) {

        std::string problem = argv[1];

        std::stringstream name;
        name << "../data/" << problem;

        Instance instance;
        load(name.str(), instance);

        state.reset();
        state.set_limit(10000);

        t.start();

        Candidate c(&instance);
        c.best_init();

        Candidate bsf = ls::search(instance, c, 1000);

        t.stop();

        #if TO_FILE
        to_file("ls", problem, bsf, t);
        #else
        to_stdout(problem, bsf, t);
        #endif

    } else {

        std::vector<unsigned int> limits = {1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000};

        for (unsigned int l : limits) {
            state.set_limit(l);

            for (std::string problem : files) { // files

                for (unsigned int i = 0; i < 1; ++i) {
                    state.reset();

                    std::cout << "solving ls " << problem << " " << l << " " << i << std::endl;

                    std::stringstream name;
                    name << "../data/" << problem;

                    Instance instance;
                    load(name.str(), instance);

                    t.start();

                    Candidate bsf = ls::search(instance, 1000);

                    t.stop();

                    #if TO_FILE
                    to_file("ls", problem, bsf, t);
                    #else
                    to_stdout(problem, bsf, t);
                    #endif
                }

            }
        }

    }

    return 0;
}
