#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include "weight_function.h"

using namespace std;

class Agent {
    public:
        Agent(int id,
              double max_capacity,
              double current_capacity,
              map<int, double> gain,
              map<int, double> weight);
        
        void task_assignment(bool assignment);
        
        double get_gain(int task) ;
        double get_weight(int task) ;
        double get_gain_weight_ratio(int task) ;
        double get_weight_max_capacity_ratio(int task) ;

        int get_id();
        double get_max_capacity() ;
        double get_current_capacity() ;

        double get_desirability() ;
        int get_min_weight_task() ;

        void initialise_possible_tasks(vector<int> task);
        void show_possible_tasks();
        void remove_impossible_tasks();
        void compute_desirability(WeightFunction weight_function);
        void find_min_weight_task(WeightFunction weight_function);
    private:
        int id_;
        
        double max_capacity_;
        double current_capacity_;
        
        map<int, double> gain_;
        map<int, double> weight_;
        
        double desirability_;
        int min_weight_task_;
        vector<int> possible_tasks_;
};

#endif
