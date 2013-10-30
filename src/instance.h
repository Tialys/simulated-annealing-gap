#ifndef INSTANCE_H_INCLUDED
#define INSTANCE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "agent.h"
#include "task.h"
using namespace std;

class Instance {
    public:
        int nb_agents;
        int nb_tasks;
        vector<Agent> agent;
        vector<Task> task;
        
        Instance(int nb_agents, int nb_tasks);
        void add(Agent agent);
        void add(Task task);
};

Instance read(ifstream& instance_file);

void load(ifstream& instance_file, const char* file_name);

#endif
