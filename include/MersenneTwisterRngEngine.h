/// (c) Copyright:
/// This file is part of Rock-Paper-Scissors project.
/// This is a free software: you can redistribute it and/or modify it under 
/// the terms of the GNU General Public License as published by Free Software Foundation, 
/// either version 3 of the License, or (at your option) any later version.

#ifndef RPS_PROJECT_MERSENNE_TWISTER_RNG_ENGINE_H
#define RPS_PROJECT_MERSENNE_TWISTER_RNG_ENGINE_H

/// CPP standard libs
#include <random>

/// project libs
#include "RandomNumberGeneratorConcept.h"

namespace MtEngine {

class MersenneTwisterRngEngine {
public:
    MersenneTwisterRngEngine();
    
    /// Brief:      Function returns random number between param lower_bound and upper_bound.
    ///             Uniform distribution is used.
    /// Param[in]:  lowerBound - minimum number the generator will generate values from.
    /// Param[in]:  uperBound  - maximum number the generator will generate values to.
    /// Return:     Random number between [lowerBound, uperBound].
    int64_t generateRandomNumber(int64_t lowerBound, int64_t uperBound);
    
private:
    std::random_device _rd;  // a seed source for the random number engine
    std::mt19937_64    _rng;
};

} // MtEngine namespace 

#endif // RPS_PROJECT_MERSENNE_TWISTER_RNG_ENGINE_H
