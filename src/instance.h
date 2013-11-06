#ifndef INSTANCE_H_INCLUDED
#define INSTANCE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "agent.h"
#include "weight_function.h"

using namespace std;

class Instance {
    public:
        Instance(ifstream& instance_file);
        Instance(Instance & i, Agent & a1, Agent & a2);
        void create_neighbourhood(Instance & base_instance,
                                  vector<Instance> & neighbourhood);

        int get_nb_agents();
        int get_nb_tasks();
        int get_nb_unassigned_tasks();
        vector<Agent> agents();

        void initialise_possible_tasks();
        void compute_desirability(WeightFunction weight_function);
        int max_desirability_agent();
        void assign();
        void remove_impossible_tasks();
        
        void show_agents();
        void show_tasks();

        void show_possible_tasks();
        void show_desirability();
        void show_assignment();
        void show_solution();
        double value();

        bool remaining_tasks();
        bool satisfies_assignment_constraint();
        bool satisfies_capacity_constraint();
    private:
        int nb_agents_;
        int nb_tasks_;
        
        vector<Agent> agent_;
        vector<int> task_;
};

void load(ifstream& instance_file, vector<Instance> & instance); 

#endif
