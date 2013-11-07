#ifndef HEURISTIC_H_INCLUDED
#define HEURISTIC_H_INCLUDED

#include <iostream>
#include "instance.h"
#include "weight_function.h"

class Heuristic {
    public:
        Heuristic(Instance & instance,
                  WeightFunction weight_function,
                  NeighbourhoodType neighbourhood_type);
        
        void solve();
        void assign();
        
        void initialise_neighbourhood();
        void compute_neighbourhood_values();
        void empty_neighbourhood();
        void empty_admissible_neighbourhood();

        void find_best_neighbour();
        void ascend();

        int get_nb_iterations();
        double value();
        void set_value(double value);
        
        bool remaining_tasks();
        bool satisfies_assignment_constraint();
        bool satisfies_capacity_constraint();
        bool admissible_solution();
        
        void show_assignment();
        void show_value();
        void show_solution();
        void show_information();
    private:
        Instance instance_;
        WeightFunction weight_function_;
        NeighbourhoodType neighbourhood_type_;
        double value_;
        double best_neighbour_value_;
        int best_neighbour;
        int nb_iterations_;
        vector<Instance> neighbourhood_;
        vector<Heuristic> admissible_neighbourhood_;
        vector<Heuristic> best_neighbour_;
};

#endif
