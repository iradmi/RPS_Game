/// (c) Copyright:
/// This file is part of Rock-Paper-Scissors project.
/// This is a free software: you can redistribute it and/or modify it under 
/// the terms of the GNU General Public License as published by Free Software Foundation, 
/// either version 3 of the License, or (at your option) any later version.

#include <cstdint>

#ifndef RPS_PROJECT_IRANDOM_NUMBER_GENERATOR_H
#define RPS_PROJECT_IRANDOM_NUMBER_GENERATOR_H

namespace Rng {

class IRandomNumberGenerator {
public:
    IRandomNumberGenerator() = default;

    IRandomNumberGenerator(const IRandomNumberGenerator& other) = delete;
    IRandomNumberGenerator(IRandomNumberGenerator&& other) noexcept = default;

    IRandomNumberGenerator& operator=(const IRandomNumberGenerator& other) = delete;
    IRandomNumberGenerator& operator=(IRandomNumberGenerator&& other) noexcept = default;

    virtual ~IRandomNumberGenerator() = default;

    /// Brief:      Function returns random number between param lower_bound and upper_bound.
    virtual int64_t generateRandomNumber(int64_t upperBound, int64_t lowerBound) = 0;
};

} // namespace Rng
#endif // RPS_PROJECT_IRANDOM_NUMBER_GENERATOR_H
