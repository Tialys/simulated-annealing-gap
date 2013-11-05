#include "heuristic.h"

Heuristic::Heuristic(Instance instance,
                     WeightFunction weight_function) : instance_(instance) {
   instance_.initialise_possible_tasks();
   instance_.compute_desirability(weight_function);
}
/*
int Heuristic::find_max_desirability_job() {
    //double max_desirability = instance.agent[0].get_desirability();
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
*/
