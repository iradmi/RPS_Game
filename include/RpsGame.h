/// (c) Copyright:
/// This file is part of Rock-Paper-Scissors project.
/// This is a free software: you can redistribute it and/or modify it under 
/// the terms of the GNU General Public License as published by Free Software Foundation, 
/// either version 3 of the License, or (at your option) any later version.

#ifndef RPS_PROJECT_RPS_GAME_H
#define RPS_PROJECT_RPS_GAME_H

/// CPP standard lib includes
#include <string_view>
#include <chrono>
#include <sstream>
#include <memory>
#include <iostream>

/// project includes
#include "IRandomNumberGenerator.h"
#include "IGame.h"


namespace Game {
using milliseconds_t = std::chrono::milliseconds;
/// Rock-Papers-Scissors Game class
class RpsGame : public IGame {
public:
    RpsGame(std::shared_ptr<Rng::IRandomNumberGenerator> rng, 
            milliseconds_t roundsDelay = milliseconds_t(1200),
            std::istream& iStream = std::cin,
            std::ostream& oStream = std::cout);

    /// IGame inherited
    void run() override;
  
private:
                 
    enum class Symbol : uint8_t { Rock     = 1,
                                  Paper    = 2,
                                  Scissors = 3 };

    enum class Player : uint8_t { None,
                                  User,
                                  PC };

    
    /// Welcome message
    void    printWelcomeMsg() const;
    /// Instructions about symbol meaning and which number represents which symbol
    void    printSymbolInfo() const;
    /// Printing information about the round (round number)
    void    printRoundInfo(size_t round) const;
    
    /// Ensure number of rounds is in valid range @see _ROUNDS_NUM_MIN and @see _ROUNDS_NUM_MAX
    /// Param[in] Chosen number of rounds for game
    /// Returns true if number of rounds is in valid range, otherwise false
    bool    isNumberOfRoundsValid(size_t num) const;
    /// Ensure entered symbol is valid
    /// Param[in] Chosen symbol number
    /// Returns true if symbol's number is in valid range, otherwise false
    bool    isSymbolNumberValid(size_t num) const;
    
    /// Generate randomly symbol that computer will play
    /// Return Symbol chosen by computer
    Symbol  generateComputerSymbol() const;
    
    /// Clear console input buffer on invalid input
    void    refreshConsoleInput() const;
    
    /// Let user enter the number of rounds game will be played for
    /// Return - number of rounds for the game.
    size_t  promptAndValidateNumberOfRoundsInput();
    
    /// Perform one round of Rock, Papers, Scissors game
    void    playRound();
    
    /// Prompt user to enter wanted symbol number, validate it and return the symbol
    /// Return - User entered symbol
    Symbol  promptUserSymbolInput();
    
    /// Establish and return the winer of the round; keep the score
    /// Param[in] userSymbol
    /// Param[in] computerSymbol
    /// Return winner
    Player  determineRoundWinner(Symbol userSymbol, Symbol computerSymbol) const;
    
    /// Pronounce winner
    /// Param[in] Player - winner of a round
    void    pronounceRoundWinner(Player roundWinner);
    
    /// Establish and return the winer of the round; keep the score
    /// Param[in] userSymbol
    /// Param[in] computerSymbol
    void    determineAndPronounceRoundWinner(Symbol userSymbol, Symbol computerSymbol);
    
    /// Calculate score and determine game winner
    void    pronounceGameWinner();
    
    /// Start the game; delay of @see(_roundDelay) is added between rounds for more pleasant user experience
    /// Param[in] Number of rounds of the game.
    void    startCompetition(size_t numRounds);
    
    /// Convert game symbol to its UTF representation
    /// Param[in] Symbol to convert to UTF
    /// Return    Symbol's UTF representation
    static std::string_view constexpr 
            convertSymbolToUtf(Symbol symbol);
    
    static constexpr std::string_view  _ROCK_SYMBOL_UTF     = "\U0001F44A";
    static constexpr std::string_view  _PAPER_SYMBOL_UTF    = "\U0001F590";
    static constexpr std::string_view  _SCISSORS_SYMBOL_UTF = "\U0001F91E"; // "\U0000270C";
    static constexpr std::string_view  _WRONG_SYMBOL_UTF    = "\U0001F6D1";
    static constexpr std::string_view  _PARTY_SYMBOL_UTF    = "\U0001F389";

    static constexpr uint8_t _ROUNDS_NUM_MIN = 1;
    static constexpr uint8_t _ROUNDS_NUM_MAX = 100;
    
    size_t                                        _numOfRounds;
    size_t                                        _currRoundNum;
    uint8_t                                       _userScore;
    uint8_t                                       _pcScore;
    std::shared_ptr<Rng::IRandomNumberGenerator>  _rngEngine;
    milliseconds_t                                _roundDelay; // delay for presenting the next user input prompt,
                                                               // mostly for more pleasant user experience

    std::istream& _iStream;
    std::ostream& _oStream;
}; // class RpsGame

} // namespace Game

#endif // RPS_PROJECT_RPS_GAME_H
