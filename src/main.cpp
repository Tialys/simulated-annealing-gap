#include <iostream>
#include <fstream>
#include <vector>
#include "heuristic.h"
#include "instance.h"
#include "weight_function.h"

using namespace std;


int main() {
    ifstream instance_file;
    const char file_name[] = "instances/gap12.txt";
    instance_file.open(file_name);

    if(instance_file.is_open()) {
        vector<Heuristic> heuristic;
        WeightFunction weight_function = Weight;
        vector<Instance> instance;

        load(instance_file, instance);
        cout << int(instance.size()) << " instances loaded" << endl;
        
        for (Instance & i : instance) {
            Heuristic h = Heuristic(i, weight_function);
            heuristic.push_back(h);
        }

        for (Heuristic & h : heuristic) {
            h.assign();
        }
    } 
    return 0;
}

