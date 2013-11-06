#include "heuristic.h"

Heuristic::Heuristic(Instance & instance,
                     WeightFunction weight_function) : instance_(instance) {
    cout << "Initialise heuristic" << endl;
    cout << endl;
    
    cout << "Find possible tasks" << endl;
    instance_.initialise_possible_tasks();
    instance_.show_possible_tasks();
    cout << endl;
    
    cout << "Compute agent desirability" << endl;
    instance_.compute_desirability(weight_function);
    instance_.show_desirability();
    cout << endl;
}

void Heuristic::assign() {
    instance_.assign();
}
