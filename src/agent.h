#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "weight_function.h"
#include "task.h"

using namespace std;

class Agent {
    public:
        Agent(int id, int nb_tasks);
        void set_max_capacity(int max_capacity);
        void set_current_capacity(int current_capacity);
        
        void task_gain(pair<int, double> taskId_gain);
        void task_weight(pair<int, double> taskId_weight);
        
        void compute_gain_weight_ratio();
        void task_assignment(bool assignment);
        
        double get_gain(int task);
        void update_possible_tasks(double current_capacity);
        double get_weight(int task);
        double get_gain_weight_ratio(int task);
        double get_weight_max_capacity_ratio(int task);
        double get_max_capacity();
        double get_desirability();

        void initialise_possible_tasks(vector<Task> task);
        void update_possible_tasks(double current_capacity);
        void desirability(WeightFunction weight_function);
        void find_min_weight_task(WeightFunction weight_function);
        
        void show(WeightFunction weight_function);
    private:
        int id;
        int nb_tasks;
        int min_weight_task;
        double max_capacity;
        double current_capacity;
        double current_desirability;
        map<int, double> gain;
        map<int, double> weight;
        map<Task, int> index;
        vector<Task> possible_tasks;
};

#endif
