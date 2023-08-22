#include "./out.h"

void to_file(std::string alg, std::string problem, Candidate& c, Timer& t) {
    std::stringstream outname;
    outname << "../res/" << alg << "_" << state.iterations() << "_" << problem;

    std::ofstream out(outname.str(), std::ios::app);

    c.short_print(out);
    out << c.get_objective() / optimum_values[problem] << std::endl;
    out << "iterations: " << state.total() << std::endl << "evaluations: " << state.total_evaluations() << std::endl << "time: ";
    t.print(out);
    out << std::endl << std::endl;;

}

void to_stdout(std::string problem, Candidate& c, Timer& t) {
    c.short_print();
    std::cout << c.get_objective() / optimum_values[problem] << std::endl;
    std::cout << "iterations: " << state.total() << std::endl << "evaluations: " << state.total_evaluations() << std::endl << "time: ";
    t.print();
    std::cout << std::endl << std::endl;;
}
