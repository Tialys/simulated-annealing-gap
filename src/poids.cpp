#include "poids.h"
#include "instance.h"
#include "agent.h"
#include "task.h"
#include <algorithm>

int poid1 (Instance instance, Agent agent, int num_agent, int num_task){
    int poid1 = instance.agent[num_agent].get_gain(num_task);
    return(poid1);
}

int poid2 (Instance instance, Agent agent, int num_agent, int num_task){
    int poid2 = instance.agent[num_agent].get_weight(num_task);
    return(poid2);
}

int poid3 (Instance instance, Agent agent, int num_agent, int num_task){
    int poid3 = instance.agent[num_agent].get_weight(num_task)/instance.agent[num_agent].get_max_capacity();
    return(poid3);
}

int poid4 (Instance instance, Agent agent, int num_agent, int num_task){
    int poid4 = instance.agent[num_agent].get_gain_weight_ratio(num_task);
    return(poid4);
}

int min_poid (Instance instance, Agent agent, int num_agent, int num_task){
    int poid_min = min (min (poid1(instance, agent, num_agent, num_task),
            poid2(instance, agent, num_agent, num_task)),
            min (poid3(instance, agent, num_agent, num_task),
            poid4(instance, agent, num_agent, num_task)));

    return(poid_min);
}

int max_poid (Instance instance, Agent agent, int num_agent, int num_task){
    int poid_max = max (max (poid1(instance, agent, num_agent, num_task),
            poid2(instance, agent, num_agent, num_task)),
            max (poid3(instance, agent, num_agent, num_task),
            poid4(instance, agent, num_agent, num_task)));

    return(poid_max);
}

int arg_min_task (Instance instance, Agent agent, int num_agent){

    int poid_min = poid1(instance, agent, num_agent, 0);
    int task = 0;
    for(int task_it = 1; task_it < instance.nb_tasks; task_it++){
        int poid_min_temp = poid1(instance, agent, num_agent, task_it);
        if (poid_min_temp <= poid_min){
            poid_min = poid_min_temp;
            task = task_it;
        }
    }
    return (task);
}

int desirability(Instance instance, Agent agent, int num_agent){

    int arg_min = arg_min_task(instance, agent, num_agent);
    int poid_min = 0;
    if (arg_min != 0){
        poid_min = poid1(instance, agent, num_agent, 1);
    }
    else{
        poid_min = poid1(instance, agent, num_agent, 0);
    }
    for(int task_it = 1; task_it < instance.nb_tasks; task_it++){

        if(task_it != arg_min){
            int poid_min_temp = poid1(instance, agent, num_agent, task_it);
            if (poid_min_temp <= poid_min){
                poid_min = poid_min_temp;
            }
        }


    }
    int desirability = poid_min - poid1(instance, agent, num_agent, arg_min);
    return (desirability);

}









