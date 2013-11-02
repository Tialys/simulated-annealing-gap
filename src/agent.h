#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class Agent {
    typedef double (Agent::*WeightFunction)(int task);
    public:
        Agent(int id, int nb_tasks);
        void set_max_capacity(int max_capacity);
        
        void task_gain(pair<int, double> taskId_gain);
        void task_weight(pair<int, double> taskId_weight);
        
        void compute_gain_weight_ratio();
        void task_assignment(bool assignment);
        
        double get_gain(int task);
        double get_weight(int task);
        double get_max_capacity();
        double get_gain_weight_ratio(int task);
        double get_weight_max_capacity_ratio(int task);
        
        int minimum_weight_task();
        double desirability();
        
        void show();
    private:
        int id;
        int nb_tasks;
        int max_capacity;
        map<int, double> gain;
        map<int, double> weight;
        map<int, double> gain_weight_ratio;
        vector<bool> task;
};

#endif
