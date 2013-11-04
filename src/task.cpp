#include "task.h"

Task::Task(int id, int nb_agents) {
    this->id = id;
    this->nb_agents = nb_agents;

    map<int, double> gain;
    this->gain = gain;

    map<int, double> weight;
    this->weight = weight;

    vector<bool> agents;
    this->agent = agent;
}

void Task::agent_gain(pair<int, double> gain_agentId) {
    gain.insert(gain_agentId);
}

void Task::agent_weight(pair<int, double> weight_agentId) {
    weight.insert(weight_agentId);
}

void Task::compute_gain_weight_ratio() {
    int g_size = gain.size();
    int w_size = weight.size();
    if (g_size == nb_agents && w_size == nb_agents) {
        for (int agent = 0; agent < nb_agents; agent++) {
            pair<int, double> p(agent, gain[agent] / weight[agent]);
            gain_weight_ratio.insert(p);
        }
    }
}

void Task::agent_assignment(bool assignment) {
    agent.push_back(assignment);
}

double Task::get_gain(int agent) {
    return gain[agent];
}

double Task::get_weight(int agent) {
    return weight[agent];
}

void Task::show() {
    cout << "Task #" << id << endl;
    cout << "   Number of agents: " << nb_agents << endl;
    cout << "   Gain per agent: " << endl;
    for (int agent = 0; agent < nb_agents; agent++) {
        cout << gain[agent] << " ";
    }
    cout << endl;
    cout << "   Weight per agent: " << endl;
    for (int agent = 0; agent < nb_agents; agent++) {
        cout << weight[agent] << " ";
    }
    cout << endl;
    cout << "   Gain/weight per agent: " << endl;
    for (int agent = 0; agent < nb_agents; agent++) {
        cout << gain_weight_ratio[agent] << " ";
    }
    
    cout << endl;
    cout << " " << endl;
}
