/// (c) Copyright:
/// This file is part of Rock-Paper-Scissors project.
/// This is a free software: you can redistribute it and/or modify it under 
/// the terms of the GNU General Public License as published by Free Software Foundation, 
/// either version 3 of the License, or (at your option) any later version.

#ifndef RPS_PROJECT_IGAME_H
#define RPS_PROJECT_IGAME_H

#include <concepts>

namespace Game {

template <typename TGame>
concept GameC = requires(TGame game) {
    { game.run() } -> std::same_as<void>;
};

} // namespace Game

#endif // RPS_PROJECT_IGAME_H
