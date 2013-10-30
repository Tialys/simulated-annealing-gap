#include "instance.h"

void Instance::add(Agent agent) {
    this->agent.push_back(agent);
}

Instance::Instance(int nb_agents, int nb_tasks) {
    this->nb_agents = nb_agents;
    this->nb_tasks = nb_tasks;
    vector<Agent> agent;
    this->agent = agent;
    for (int i = 0; i < nb_agents; i++) {
        Agent agent = Agent(i, nb_tasks);
        add(agent);
    }
}

// Format per instance:
// First line : m (agents) n (tasks)
// Next m lines : gain for each task
// Next m lines : weight for each task
// Next line : capacity for each agent
Instance read(ifstream& instance_file) {
    int nb_agents, nb_tasks;
    // first two words
    instance_file >> nb_agents;
    instance_file >> nb_tasks;
    Instance instance = Instance(nb_agents, nb_tasks);

    for (int i=0; i < instance.nb_agents; i++) {
        for (int task=0; task < instance.nb_tasks; task++) {
            double gain;
            instance_file >> gain;
            pair<int, double> p(task, gain);

            instance.agent[i].task_gain(p);
        }
    }

    for (int i=0; i < instance.nb_agents; i++) {
        for (int task=0; task < instance.nb_tasks; task++) {
            double weight;
            instance_file >> weight;
            pair<int, double> p(task, weight);

            instance.agent[i].task_weight(p);
        }
    }

    for (int i=0; i < instance.nb_agents; i++) {
        int c;
        instance_file >> c;
        
        instance.agent[i].set_max_capacity(c);
        instance.agent[i].compute_gain_weight_ratio();
    }
    return instance;
}
