#include "instance.h"

void Instance::add(Agent agent) {
    this->agent.push_back(agent);
}

void Instance::add(Task task) {
    this->task.push_back(task);
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
    for (int i = 0; i < nb_tasks; i++) {
        Task task = Task(i, nb_agents);
        add(task);
    }
}

void read_gain(ifstream& instance_file, Instance& instance) {
    for (int agent = 0; agent < instance.nb_agents; agent++) {
        for (int task = 0; task < instance.nb_tasks; task++) {
            double gain;
            instance_file >> gain;
            pair<int, double> p(task, gain);
            pair<int, double> d(agent, gain);

            instance.agent[agent].task_gain(p);
            instance.task[task].agent_gain(d);
        }
    }
}

void read_weight(ifstream& instance_file, Instance& instance) {
    for (int agent = 0; agent < instance.nb_agents; agent++) {
        for (int task = 0; task < instance.nb_tasks; task++) {
            double weight;
            instance_file >> weight;
            pair<int, double> p(task, weight);
            pair<int, double> d(agent, weight);

            instance.agent[agent].task_weight(p);
            instance.task[task].agent_weight(d);
        }
    }
}

void read_max_capacity(ifstream& instance_file, Instance& instance) {
    for (int agent = 0; agent < instance.nb_agents; agent++) {
        int c;
        instance_file >> c;
        
        instance.agent[agent].set_max_capacity(c);
    }
}

void compute_gain_weight_ratio(Instance& instance) {
    for (int agent = 0; agent < instance.nb_agents; agent++) {
        instance.agent[agent].compute_gain_weight_ratio();
    }
    for (int task = 0; task < instance.nb_tasks; task++) {
        instance.task[task].compute_gain_weight_ratio();
    }
}
// Format per instance:
// First line : m (agents) n (tasks)
// Next m lines : gain for each task
// Next m lines : weight for each task
// Next line : capacity for each agent
Instance read(ifstream& instance_file) {
    
    int nb_agents, nb_tasks;
    instance_file >> nb_agents;
    instance_file >> nb_tasks;
    
    Instance instance = Instance(nb_agents, nb_tasks);

    read_gain(instance_file, instance);
    
    read_weight(instance_file, instance);

    read_max_capacity(instance_file, instance);

    compute_gain_weight_ratio(instance);

    return instance;
}

void load(ifstream& instance_file, const char* file_name) {
    instance_file.open(file_name);
    
    if(instance_file.is_open()) {
        int nb_instances;
        instance_file >> nb_instances;
        cout << "Instance file containing " << nb_instances << " instances" << endl;

        vector<Instance> instance;
        for (int i=0; i < nb_instances; i++) {
            Instance temp_instance = read(instance_file);
            instance.push_back(temp_instance);
        }
        for (int i=0; i < nb_instances; i++) {
            cout << ">>>>>> Instance #" << i << endl;
            for (int j = 0; j < instance[i].nb_agents; j++) {
                instance[i].agent[j].show();
            }
            for (int j = 0; j < instance[i].nb_tasks; j++) {
                instance[i].task[j].show();
            }
        }

    } else {
        cout << "Could not find file " << file_name << endl;
    }   
}
