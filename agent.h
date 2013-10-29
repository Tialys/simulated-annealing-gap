#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class Agent {
    public:
        int id;
        int max_capacity;
        // task id, gain
        map<int, double> gain;
        // task id, weight
        map<int, double> weight;
        // task id, gain/weight
        map<int, double> gain_weight_ratio;
        vector<bool> tasks;

        Agent(int id, int max_capacity);
        void task_gain(pair<int, double> gain_taskId);
        void task_weight(pair<int, double> weight_taskId);
};

#endif
