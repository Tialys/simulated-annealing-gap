#ifndef WEIGHT_FUNCTION_H_INCLUDED
#define WEIGHT_FUNCTION_H_INCLUDED

enum WeightFunction {
    MinusGain,
    Weight,
    WeightMaxCapacityRatio,
    MinusGainWeightRatio,
};

enum NeighbourhoodType {
    Swap,
    Give,
};

#endif
