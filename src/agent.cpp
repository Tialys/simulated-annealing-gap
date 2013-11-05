#include "agent.h"

/*
 * Constructor
 * args: 
 * returns: partially initialised Agent, does not compute desirability,
 *          minimum weight task, possible tasks.
 */
Agent::Agent(int id,
             double max_capacity,
             double current_capacity,
             map<const Task, int>  index,
             map<int, double> gain,
             map<int, double>  weight)
            :
             id_(id),
             max_capacity_(max_capacity),
             current_capacity_(current_capacity),
             index_(index),
             gain_(gain),
             weight_(weight)
{
    vector<Task> possible_tasks;
    possible_tasks_ = possible_tasks;
}

double Agent::get_gain(int task) {
    return gain_[task];
}

double Agent::get_weight(int task) {
    return weight_[task];
}

double Agent::get_desirability() {
    return desirability_;
}

double Agent::get_gain_weight_ratio(int task) {
    return gain_[task] / weight_[task];
}

double Agent::get_weight_max_capacity_ratio(int task) {
    return weight_[task] / max_capacity_;
}

void Agent::initialise_possible_tasks(vector<Task> task) {
    for (Task t : task) {
        if (get_weight(index_[t]) <= max_capacity_)
            possible_tasks_.push_back(t);
    }
}

void Agent::remove_impossible_tasks() {
    for (Task t : possible_tasks_) {
        if (get_weight(index_[t]) > max_capacity_)
            possible_tasks_.push_back(t);
    }
}

void Agent::find_min_weight_task(WeightFunction weight_function) {
    vector<Task>::iterator it = possible_tasks_.begin();
    double min_weight;
    int min_weight_task;
    
    switch(weight_function)
    {   
        case Gain:
            min_weight_task = possible_tasks_[0].get_id();
            min_weight = get_gain(min_weight_task);
            for (Task t : possible_tasks_)
            {
                int current_task = t.get_id();
                double current_weight = get_gain(current_task);
                if (current_weight < min_weight) {
                    min_weight_task = current_task;
                    min_weight = current_weight;
                }
            }
            break;
        case Weight:
            min_weight_task = possible_tasks_[0].get_id();
            min_weight = get_weight(min_weight_task);
            for (Task t : possible_tasks_)
            {
                int current_task = t.get_id();
                double current_weight = get_weight(current_task);
                if (current_weight < min_weight) {
                    min_weight_task = current_task;
                    min_weight = current_weight;
                }
            }
            break;
        case WeightMaxCapacityRatio:
            min_weight_task = possible_tasks_[0].get_id();
            min_weight = get_weight_max_capacity_ratio(min_weight_task);
            for (Task t : possible_tasks_)
            {
                int current_task = t.get_id();
                double current_weight = get_weight_max_capacity_ratio(current_task);
                if (current_weight < min_weight) {
                    min_weight_task = current_task;
                    min_weight = current_weight;
                }
            }
            break;
        case MinusGainWeightRatio:
            min_weight_task = possible_tasks_[0].get_id();
            min_weight = get_gain_weight_ratio(min_weight_task);
            for (Task t : possible_tasks_)
            {
                int current_task = t.get_id();
                double current_weight = get_gain_weight_ratio(current_task);
                if (current_weight < min_weight) {
                    min_weight_task = current_task;
                    min_weight = current_weight;
                }
            }
            break;
    }
    min_weight_task_ = min_weight_task;
}

Task Agent::get_min_weight_task(WeightFunction weight_function) {
    find_min_weight_task(weight_function);
    for (Task t : possible_tasks_) {
        if (index_[t] == min_weight_task_.get_id()) {
            return t;
        }
    }
    return possible_tasks_[0];
}

void Agent::compute_desirability(WeightFunction weight_function) {
    Task min_weight_task = get_min_weight_task(weight_function);

    double min_weight;
    double desirability;
    
    switch(weight_function)
    {
    case Gain:
        min_weight = get_gain(min_weight_task.get_id());
        if (possible_tasks_[0] != min_weight_task)
            desirability = get_gain(index_[possible_tasks_[0]]) - min_weight;
        else
            desirability = get_gain(index_[possible_tasks_[1]]) - min_weight;
        for (Task t : possible_tasks_) {
            if (t != min_weight_task) {
                double current_desirability = get_gain(t.get_id()) - min_weight;
                if (current_desirability < desirability)
                    desirability = current_desirability;
            }
        }
        break;
    case Weight:
        min_weight = get_weight(min_weight_task.get_id());
        if (possible_tasks_[0] != min_weight_task)
            desirability = get_weight(index_[possible_tasks_[0]]) - min_weight;
        else
            desirability = get_weight(index_[possible_tasks_[1]]) - min_weight;
        for (Task t : possible_tasks_) {
            if (t != min_weight_task) {
                double current_desirability = get_weight(t.get_id()) - min_weight;
                if (current_desirability < desirability)
                    desirability = current_desirability;
            }
        }
        break;
    case WeightMaxCapacityRatio:
        min_weight = get_weight_max_capacity_ratio(min_weight_task.get_id());
        if (possible_tasks_[0] != min_weight_task)
            desirability = get_weight_max_capacity_ratio(index_[possible_tasks_[0]])
                         - min_weight;
        else
            desirability = get_weight_max_capacity_ratio(index_[possible_tasks_[1]])
                         - min_weight;
        for (Task t : possible_tasks_) {
            if (t != min_weight_task) {
                double current_desirability = get_weight_max_capacity_ratio(t.get_id())
                                            - min_weight;
                if (current_desirability < desirability)
                    desirability = current_desirability;
            }
        }
        break;
    case MinusGainWeightRatio:
        min_weight = get_gain_weight_ratio(min_weight_task.get_id());
        if (possible_tasks_[0] != min_weight_task)
            desirability = get_gain_weight_ratio(index_[possible_tasks_[0]])
                         - min_weight;
        else
            desirability = get_gain_weight_ratio(index_[possible_tasks_[1]])
                         - min_weight;
        for (Task t : possible_tasks_) {
            if (t != min_weight_task) {
                double current_desirability = get_gain_weight_ratio(t.get_id())
                                            - min_weight;
                if (current_desirability < desirability)
                    desirability = current_desirability;
            }
        }
        break;
    }
    desirability_ = desirability;
}

double Agent::get_max_capacity() {
    return max_capacity_;
}
