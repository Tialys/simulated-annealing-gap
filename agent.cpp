#include "agent.h"

Agent::Agent(int id, int max_capacity) {
    this->id = id;
    this->max_capacity = max_capacity;

    map<int, double> gain;
    this->gain = gain;

    map<int, double> weight;
    this->weight = weight;

    vector<bool> tasks;
    this->tasks = tasks;
}

void Agent::task_gain(pair<int, double> gain_taskId) {
    gain.insert(gain_taskId);
}
void Agent::task_weight(pair<int, double> weight_taskId) {
    weight.insert(weight_taskId);
}
