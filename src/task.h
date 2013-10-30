#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class Task {
    public:
        Task(int id, int nb_agents);
        void agent_gain(pair<int, double> agentId_gain);
        void agent_weight(pair<int, double> agentId_weight);
        void compute_gain_weight_ratio();
        void agent_assignment(bool assignment);
        double get_gain(int task);
        double get_weight(int task);
        void show();
    private:
        int id;
        int nb_agents;
        map<int, double> gain;
        map<int, double> weight;
        map<int, double> gain_weight_ratio;
        vector<bool> agent;
};

#endif
