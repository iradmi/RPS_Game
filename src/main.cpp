/// (c) Copyright:
/// This file is part of Rock-Paper-Scissors project.
/// This is a free software: you can redistribute it and/or modify it under 
/// the terms of the GNU General Public License as published by Free Software Foundation, 
/// either version 3 of the License, or (at your option) any later version.

/// CPP standard libs
#include <memory>

#include "RpsGame.h"
#include "MersenneTwisterRngEngine.h"

int main() {
	std::shared_ptr<Rng::IRandomNumberGenerator> rng = std::make_shared<MtEngine::MersenneTwisterRngEngine>();
    std::unique_ptr<Game::IGame> game = std::make_unique<Game::RpsGame>(rng);

    game->run();

    return 0;
}
