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
    public:
        Heuristic(Instance & instance, WeightFunction weight_function);
        void assign();
        
        bool remaining_tasks();
        bool satisfies_assignment_constraint();
        bool satisfies_capacity_constraint();
        
        void show_assignment();
        void show_value();
        void show_solution();
};

#endif
