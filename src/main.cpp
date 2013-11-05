#include <iostream>
#include <fstream>
#include <vector>
#include "heuristic.h"
#include "instance.h"
#include "weight_function.h"

using namespace std;


int main() {
    ifstream instance_file;
    const char file_name[] = "instances/gap1.txt";
    instance_file.open(file_name);

    if(instance_file.is_open()) {
        vector<Instance> instance;
        load(instance_file, instance);

        cout << "no instance ?" << endl;
        if (instance.empty() == true)
            cout << "yep, it's empty" << endl;
        else
            cout << "no, there is at least one" << endl;

        instance[0].initialise_possible_tasks();
        instance[0].show_possible_tasks();
        instance[0].remove_impossible_tasks();
        instance[0].show_possible_tasks();
        instance[0].compute_desirability(Weight);

        if (instance.empty() != 0) {
            Heuristic heuristic_weight = Heuristic(instance[0], Weight);
        }
    } 
    return 0;
}

