#ifndef INSTANCE_H_INCLUDED
#define INSTANCE_H_INCLUDED

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <functional>
#include "agent.h"
#include "task.h"
using namespace std;

class Instance {
    private:
        int nb_agents;
        int nb_tasks;
        
    public:
        vector<Agent> agent;
        vector<Task> task;
        
        Instance(int nb_agents, int nb_tasks);
        Instance(ifstream& instance_file);

        void add(Agent agent);
        void add(Task task);

        int get_nb_agents();
        int get_nb_tasks();
};


void load(ifstream& instance_file, const char* file_name);

#endif
