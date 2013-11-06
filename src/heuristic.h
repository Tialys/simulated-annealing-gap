#ifndef HEURISTIC_H_INCLUDED
#define HEURISTIC_H_INCLUDED

#include <iostream>
#include "instance.h"
#include "weight_function.h"

class Heuristic {
    private:
        Instance instance_;
        WeightFunction weight_function_;
        double value_;
        int nb_iterations_;
        vector<Instance> neighbourhood_;
        vector<Heuristic> heuristic_neighbour_;
    public:
        Heuristic(Instance & instance, WeightFunction weight_function);
        void solve();
        void assign();
        void set_nb_iterations(int nb_iterations);
        int get_nb_iterations();
        void initialise_neighbourhood();
        void compute_neighbourhood_values();
        
        bool remaining_tasks();
        bool satisfies_assignment_constraint();
        bool satisfies_capacity_constraint();
        bool admissible_solution();
        
        void show_assignment();
        void show_value();
        void show_solution();
        void show_information();
};

#endif
