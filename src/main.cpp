#include <iostream>
#include <fstream>
#include <vector>
#include "heuristic.h"
#include "instance.h"
#include "weight_function.h"

using namespace std;

WeightFunction to_weight_function(const string & s) {
    if (s == "Gain") return Gain;
    if (s == "Weight") return Weight;
    if (s == "WeightMaxCapacityRatio") return WeightMaxCapacityRatio;
    if (s == "MinusGainWeightRatio") return MinusGainWeightRatio;
    throw runtime_error("Maybe you mistyped the weight function you wanted?");
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <file name> <weight function>" << endl;
    } else {
        ifstream instance_file;
        instance_file.open(argv[1]);

        if(instance_file.is_open()) {
            vector<Heuristic> heuristic;
            vector<Instance> instance;
            WeightFunction weight_function = to_weight_function(argv[2]);

            load(instance_file, instance);
            cout << int(instance.size()) << " instances loaded" << endl;

            for (Instance & i : instance) {
                Heuristic h = Heuristic(i, weight_function);
                heuristic.push_back(h);
            }
            for (Heuristic & h : heuristic) {
                h.solve();

                cout << "SOLUTION OF VALUE: " << h.value() << endl;
                cout << "Achieved in " << h.get_nb_iterations() << " iterations" << endl;
                cout << endl;

                if (h.admissible_solution()) {
                    h.initialise_neighbourhood();
                    h.ascend();
                } else {
                    cout << "               NON ADMISSIBLE SOLUTION" << endl;
                }
                cout << "================" << endl;
            }
        } 
    }
    return 0;
}

