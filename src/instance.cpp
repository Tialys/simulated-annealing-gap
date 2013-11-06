#include "instance.h"

void load(ifstream& instance_file, vector<Instance> & instance) {
    int nb_instances;

    instance_file >> nb_instances;
    //cout << "Instance file containing " << nb_instances << " instances" << endl;

    for (int i=0; i < nb_instances; i++) {
        Instance temp_instance = Instance(instance_file);
        instance.emplace_back(temp_instance);

        /*
        cout << ">>>>>> Instance #" << i << endl;
        instance[i].show_agents();
        instance[i].show_tasks();
        */
    }
}

// GENERATE NEIGHBOURHOOD (instances with tasks swapped between two agents)
void Instance::create_neighbourhood(Instance & base_instance,
                                    vector<Instance> & neighbourhood) {
    int nb_neighbourhoods = 0;
    for (Agent & a1 : base_instance.agents()) {
        for (Agent & a2 : base_instance.agents()) {
            if (a1.get_id() < a2.get_id()) {
                Instance neighbour = Instance(base_instance, a1, a2);
                neighbourhood.emplace_back(neighbour);
                nb_neighbourhoods++;
            }
        }
    }
    cout << "Created " << nb_neighbourhoods << " neighbours" << endl;
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

    //cout << "read metadata" << endl;

    instance_file >> nb_agents_;
    instance_file >> nb_tasks_;

    for (int taskId = 0; taskId < nb_tasks_; taskId++) {
        task_.emplace_back(taskId);
    }

    //cout << "read gain" << endl;
    // read gain
    for (int agent = 0; agent < nb_agents_; agent++) {
        map<int, double> task_gain;
        for (int taskId = 0; taskId < nb_tasks_; taskId++) {
            double gain;
            instance_file >> gain;
            pair<int, double> g(taskId, gain);
            task_gain.insert(g);
        }
        agent_task_gain.emplace_back(task_gain);
    }

    //cout << "read weight" << endl;
    // read weight
    for (int agent = 0; agent < nb_agents_; agent++) {
        map<int, double> task_weight;
        for (int taskId = 0; taskId < nb_tasks_; taskId++) {
            double weight;
            instance_file >> weight;
            pair<int, double> w(taskId, weight);
            task_weight.insert(w);
        }
        agent_task_weight.emplace_back(task_weight);
    }

    //cout << "read max capacity" << endl;
    // read max capacity
    for (int agent = 0; agent < nb_agents_; agent++) {
        double max_capacity;
        instance_file >> max_capacity;
        agent_max_capacity.emplace_back(max_capacity);
        agent_current_capacity.emplace_back(max_capacity);
    }

    for (int agentId = 0; agentId < nb_agents_; agentId++) {
        Agent agent = Agent(
                            agentId,
                            agent_max_capacity[agentId],
                            agent_current_capacity[agentId],
                            agent_task_gain[agentId],
                            agent_task_weight[agentId]
                           );
        agent_.emplace_back(agent);
    }
}

// Copy/swap constructor
Instance::Instance(Instance & i, Agent & a1, Agent & a2) {
    nb_agents_ = i.get_nb_agents();
    nb_tasks_ = i.get_nb_tasks();

    for (Agent & agent : i.agent_) {
        agent_.emplace_back(agent);
    }
    for (int t : i.task_) {
        task_.emplace_back(t);
    }
    
    agent_[a1.get_id()].swap_assigned_tasks(agent_[a2.get_id()]);
    /*
    cout << "original "; a1.show_assigned_tasks();
    cout << "new      "; agent_[a1.get_id()].show_assigned_tasks();
    
    cout << "original "; a2.show_assigned_tasks();
    cout << "new      "; agent_[a2.get_id()].show_assigned_tasks();
    */
}

// CONST
int Instance::get_nb_agents(){
    return nb_agents_;
}

// CONST
int Instance::get_nb_tasks() {
    return nb_tasks_;
}

// VARIABLE
int Instance::get_nb_unassigned_tasks() {
    int count = agent_[0].get_nb_unassigned_tasks();
    for (Agent & a : agent_) {
        count = count + a.get_nb_unassigned_tasks();
    }
 /*   cout << count << endl;
    bool equal = true;
    for (Agent & a : agent_) {
        equal &= (count == a.get_nb_unassigned_tasks());
    }
    cout << "Same number of unassigned tasks for every agent? " << equal << endl;
*/
    return count;
}

vector<Agent> Instance::agents() {
    vector<Agent> agents;
    for (Agent & a : agent_) {
        agents.emplace_back(a);
    }
    return agents;
}

// INITIAL POSSIBLE TASKS (called once)
void Instance::initialise_possible_tasks() {
    for (Agent & agent : agent_) {
        agent.initialise_possible_tasks(task_);
    }
}

// Compute desirability for every agent (called once per iteration)
// - side effect: compute minimum weight task for every agent
void Instance::compute_desirability(WeightFunction weight_function) {
    for (Agent & agent : agent_) {
        agent.compute_desirability(weight_function);
    }
}

// Find maximum desirability agent (called once per iteration)
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

// Assign to maximum desirability agent its min weight task (called once per iteration)
void Instance::assign() {
    int agent = max_desirability_agent();
    int task = agent_[agent].get_min_weight_task();

    //cout << "ASSIGNMENT OF TASK #" << task << " TO AGENT #" << agent << endl;
    agent_[agent].assign(task);
    //agent_[agent].show_assigned_tasks();

    for (Agent & a : agent_) {
        a.cross_out(task);
     //   a.show_possible_tasks();
    }
    remove_impossible_tasks();
}


// UPDATE TASKS
void Instance::remove_impossible_tasks() {
    for (Agent & agent : agent_) {
        agent.remove_impossible_tasks();
    }
}


// LOGGING METHODS

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

void Instance::show_assignment() {
    for (Agent & a : agent_) {
        a.show_assigned_tasks();
    }
}

void Instance::show_solution() {
    for (Agent & a : agent_) {
        a.show_solution();
    }
}

void Instance::show_possible_tasks() {
    for (Agent & agent : agent_) {
        agent.show_possible_tasks();
    }
}

/*
void Instance::show_desirability() {
    for (Agent & agent : agent_) {
        cout << "Agent #" << agent.get_id() << endl;
        cout << "    Desirability: "  << agent.get_desirability() << endl;
    }
}
*/

// CONDITIONS

// called once per iteration
bool Instance::remaining_tasks() {
    if (get_nb_unassigned_tasks() > 0)
        return true;
    else if (get_nb_unassigned_tasks() == 0)
        return false;
    else {
        cout << "PROBLEM HERE" << endl;
        return false;
    }
}

// called once at the end
bool Instance::satisfies_assignment_constraint() {
    bool satisfies = true;
    for (int t : task_) {
        int task_assignments = 0;
        for (Agent & a : agent_) {
            if (a.assigned_task(t))
                ++task_assignments;
        }
        satisfies &= (task_assignments == 1);
    }
    return satisfies;
}

// called once at the end
bool Instance::satisfies_capacity_constraint() {
    bool satisfies = true;
    for (Agent & a : agent_) {
        satisfies &= a.satisfies_capacity_constraint();
    }
    return satisfies;
}

// called once at the end
double Instance::value() {
    double value = 0.0;
    for (Agent & a : agent_) {
        value += a.compute_value();
    }
    return value;
}

