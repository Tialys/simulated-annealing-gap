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
        Agent agent = Agent(i, 0);
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

    // next m lines
    for (int i=0; i < instance.nb_agents; i++) {
        // next n words
        for (int task=0; task < instance.nb_tasks; task++) {
            double gain;
            instance_file >> gain;
            pair<int, double> p(task, gain);
            //cout << "pair " << p.first << " " << p.second << endl;
            //Agent agent = Agent(0, 30);
            //agent.task_gain(p);
            //cout << agent.gain[task] << " " << task << endl;

            instance.agent[i].task_gain(p);
            cout << "Task #" << task << " of gain: "
                 << instance.agent[i].gain[task] << endl;
        }
        cout << "=====" << i << endl;
    }

    // next m lines
    for (int i=0; i < instance.nb_agents; i++) {
        // next n words
        for (int task=0; task < instance.nb_tasks; task++) {
            double weight;
            instance_file >> weight;
            pair<int, double> p(task, weight);
            instance.agent[i].task_weight(p);
            cout << "Task #" << task << " of weight: "
                 << instance.agent[i].weight[task] << endl;
        }
    }

    // next m words
    for (int i=0; i < instance.nb_agents; i++) {
        instance_file >> instance.agent[i].max_capacity;
    }
    return instance;
}

Instance read2(ifstream& instance_file) {
    Instance instance = Instance(0,0);
    
    string line;
    while(getline(instance_file, line)) {
        cout << line << endl;
    }

    return instance;
}



