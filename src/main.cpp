#include <iostream>
#include <fstream>
#include <vector>
#include "heuristic.h"
#include "instance.h"
#include "weight_function.h"

using namespace std;

WeightFunction to_weight_function(const string & s) {
    if (s == "MinusGain") return MinusGain;
    if (s == "Weight") return Weight;
    if (s == "WeightMaxCapacityRatio") return WeightMaxCapacityRatio;
    if (s == "MinusGainWeightRatio") return MinusGainWeightRatio;
    throw runtime_error("Maybe you mistyped the weight function you wanted?");
}

NeighbourhoodType to_neighbourhood_type(const string & s) {
    if (s == "Swap") return Swap;
    if (s == "Give") return Give;
    throw runtime_error("Maybe you mistyped the neighbourhood type you wanted?");
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: " << argv[0]
             << " <file name> <weight function> <neighbourhood type>"
             << endl;
    } else {
        ifstream instance_file;
        instance_file.open(argv[1]);

        if(instance_file.is_open()) {
            vector<Heuristic> heuristic;
            vector<Instance> instance;
            WeightFunction weight_function = to_weight_function(argv[2]);
            NeighbourhoodType neighbourhood_type = to_neighbourhood_type(argv[3]);

            load(instance_file, instance);
            cout << int(instance.size()) << " instances loaded" << endl;

            for (Instance & i : instance) {
                Heuristic h = Heuristic(i, weight_function, neighbourhood_type);
                heuristic.push_back(h);
            }
            for (Heuristic & h : heuristic) {
                h.solve();

                cout << "SOLUTION OF VALUE: " << h.value() << endl;
                cout << "Achieved in " << h.get_nb_iterations() << " iterations" << endl;
                cout << endl;

                if (h.admissible_solution()) {
                    int nb_iterations = 0;
                    double real_value = 0.0;
                    h.create_neighbourhood();
                    h.ascend(nb_iterations, real_value);
                    cout << endl;
                    cout << "FINAL SOLUTION OF VALUE: " << real_value 
                         << " FOUND IN " << nb_iterations << " ITERATIONS"
                         << endl;
                } else {
                    cout << "               NON ADMISSIBLE SOLUTION" << endl;
                }
                cout << "================" << endl;
            }
        } 
    }
    return 0;
}
