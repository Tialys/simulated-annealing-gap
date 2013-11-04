#include "agent.h"

Agent::Agent(int id, int nb_tasks) {
    this->id = id;
    this->nb_tasks = nb_tasks;
}

void Agent::set_max_capacity(int max_capacity) {
    this->max_capacity = max_capacity;
}

void Agent::set_current_capacity(int current_capacity) {
    this->current_capacity = current_capacity;
}

void Agent::task_gain(pair<int, double> gain_taskId) {
    gain.insert(gain_taskId);
}

void Agent::task_weight(pair<int, double> weight_taskId) {
    weight.insert(weight_taskId);
}

void Agent::compute_gain_weight_ratio() {
    int g_size = gain.size();
    int w_size = weight.size();
    if (g_size == nb_tasks && w_size == nb_tasks) {
        for (int task = 0; task < nb_tasks; task++) {
            pair<int, double> p(task, gain[task] / weight[task]);
            gain_weight_ratio.insert(p);
        }
    }
}

void Agent::initialise_possible_tasks(vector<Task> task) {
    for (id = 0; id < nb_tasks; id++) {
        if (get_gain(id) < max_capacity) {
            Task possible_task = Task(id, 0);
            possible_tasks.push_back(possible_task);
        }
    }
}

void Agent::update_possible_tasks(double current_capacity) {
    for (id = 0; id < (int) possible_tasks.size(); id++) {
        if (get_gain(id) < current_capacity)
            possible_tasks.erase(possible_tasks.begin() + id);
    }
}

double Agent::get_gain(int task) {
    return gain[task];
}

double Agent::get_weight(int task) {
    return weight[task];
}

double Agent::get_max_capacity() {
    return max_capacity;
}

double Agent::get_desirability() {
    return current_desirability;
}

double Agent::get_gain_weight_ratio(int task){
    return gain_weight_ratio[task];
}

double Agent::get_weight_max_capacity_ratio(int task) {
    return weight[task] / max_capacity;
}

void Agent::find_min_weight_task(WeightFunction weight_function) {
    double min_weight;
    int min_weight_task;
    
    switch(weight_function)
    {   
        case Gain:
            min_weight = get_gain(0);
            for (int taskId = 1; taskId < (int) possible_tasks.size(); taskId++) {
                if (get_gain(taskId) < min_weight) {
                    min_weight = get_gain(taskId);
                    min_weight_task = taskId;
                }
            }
            break;
        case Weight:
            min_weight = get_weight(0);
            for (int taskId = 1; taskId < (int) possible_tasks.size(); taskId++) {
                if (get_weight(taskId) < min_weight) {
                    min_weight = get_weight(taskId);
                    min_weight_task = taskId;
                }
            }
            break;
        case WeightMaxCapacityRatio:
            min_weight = get_weight_max_capacity_ratio(0);
            for (int taskId = 1; taskId < (int) possible_tasks.size(); taskId++) {
                if (get_weight_max_capacity_ratio(taskId) < min_weight) {
                    min_weight = get_weight_max_capacity_ratio(taskId);
                    min_weight_task = taskId;
                }
            }
            break;
        case MinusGainWeightRatio:
            min_weight = - get_gain_weight_ratio(0);
            for (int taskId = 1; taskId < (int) possible_tasks.size(); taskId++) {
                if (- get_gain_weight_ratio(taskId) < min_weight) {
                    min_weight = - get_gain_weight_ratio(taskId);
                    min_weight_task = taskId;
                }
            }
            break;
    }
    this->min_weight_task = min_weight_task;
}

void Agent::desirability(WeightFunction weight_function) {
    int min_weight_task = find_min_weight_task(weight_function);
    double min_weight;
    double desirability;
    vector<Task>::iterator it = possible_tasks.begin();
    vector<Task>::iterator it_min_weight_task = possible_tasks.begin() + min_weight_task;
    switch(weight_function)
    {
        case Gain:
            min_weight = get_gain(0);
            for (; it != possible_tasks.end() && it != it_min_weight_task ; it++) {
                taskId = it - possible_tasks.begin();
                current_desirability = get_gain(taskId)
                                     - get_gain(min_weight_task);
                if (current_desirability < desirability)
                    desirability = current_desirability;
            }
            break;
        case Weight:
            min_weight = get_weight(0);
            for (; it != possible_tasks.end() && it != it_min_weight_task ; it++) {
                taskId = it - possible_tasks.begin();
                current_desirability = get_weight(taskId)
                                     - get_weight(min_weight_task);
                if (current_desirability < desirability)
                    desirability = current_desirability;
            }
            break;
        case WeightMaxCapacityRatio:
            min_weight = get_weight_max_capacity_ratio(it->first);
            for (; it != possible_tasks.end() && it != it_min_weight_task ; it++) {
                taskId = it - possible_tasks.begin();
                current_desirability = get_weight_max_capacity_ratio(taskId)
                                     - get_weight_max_capacity_ratio(min_weight_task);
                if (current_desirability < desirability)
                    desirability = current_desirability;
            }
            break;
        case MinusGainWeightRatio:
            min_weight = get_gain_weight_ratio(it->first);
            for (; it != possible_tasks.end() && it != it_min_weight_task ; it++) {
                taskId = it - possible_tasks.begin();
                current_desirability = get_gain_weight_ratio(taskId)
                                     - get_gain_weight_ratio(min_weight_task);
                if (current_desirability < desirability)
                    desirability = current_desirability;
            }
            break;
    }
    this->current_desirability = desirability;
}

void Agent::show(WeightFunction weight_function) {
    cout << "Agent #" << id << endl;
    cout << "   Number of tasks: " << nb_tasks << endl;
    cout << "   Maximum capacity: " << max_capacity << endl;
    
    cout << "   Gain per task: " << endl;
    for (int task = 0; task < nb_tasks; task++) {
        cout << gain[task] << " ";
    }
    cout << endl;
    
    cout << "   Weight per task: " << endl;
    for (int task = 0; task < nb_tasks; task++) {
        cout << weight[task] << " ";
    }
    cout << endl;
    
    cout << "   Gain/weight per task: " << endl;
    for (int task = 0; task < nb_tasks; task++) {
        cout << gain_weight_ratio[task] << " ";
    }
    cout << endl;

    desirability(weight_function);
    //cout << "   Desirability: " << get_desirability() << endl;

    cout << " " << endl;
}
