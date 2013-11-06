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
             map<int, double> gain,
             map<int, double>  weight)
            :
             id_(id),
             max_capacity_(max_capacity),
             current_capacity_(current_capacity),
             gain_(gain),
             weight_(weight)
{
    vector<int> possible_tasks_;
    int min_weight_task_;
    double desirability_;
    vector<int> assigned_tasks_;
}

int Agent::get_id() {
    return id_;
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

void Agent::show_possible_tasks() {
    cout << int(possible_tasks_.size()) << " possible tasks: ";
    for (int t : possible_tasks_) {
        cout << t << " ";
    }
    cout << endl;
}

void Agent::show_assigned_tasks() {
    cout << " assigned tasks (" << int(assigned_tasks_.size()) << "): ";
    for (int t : assigned_tasks_) {
        cout << t << "(agent " << id_ << ") ";
    }
    cout << endl;
}

void Agent::cross_out(int task) {
    possible_tasks_.erase(remove(possible_tasks_.begin(),
                                 possible_tasks_.end(),
                                 task),
                          possible_tasks_.end());
}

int Agent::get_nb_unassigned_tasks() {
    return int(possible_tasks_.size());
}

void Agent::decrease_capacity(int weight) {
    current_capacity_ -= weight;
}

void Agent::assign(int task) {
    assigned_tasks_.emplace_back(task);
    decrease_capacity(get_weight(task));
}

void Agent::initialise_possible_tasks(vector<int> task) {
    for (int t : task) {
        if (get_weight(t) <= max_capacity_)
            possible_tasks_.emplace_back(t);
    }
}

void Agent::remove_impossible_tasks() {
    vector<int>::iterator it = possible_tasks_.begin();
    for (; it != possible_tasks_.end(); ++it) {
        //cout << get_weight(*it) << endl;
        if (get_weight(*it) > max_capacity_)
            possible_tasks_.erase(it);
    }
    /*
    cout << "possible tasks' weight" << endl;
    for (int t : possible_tasks_) {
        cout << "task " <<  t 
             << " of weight " << get_weight(t)<< endl;
    }
    */
}

void Agent::find_min_weight_task(WeightFunction weight_function) {
    double min_weight;
    int min_weight_task;
    
    switch(weight_function)
    {   
        case Gain:
            min_weight_task = possible_tasks_[0];
            min_weight = get_gain(min_weight_task);
            for (int t : possible_tasks_)
            {
                double current_weight = get_gain(t);
                if (current_weight < min_weight) {
                    min_weight_task = t;
                    min_weight = current_weight;
                }
            }
            break;
        case Weight:
            min_weight_task = possible_tasks_[0];
            min_weight = get_weight(min_weight_task);
            for (int t : possible_tasks_)
            {
                double current_weight = get_weight(t);
                if (current_weight < min_weight) {
                    min_weight_task = t;
                    min_weight = current_weight;
                }
            }
            /*
            cout << "Agent #" << id_ << endl;
            cout << "    minimum weight task #" << min_weight_task
                 << " of weight " << min_weight
                 << endl;
            */
            break;
        case WeightMaxCapacityRatio:
            min_weight_task = possible_tasks_[0];
            min_weight = get_weight_max_capacity_ratio(min_weight_task);
            for (int t : possible_tasks_)
            {
                double current_weight = get_weight_max_capacity_ratio(t);
                if (current_weight < min_weight) {
                    min_weight_task = t;
                    min_weight = current_weight;
                }
            }
            break;
        case MinusGainWeightRatio:
            min_weight_task = possible_tasks_[0];
            min_weight = get_gain_weight_ratio(min_weight_task);
            for (int t : possible_tasks_)
            {
                double current_weight = get_gain_weight_ratio(t);
                if (current_weight < min_weight) {
                    min_weight_task = t;
                    min_weight = current_weight;
                }
            }
            break;
    }
    min_weight_task_ = min_weight_task;
}

int Agent::get_min_weight_task() {
    return min_weight_task_;
}

void Agent::compute_desirability(WeightFunction weight_function) {
    find_min_weight_task(weight_function);
    int min_weight_task = get_min_weight_task();

    double min_weight;
    double desirability;
    
    switch(weight_function)
    {
    case Gain:
        min_weight = get_gain(min_weight_task);
        if (possible_tasks_[0] != min_weight_task)
            desirability = get_gain(possible_tasks_[0]) - min_weight;
        else
            desirability = get_gain(possible_tasks_[1]) - min_weight;
        for (int t : possible_tasks_) {
            if (t != min_weight_task) {
                double current_desirability = get_gain(t)- min_weight;
                if (current_desirability < desirability)
                    desirability = current_desirability;
            }
        }
        break;
    case Weight:
        min_weight = get_weight(min_weight_task);
        if (possible_tasks_[0] != min_weight_task)
            desirability = get_weight(possible_tasks_[0]) - min_weight;
        else
            desirability = get_weight(possible_tasks_[1]) - min_weight;
        for (int t : possible_tasks_) {
            if (t != min_weight_task) {
                double current_desirability = get_weight(t) - min_weight;
                if (current_desirability < desirability)
                    desirability = current_desirability;
            }
        }
        break;
    case WeightMaxCapacityRatio:
        min_weight = get_weight_max_capacity_ratio(min_weight_task);
        if (possible_tasks_[0] != min_weight_task)
            desirability = get_weight_max_capacity_ratio(possible_tasks_[0])
                         - min_weight;
        else
            desirability = get_weight_max_capacity_ratio(possible_tasks_[1])
                         - min_weight;
        for (int t : possible_tasks_) {
            if (t != min_weight_task) {
                double current_desirability = get_weight_max_capacity_ratio(t)
                                            - min_weight;
                if (current_desirability < desirability)
                    desirability = current_desirability;
            }
        }
        break;
    case MinusGainWeightRatio:
        min_weight = get_gain_weight_ratio(min_weight_task);
        if (possible_tasks_[0] != min_weight_task)
            desirability = get_gain_weight_ratio(possible_tasks_[0])
                         - min_weight;
        else
            desirability = get_gain_weight_ratio(possible_tasks_[1])
                         - min_weight;
        for (int t : possible_tasks_) {
            if (t != min_weight_task) {
                double current_desirability = get_gain_weight_ratio(t)
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
