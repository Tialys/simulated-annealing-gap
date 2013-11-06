#include "heuristic.h"

Heuristic::Heuristic(Instance & instance,
                     WeightFunction weight_function)
                     :
                     instance_(instance),
                     weight_function_(weight_function) {
    value_ = 0.0;
    nb_iterations_ = 0;
    instance_.initialise_possible_tasks();
    vector<Instance> neighbourhood_;
    vector<Heuristic> heuristic_neighbour_;
}

void Heuristic::initialise_neighbourhood() {
    Instance & i = instance_;
    vector<Instance> & n = neighbourhood_;
    instance_.create_neighbourhood(i, n);
}

void Heuristic::compute_neighbourhood_values() {
    for (Instance & neighbour : neighbourhood_) {
        Heuristic h = Heuristic(neighbour, weight_function_);
        //h.show_information();
        if (h.admissible_solution()) {
            //cout << "GOOD NEIGHBOUR HERE" << endl;
            heuristic_neighbour_.emplace_back(h);
        }
    }
    for (Heuristic & h : heuristic_neighbour_) {
        //h.show_information();
        h.show_value();
    }
    cout << int(heuristic_neighbour_.size()) << " good neighbours" << endl;
}

void Heuristic::solve() {
    int nb_iterations = 0;
    while (remaining_tasks()) {
        assign();
        nb_iterations++;
    }
    set_nb_iterations(nb_iterations);
}

void Heuristic::set_nb_iterations(int nb_iterations) {
    nb_iterations_ = nb_iterations;
}

int Heuristic::get_nb_iterations() {
    return nb_iterations_;
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

bool Heuristic::admissible_solution() {
    return satisfies_assignment_constraint() && satisfies_capacity_constraint();
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

void Heuristic::show_information() {
    cout << "====================" << endl;
    show_assignment();
    cout << "====================" << endl;
    cout << "Solution satisfies assignment constraint? "
         << (satisfies_assignment_constraint() ? "true" : "false")
         << endl;
    cout << "Solution satisfies capacity constraint? "
         << (satisfies_capacity_constraint() ? "true" : "false")
         << endl;
    cout << "Solution is realisable? "
         << (admissible_solution() ? "true" : "false")
         << endl;
}
