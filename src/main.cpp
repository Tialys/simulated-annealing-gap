#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "agent.h"
#include "instance.h"
#include "weight_function.h"

using namespace std;


int main() {
    ifstream instance_file;
    const char file_name[] = "instances/gap1.txt";
    
    load(instance_file, file_name, WeightMaxCapacityRatio);
    
    return 0;
}

