/// (c) Copyright:
/// This file is part of Rock-Paper-Scissors project.
/// This is a free software: you can redistribute it and/or modify it under 
/// the terms of the GNU General Public License as published by Free Software Foundation, 
/// either version 3 of the License, or (at your option) any later version.

/// project includes
#include "MersenneTwisterRngEngine.h"

namespace MtEngine {

MersenneTwisterRngEngine::MersenneTwisterRngEngine() : _rd(), _rng(_rd()) {} // mersenne_twister_engine seeded with seed source

int64_t MersenneTwisterRngEngine::generateRandomNumber(int64_t lowerBound, int64_t upperBound) {
    std::uniform_int_distribution<std::mt19937_64::result_type> dist(lowerBound, upperBound); // distribution in range [lower_bound, upper_bound]
    
    return dist(_rng);
}

} //MtEngine namespace 
