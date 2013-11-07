#include "heuristic.h"

Heuristic::Heuristic(Instance & instance,
                     WeightFunction weight_function,
                     NeighbourhoodType neighbourhood_type)
                     :
                     instance_(instance),
                     weight_function_(weight_function),
                     neighbourhood_type_(neighbourhood_type) {
    value_ = 0.0;
    nb_iterations_ = 0;
    instance_.initialise_possible_tasks();
    vector<Instance> neighbourhood_;
    vector<Heuristic> admissible_neighbourhood_;
    vector<Heuristic> best_neighbour_;
}

double Heuristic::value() {
    value_ = instance_.value();
    return value_;
}

void Heuristic::set_value(double value) {
    value_ = value;
}

void Heuristic::initialise_neighbourhood() {
    Instance & i = instance_;
    vector<Instance> & n = neighbourhood_;
    if (neighbourhood_type_ == Swap) instance_.create_neighbourhood_swap(i, n);
    if (neighbourhood_type_ == Give) instance_.create_neighbourhood_give(i, n);
    compute_neighbourhood_values();
}

void Heuristic::ascend() {
    cout << "BEGIN ASCENT" << endl;
    cout << "   best neighbour value: " << best_neighbour_value_
         << "   current value: " << value_ << endl;
    if (best_neighbour_value_ > value_) {
        best_neighbour_.back().find_best_neighbour();
        best_neighbour_.back().ascend();
    }
    cout << "END OF ASCENT" << endl;
}

void Heuristic::find_best_neighbour() {
    initialise_neighbourhood();
    empty_neighbourhood();
    empty_admissible_neighbourhood();
}

void Heuristic::empty_neighbourhood() {
    vector<Instance>::iterator it = neighbourhood_.begin();
    while (it != neighbourhood_.end()) {
        neighbourhood_.erase(it);
    }
}

void Heuristic::empty_admissible_neighbourhood() {
    vector<Heuristic>::iterator it = admissible_neighbourhood_.begin();
    while (it != admissible_neighbourhood_.end()) {
        admissible_neighbourhood_.erase(it);
    }
}

// Generate admissible neighbourhood around current instance
// - side effect: find best neighbour
// - side effect: find best neighbourhood value
void Heuristic::compute_neighbourhood_values() {
    for (Instance & neighbour : neighbourhood_) {
        Heuristic h = Heuristic(neighbour,
                                weight_function_,
                                neighbourhood_type_);
        if (h.admissible_solution()) {
            admissible_neighbourhood_.emplace_back(h);
        }
    }
    
    // Put in best_neighbour_ every neighbour with superior value
    double best_neighbour_value = value_; 
    for (Heuristic & neighbour : admissible_neighbourhood_) {
        //cout << "Current best neighbour value: " << best_neighbour_value 
        //     << " vs. value of current neighbour: " << neighbour.value() << endl;
        if (neighbour.value() > best_neighbour_value) {
            cout << "NEIGHBOUR OF VALUE: " << neighbour.value() << endl;
            best_neighbour_value = neighbour.value();
            best_neighbour_.emplace_back(neighbour);
        }
    }
    best_neighbour_value_ = best_neighbour_value;
    
    cout << int(admissible_neighbourhood_.size()) << " good neighbours" << endl;
    cout << int(best_neighbour_.size()) << " awesome neighbours" << endl;
    cout << "Admissible solution: " << value_ 
         << " vs. Best neighbour: " << best_neighbour_value_ << endl;
}

void Heuristic::solve() {
    int nb_iterations = 0;
    while (remaining_tasks()) {
        assign();
        nb_iterations++;
    }
    nb_iterations_ = nb_iterations;
}

void Heuristic::assign() {
    instance_.compute_desirability(weight_function_);
    instance_.assign();
}

bool Heuristic::remaining_tasks() {
    return instance_.remaining_tasks();
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

int Heuristic::get_nb_iterations() {
    return nb_iterations_;
}

void Heuristic::show_assignment() {
    instance_.show_assignment();
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
