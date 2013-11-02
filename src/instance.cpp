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
    
    for (int i = 0; i < nb_agents; i++) {
        Agent agent = Agent(i, nb_tasks);
        add(agent);
    }
   
    for (int i = 0; i < nb_tasks; i++) {
        Task task = Task(i, nb_agents);
        add(task);
    }
}

int Instance::get_nb_agents() {
    return nb_agents;
}

int Instance::get_nb_tasks() {
    return nb_tasks;
}

void compute_gain_weight_ratio(Instance& instance) {
}
// Instance file format:
// First line : m (agents) n (tasks)
// Next m lines : gain for each task
// Next m lines : weight for each task
// Next line : capacity for each agent
Instance::Instance(ifstream& instance_file) {
    
    cout << "read metadata" << endl;

    instance_file >> this->nb_agents;
    instance_file >> this->nb_tasks;
    
    for (int i = 0; i < nb_agents; i++) {
        Agent agent = Agent(i, nb_tasks);
        add(agent);
    }
   
    for (int i = 0; i < nb_tasks; i++) {
        Task task = Task(i, nb_agents);
        add(task);
    }

    cout << "read gain" << endl;
    // read gain
    for (int agentId = 0; agentId < nb_agents; agentId++) {
        for (int taskId = 0; taskId < nb_tasks; taskId++) {
            cout << agentId << " " << taskId << endl;
            double gain;
            instance_file >> gain;
            cout << gain << endl;
            pair<int, double> p(taskId, gain);
            pair<int, double> d(agentId, gain);

            this->agent[agentId].task_gain(p);
            this->task[taskId].agent_gain(d);
        }
    }
    
    cout << "read weight" << endl;
    // read weight
    for (int agent = 0; agent < nb_agents; agent++) {
        for (int task = 0; task < nb_tasks; task++) {
            double weight;
            instance_file >> weight;
            pair<int, double> p(task, weight);
            pair<int, double> d(agent, weight);

            this->agent[agent].task_weight(p);
            this->task[task].agent_weight(d);
        }
    }

    cout << "read max capacity" << endl;
    // read max capacity
    for (int agent = 0; agent < nb_agents; agent++) {
        int c;
        instance_file >> c;
        
        this->agent[agent].set_max_capacity(c);
    }

    cout << "compute gain weight ratio" << endl;
    // compute gain weight ratio
    for (int agent = 0; agent < nb_agents; agent++) {
        this->agent[agent].compute_gain_weight_ratio();
    }
    for (int task = 0; task < nb_tasks; task++) {
        this->task[task].compute_gain_weight_ratio();
    }
}

void load(ifstream& instance_file, const char* file_name) {
    instance_file.open(file_name);
    
    if(instance_file.is_open()) {
        int nb_instances;
        instance_file >> nb_instances;
        cout << "Instance file containing " << nb_instances << " instances" << endl;

        vector<Instance> instance;
        for (int i=0; i < nb_instances; i++) {
            Instance temp_instance = Instance(instance_file);
            instance.push_back(temp_instance);
        }
        for (int i=0; i < nb_instances; i++) {
            cout << ">>>>>> Instance #" << i << endl;
            for (int j = 0; j < instance[i].get_nb_agents(); j++) {
                instance[i].agent[j].show();
            }
            for (int j = 0; j < instance[i].get_nb_tasks(); j++) {
                instance[i].task[j].show();
            }
        }

    } else {
        cout << "Could not find file " << file_name << endl;
    }   
}
