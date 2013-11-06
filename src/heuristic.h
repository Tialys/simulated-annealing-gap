#ifndef HEURISTIC_H_INCLUDED
#define HEURISTIC_H_INCLUDED

#include <iostream>
#include "instance.h"
#include "weight_function.h"

class Heuristic {
    private:
        Instance instance_;
    public:
        Heuristic(Instance & instance, WeightFunction weight_function);
        void assign();
};

class Solution {
    private:
        double value;
    public:
        Solution(Heuristic heuristic);
        bool satisfies_affectation_constraint();
        bool satisfies_capacity_constraint();
};

#endif

