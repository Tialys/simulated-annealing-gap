#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "agent.h"
#include "instance.h"

using namespace std;

int main() {
    ifstream instance_file;
    instance_file.open("instances/gap1.txt");
    
    
    if(instance_file.is_open()) {
        int nb_instances;
        instance_file >> nb_instances;
        cout << "Instance file containing " << nb_instances << " instances" << endl;

        vector<Instance> instance;
        for (int i=0; i < nb_instances; i++) {
            cout << ">>>>>> Instance #" << i << endl;
            Instance temp_instance = read(instance_file);
            instance.push_back(temp_instance);
        }

        //Instance instance1 = read(instance_file);
        cout << "# of agents: " << instance[0].nb_agents << endl;
        cout << "# of tasks: " << instance[0].nb_tasks << endl;

    } else {
        cout << "Could not find instance" << endl;
    }
    return 0;
}
