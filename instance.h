#ifndef INSTANCE_H_INCLUDED
#define INSTANCE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "agent.h"
using namespace std;

class Instance {
    public:
        int nb_agents;
        int nb_tasks;
        vector<Agent> agent;
        
        Instance(int nb_agents, int nb_tasks);
        void add(Agent agent);
};

Instance read(ifstream& instance_file);

void load(ifstream& instance_file, const char* file_name);

#endif
