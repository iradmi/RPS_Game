/// (c) Copyright:
/// This file is part of Rock-Paper-Scissors project.
/// This is a free software: you can redistribute it and/or modify it under 
/// the terms of the GNU General Public License as published by Free Software Foundation, 
/// either version 3 of the License, or (at your option) any later version.

#ifndef RPS_PROJECT_IRANDOM_NUMBER_GENERATOR_H
#define RPS_PROJECT_IRANDOM_NUMBER_GENERATOR_H

#include <cstdint>
#include <concepts>

namespace Rng {

template <typename EngineT>
concept EngineC = requires(EngineT engine) {
    { engine.generateRandomNumber(int64_t {}, int64_t {}) } -> std::same_as<int64_t>;
};

} // namespace Rng
#endif // RPS_PROJECT_IRANDOM_NUMBER_GENERATOR_H
