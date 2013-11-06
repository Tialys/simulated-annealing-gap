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
        vector<Heuristic> heuristic;
        WeightFunction weight_function = WeightMaxCapacityRatio;
        vector<Instance> instance;

        load(instance_file, instance);
        cout << int(instance.size()) << " instances loaded" << endl;

        for (Instance & i : instance) {
            Heuristic h = Heuristic(i, weight_function);
            heuristic.push_back(h);
        }
        
        //for (Heuristic & h : heuristic) {
            Heuristic & h = heuristic[3];
            int nb_iterations = 0;
            h.show_solution();
            while (h.remaining_tasks()) {
                cout << "ITERATION " << nb_iterations << endl;
                h.assign();
                h.show_solution();
                nb_iterations++;
            }
            h.set_nb_iterations(nb_iterations);
            h.show_solution();
            h.show_value();
            cout << "====================" << endl;
            h.show_assignment();
            cout << "====================" << endl;
            cout << "Solution satisfies assignment constraint? "
                 << (h.satisfies_assignment_constraint() ? "true" : "false")
                 << endl;
            cout << "Solution satisfies capacity constraint? "
                 << (h.satisfies_capacity_constraint() ? "true" : "false")
                 << endl;
            cout << "Solution is realisable? "
                 << (h.satisfies_capacity_constraint() &&
                     h.satisfies_assignment_constraint()
                     ? "true" : "false")
                 << endl;
            cout << "Achieved in " << h.get_nb_iterations() << " iterations" << endl;
        //}
    } 
    return 0;
}

