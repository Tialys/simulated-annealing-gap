#include <iostream>
#include <fstream>
#include <vector>
#include "heuristic.h"
#include "instance.h"
#include "weight_function.h"

using namespace std;


int main() {
    ifstream instance_file;
    const char file_name[] = "instances/gap9.txt";
    instance_file.open(file_name);

    if(instance_file.is_open()) {
        vector<Heuristic> heuristic;
        //WeightFunction weight_function = WeightMaxCapacityRatio;
        WeightFunction weight_function = MinusGainWeightRatio;
        vector<Instance> instance;

        load(instance_file, instance);
        cout << int(instance.size()) << " instances loaded" << endl;

        for (Instance & i : instance) {
            Heuristic h = Heuristic(i, weight_function);
            heuristic.push_back(h);
        }
        for (Heuristic & h : heuristic) {
            //h.show_solution();
            h.solve();

            //h.show_solution();
            h.show_value();
            //h.show_information();
            cout << "Achieved in " << h.get_nb_iterations() << " iterations" << endl;

            if (h.admissible_solution()) {
                h.initialise_neighbourhood();
                h.compute_neighbourhood_values();
            } else {
                cout << "               NON ADMISSIBLE SOLUTION" << endl;
            }
        }
    } 
    return 0;
}

