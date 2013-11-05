#ifndef INSTANCE_H_INCLUDED
#define INSTANCE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "agent.h"
#include "task.h"
#include "weight_function.h"

using namespace std;

class Instance {
    public:
        Instance(ifstream& instance_file);

        int get_nb_agents();
        int get_nb_tasks();

        void show_agents();
        void show_tasks();

        void initialise_possible_tasks();
        void compute_desirability(WeightFunction weight_function);
        //void find_min_weight_task(WeightFunction weight_function);
    private:
        int nb_agents_;
        int nb_tasks_;
        
        vector<Agent> agent_;
        vector<Task> task_;
};

void load(ifstream& instance_file, vector<Instance> & instance); 

#endif
