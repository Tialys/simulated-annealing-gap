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


        void initialise_possible_tasks(vector<int> task);
        void remove_impossible_tasks();
        void show_possible_tasks();
        int get_nb_unassigned_tasks();
        void swap_assigned_tasks(Agent & a);
        
        void find_min_weight_task(WeightFunction weight_function);
        void compute_desirability(WeightFunction weight_function);
        double get_desirability();
        int get_min_weight_task();

        void assign(int task);
        void cross_out(int task);
        void show_assigned_tasks();
        void show_solution();
        double compute_value();
        
        void decrease_capacity(int weight);
        
        bool satisfies_capacity_constraint();
        bool assigned_task(int task);
    private:
        int id_;
        
        double max_capacity_;
        double current_capacity_;
        
        map<int, double> gain_;
        map<int, double> weight_;
        
        double desirability_;
        int min_weight_task_;
        vector<int> possible_tasks_;
        vector<int> assigned_tasks_;
};

#endif
