#include "heuristic.h"

Heuristic::Heuristic(&Instance instance) {
    this->instance = instance;
    
    for (int agentId = 0; agentId < instance.nb_agents; agentId++) {
        Agent& agent = instance.agent[agentId];
        Task& tasks = instance.task;
        agent.set_current_capacity(i.get_max_capacity());
        agent.initialise_possible_tasks(tasks);
    }
}

int Heuristic::find_max_desirability_job() {
    double max_desirability = instance.agent[0].get_desirability();
    int max_desirability_job = 0;
    for (int agentId = 1; agentId < instance.nb_agents; agentId++) {
        double current_desirability = instance.agent[agentId].get_desirability();
        if (current_desirability > max_desirability)
            max_desirability = current_desirability;
            max_desirability_job = agentId;
    }
    return max_desirability_job;
}

void Heuristic::assign(int max_desirability_job) {

}
