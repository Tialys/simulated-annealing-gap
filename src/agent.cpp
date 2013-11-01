#include "agent.h"

Agent::Agent(int id, int nb_tasks) {
    this->id = id;
    this->nb_tasks = nb_tasks;
}

void Agent::set_max_capacity(int max_capacity) {
    this->max_capacity = max_capacity;
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

void Agent::task_assignment(bool assignment) {
    task.push_back(assignment);
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

double Agent::get_gain_weight_ratio(int task){
    return gain_weight_ratio[task];
}

void Agent::show() {
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
    cout << " " << endl;
}
