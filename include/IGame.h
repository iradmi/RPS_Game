/// (c) Copyright:
/// This file is part of Rock-Paper-Scissors project.
/// This is a free software: you can redistribute it and/or modify it under 
/// the terms of the GNU General Public License as published by Free Software Foundation, 
/// either version 3 of the License, or (at your option) any later version.

#ifndef RPS_PROJECT_IGAME_H
#define RPS_PROJECT_IGAME_H

namespace Game {

class IGame {
public:
    IGame() = default;

    IGame(const IGame& other) = delete;
    IGame(IGame&& other) noexcept = default;

    IGame& operator=(const IGame& other) = delete;
    IGame& operator=(IGame&& other) noexcept = default;

    virtual ~IGame() = default;
    
    virtual void run() = 0;
};  // class IGame

} // namespace Game

#endif // RPS_PROJECT_IGAME_H
