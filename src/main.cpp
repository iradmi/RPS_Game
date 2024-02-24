/// (c) Copyright:
/// This file is part of Rock-Paper-Scissors project.
/// This is a free software: you can redistribute it and/or modify it under 
/// the terms of the GNU General Public License as published by Free Software Foundation, 
/// either version 3 of the License, or (at your option) any later version.

/// CPP standard libs
#include "RpsGame.h"
#include "RpsGame.cpp"
#include "MersenneTwisterRngEngine.h"

int main() {
    Game::RpsGame<MtEngine::MersenneTwisterRngEngine> game(std::move(MtEngine::MersenneTwisterRngEngine{}));

    game.run();

    return 0;
}
