#include "instance.h"

int Instance::get_nb_agents(){
    return nb_agents_;
}

int Instance::get_nb_tasks() {
    return nb_tasks_;
}

void Instance::initialise_possible_tasks() {
    for (Agent & agent : agent_) {
        agent.initialise_possible_tasks(task_);
    }
}

void Instance::remove_impossible_tasks() {
    for (Agent & agent : agent_) {
        agent.remove_impossible_tasks();
    }
}

void Instance::show_possible_tasks() {
    for (Agent & agent : agent_) {
        agent.show_possible_tasks();
    }
}

void Instance::compute_desirability(WeightFunction weight_function) {
    for (Agent & agent : agent_) {
        agent.compute_desirability(weight_function); 
    }   
}

void Instance::show_desirability() {
    for (Agent & agent : agent_) {
        cout << "Agent #" << agent.get_id() << endl;
        cout << "    Desirability: "  << agent.get_desirability() << endl;
    }
}

int Instance::max_desirability_agent() {
    double max_desirability = agent_[0].get_desirability();
    int max_desirability_agent = 0;

    for (Agent & agent : agent_) {
        double current_desirability = agent.get_desirability(); 
        if (current_desirability > max_desirability) {
            max_desirability = current_desirability;
            max_desirability_agent = agent.get_id(); 
        }
    }
    return max_desirability_agent;
}

void Instance::assign() {
    int agent = max_desirability_agent();
    int task = agent_[agent].get_min_weight_task();
    cout << "ASSIGNMENT OF TASK #" << task << " TO AGENT #" << agent << endl;
}

// Instance file format:
// First line : m (agents) n (tasks)
// Next m lines : gain for each task
// Next m lines : weight for each task
// Next line : capacity for each agent

Instance::Instance(ifstream& instance_file) {
    // vectors of length equal to the number of agents
    // containing file instance information
    vector<double> agent_max_capacity;
    vector<double> agent_current_capacity;
    vector<map<int, double>> agent_task_gain;
    vector<map<int, double>> agent_task_weight;
    
    cout << "read metadata" << endl;

    instance_file >> nb_agents_;
    instance_file >> nb_tasks_;
    
    for (int taskId = 0; taskId < nb_tasks_; taskId++) {
        task_.push_back(taskId);
    }
    
    cout << "read gain" << endl;
    // read gain
    for (int agent = 0; agent < nb_agents_; agent++) {
        map<int, double> task_gain;
        for (int taskId = 0; taskId < nb_tasks_; taskId++) {
            double gain;
            instance_file >> gain;
            pair<int, double> g(taskId, gain);
            task_gain.insert(g);
        }
        agent_task_gain.push_back(task_gain);
    }
    
    cout << "read weight" << endl;
    // read weight
    for (int agent = 0; agent < nb_agents_; agent++) {
        map<int, double> task_weight;
        for (int taskId = 0; taskId < nb_tasks_; taskId++) {
            double weight;
            instance_file >> weight;
            pair<int, double> w(taskId, weight);
            task_weight.insert(w);
        }
        agent_task_weight.push_back(task_weight);
    }

    cout << "read max capacity" << endl;
    // read max capacity
    for (int agent = 0; agent < nb_agents_; agent++) {
        double max_capacity;
        instance_file >> max_capacity;
        agent_max_capacity.push_back(max_capacity);
        agent_current_capacity.push_back(max_capacity);
    }

    for (int agentId = 0; agentId < nb_agents_; agentId++) {
        Agent agent = Agent(
                            agentId,
                            agent_max_capacity[agentId],
                            agent_current_capacity[agentId],
                            agent_task_gain[agentId],
                            agent_task_weight[agentId]
                           );
        agent_.push_back(agent);
    }
}

void Instance::show_tasks() {
    for (int task = 0; task < nb_tasks_; task++) {
        cout << "Task #" << task << endl;
        cout << "   Number of agents: " << nb_agents_ << endl;
        
        cout << "   Gain per agent: " << endl;
        for (int id = 0; id < nb_agents_; id++) {
            cout << agent_[id].get_gain(task) << " ";
        }
        cout << endl;
        
        cout << "   Weight per agent: " << endl;
        for (int id = 0; id < nb_agents_; id++) {
            cout << agent_[id].get_weight(task) << " ";
        }
        cout << endl;
        
        cout << "   Gain/weight per agent: " << endl;
        for (int id = 0; id < nb_agents_; id++) {
            cout << agent_[id].get_gain_weight_ratio(task) << " ";
        }
        cout << endl;
        
        cout << " " << endl;
    }
}

void Instance::show_agents() {
    for (int id = 0; id < nb_agents_; id++) {
        cout << "Agent #" << id << endl;
        cout << "   Number of tasks: " << nb_tasks_ << endl;
        cout << "   Maximum capacity: " << agent_[id].get_max_capacity() << endl;
        
        cout << "   Gain per task: " << endl;
        for (int task = 0; task < nb_tasks_; task++) {
            cout << agent_[id].get_gain(task) << " ";
        }
        cout << endl;
        
        cout << "   Weight per task: " << endl;
        for (int task = 0; task < nb_tasks_; task++) {
            cout << agent_[id].get_weight(task) << " ";
        }
        cout << endl;
        
        cout << "   Gain/weight per task: " << endl;
        for (int task = 0; task < nb_tasks_; task++) {
            cout << agent_[id].get_gain_weight_ratio(task) << " ";
        }
        cout << endl;
        
        cout << " " << endl;
    }
}

void load(ifstream& instance_file, vector<Instance> & instance) {
    int nb_instances;

    instance_file >> nb_instances;
    cout << "Instance file containing " << nb_instances << " instances" << endl;

    for (int i=0; i < nb_instances; i++) {
        Instance temp_instance = Instance(instance_file);
        instance.push_back(temp_instance);

        cout << ">>>>>> Instance #" << i << endl;
        instance[i].show_agents();
        instance[i].show_tasks();
    }
}
