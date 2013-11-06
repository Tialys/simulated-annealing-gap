#include "heuristic.h"

Heuristic::Heuristic(Instance & instance,
                     WeightFunction weight_function)
                     :
                     instance_(instance),
                     weight_function_(weight_function) {
    value_ = 0.0;
    //cout << "Initialise heuristic" << endl;
    //cout << endl;
    
    //cout << "Find possible tasks" << endl;
    instance_.initialise_possible_tasks();
    //instance_.show_possible_tasks();
    //cout << endl;
}

void Heuristic::assign() {
    instance_.compute_desirability(weight_function_);
    instance_.assign();
}

bool Heuristic::remaining_tasks() {
    return instance_.remaining_tasks();
}

void Heuristic::show_assignment() {
    instance_.show_assignment();
}

bool Heuristic::satisfies_assignment_constraint() {
    return instance_.satisfies_assignment_constraint();
}

bool Heuristic::satisfies_capacity_constraint() {
    return instance_.satisfies_capacity_constraint();
}

void Heuristic::show_value() {
    value_ = instance_.value();
    cout << "SOLUTION OF VALUE: " << value_ << endl;
}

void Heuristic::show_solution() {
    instance_.show_solution();
}
