#include "heuristic.h"

Heuristic::Heuristic(Instance & instance,
                     WeightFunction weight_function)
                     :
                     instance_(instance),
                     weight_function_(weight_function) {
    cout << "Initialise heuristic" << endl;
    cout << endl;
    
    cout << "Find possible tasks" << endl;
    instance_.initialise_possible_tasks();
    instance_.show_possible_tasks();
    cout << endl;
    
    cout << "Compute agent desirability" << endl;
    instance_.compute_desirability(weight_function_);
    instance_.show_desirability();
    cout << endl;
}

void Heuristic::assign() {
    instance_.assign();
    instance_.compute_desirability(weight_function_);
}

bool Heuristic::remaining_tasks() {
    return instance_.remaining_tasks();
}

void Heuristic::show_assignment() {
    instance_.show_assignment();
}
