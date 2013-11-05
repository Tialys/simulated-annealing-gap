#include "instance.h"

int Instance::get_nb_agents(){
    return nb_agents_;
}

int Instance::get_nb_tasks() {
    return nb_tasks_;
}

void Instance::initialise_possible_tasks() {
    for (Agent agent : agent_) {
        agent.initialise_possible_tasks(task_);
    }
}

void Instance::compute_desirability(WeightFunction weight_function) {
    for (Agent agent : agent_) {
        agent.compute_desirability(weight_function); 
    }   
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
    vector<map<const Task, int>> agent_task_index;
    vector<map<int, double>> agent_task_gain;
    vector<map<int, double>> agent_task_weight;
    
    cout << "read metadata" << endl;

    instance_file >> nb_agents_;
    instance_file >> nb_tasks_;
    
    for (int taskId = 0; taskId < nb_tasks_; taskId++) {
        Task task = Task(taskId);
        task_.push_back(task);
    }
    
    for (int agent = 0; agent < nb_agents_; agent++) {
        map<const Task, int> task_index;
        for (int taskId = 0; taskId < nb_tasks_; taskId++) {
            pair<const Task, int> i((const Task) task_[taskId], taskId);
            task_index.insert(i);
        }
        agent_task_index.push_back(task_index);
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
                            agent_task_index[agentId],
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

        //desirability(weight_function);
        //cout << "   Desirability: " << get_desirability() << endl;

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
    cout << "I did my best mommy" << endl;
}
