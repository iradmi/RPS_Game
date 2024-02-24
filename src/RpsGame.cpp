/// (c) Copyright:
/// This file is part of Rock-Paper-Scissors project.
/// This is a free software: you can redistribute it and/or modify it under 
/// the terms of the GNU General Public License as published by Free Software Foundation, 
/// either version 3 of the License, or (at your option) any later version.

/// CPP standard libs
#include <iostream>
#include <cstdint>
#include <thread>

/// project includes
#include "MersenneTwisterRngEngine.h"

/// own headerss
#include "RpsGame.h"

namespace Game {

template<Rng::EngineC EngineT>
RpsGame<EngineT>::RpsGame(EngineT&& rng, 
                 milliseconds_t roundDelay,
                 std::istream& iStream,
                 std::ostream& oStream) 
    : _currRoundNum(0),
      _userScore(0),
      _pcScore(0),
      _rngEngine(rng),
      _roundDelay(roundDelay),
      _iStream(iStream),
      _oStream(oStream) {}

template<Rng::EngineC EngineT>
void RpsGame<EngineT>::printWelcomeMsg() const {
    _oStream << "\n"
             << "Welcome to "
             << "Rock ("     << convertSymbolToUtf(Symbol::Rock)     << "), "
             << "Paper ("    << convertSymbolToUtf(Symbol::Paper)    << " ), "
             << "Scissors (" << convertSymbolToUtf(Symbol::Scissors) << " ) "
             << "game!\n\n"
             << "Rules:\n"
             << "Paper "     << convertSymbolToUtf(Symbol::Paper)    
             << "  beats (wraps) rock  "      << convertSymbolToUtf(Symbol::Rock)     << "\n"
             << "Rock  "     << convertSymbolToUtf(Symbol::Rock)     
             << "  beats (blunts) scissors  " << convertSymbolToUtf(Symbol::Scissors) << "\n"
             << "Scissors  " << convertSymbolToUtf(Symbol::Scissors) 
             << "  beats (cuts) paper  "      << convertSymbolToUtf(Symbol::Paper)    << "\n\n\n";
}

template<Rng::EngineC EngineT>
void RpsGame<EngineT>::printSymbolInfo() const {
    _oStream << '\n'
             << "Pick your symbol by choosing the number:\n"
             << "1) " << _ROCK_SYMBOL_UTF     << "\t(rock)\n"
             << "2) " << _PAPER_SYMBOL_UTF    << "\t(paper)\n"
             << "3) " << _SCISSORS_SYMBOL_UTF << "\t(scissors)\n\n"
             << "Your choice is: ";
}

template<Rng::EngineC EngineT>
void RpsGame<EngineT>::printRoundInfo(size_t round) const {
    _oStream << "\n------------------ "
             << "\nROUND NUMBER " << round << "!"
             << "\n------------------ \n";
}

template<Rng::EngineC EngineT>
void RpsGame<EngineT>::refreshConsoleInput() const {
    _iStream.clear();
    _iStream.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

template<Rng::EngineC EngineT>
std::string_view constexpr RpsGame<EngineT>::convertSymbolToUtf(RpsGame::Symbol symbol) {
    switch (symbol) {
    case Symbol::Rock:     return _ROCK_SYMBOL_UTF;
    case Symbol::Paper:    return _PAPER_SYMBOL_UTF;
    case Symbol::Scissors: return _SCISSORS_SYMBOL_UTF;
    default:               return _WRONG_SYMBOL_UTF;
    }
}

template<Rng::EngineC EngineT>
bool RpsGame<EngineT>::isNumberOfRoundsValid(size_t num) const {
    return (num >= _ROUNDS_NUM_MIN && num <= _ROUNDS_NUM_MAX) ? true : false;
}

template<Rng::EngineC EngineT>
bool RpsGame<EngineT>::isSymbolNumberValid(size_t num) const {
    return (num >= static_cast<size_t>(Symbol::Rock) &&
            num <= static_cast<size_t>(Symbol::Scissors)) ? true : false;
}

template<Rng::EngineC EngineT>
RpsGame<EngineT>::Symbol RpsGame<EngineT>::generateComputerSymbol() const {
    return static_cast<Symbol>(_rngEngine.generateRandomNumber(static_cast<int64_t>(Symbol::Rock), 
                                                               static_cast<int64_t>(Symbol::Scissors)));
    
}

template<Rng::EngineC EngineT>
size_t RpsGame<EngineT>::promptAndValidateNumberOfRoundsInput() {
    bool inputInvalid = true;

    size_t numOfRndsInput = 0;
    
    auto invalidRoundsWarningMsg = [&] { _oStream << "Please enter valid number of rounds!\n\n"; };
    
    while (inputInvalid) {
        _oStream << "Enter the number of rounds (from 1 to 100): ";
        
        if (!(_iStream >> numOfRndsInput)) {
            invalidRoundsWarningMsg();
            refreshConsoleInput();
            continue;
        }

        if (isNumberOfRoundsValid(numOfRndsInput)) {
            inputInvalid = false;
            break;
        }

        invalidRoundsWarningMsg();
    }

    return numOfRndsInput;
}

template<Rng::EngineC EngineT>
RpsGame<EngineT>::Player RpsGame<EngineT>::determineRoundWinner(RpsGame::Symbol userSymbol, 
                                              RpsGame::Symbol computerSymbol) const {
    return static_cast<RpsGame::Player> ((_NUM_OF_SYMBOLS
                                          + static_cast<int>(userSymbol) 
                                          - static_cast<int>(computerSymbol)) % _NUM_OF_SYMBOLS);
}

template<Rng::EngineC EngineT>
void RpsGame<EngineT>::determineAndPronounceRoundWinner(Symbol userSymbol, Symbol computerSymbol) {
     Player roundWinner = determineRoundWinner(userSymbol, computerSymbol);
     
     _oStream << "\nYou chose " 
              << convertSymbolToUtf(userSymbol) 
              << "  whilst computer chose  " 
              << convertSymbolToUtf(computerSymbol)
              << " \n\n";
    
    auto printBeatsMsg = [&](const Symbol winner, const Symbol loser) {
        _oStream << convertSymbolToUtf(winner) 
                 << "   beats   " 
                 << convertSymbolToUtf(loser) 
                 << "\n\n";
    };

    if (roundWinner == Player::PC) { 
        _pcScore++;
        printBeatsMsg(computerSymbol, userSymbol);
        _oStream << "Computer WINS this round!\n\n";
        return;
    }
   
    if (roundWinner == Player::User) {
        _userScore++;
        printBeatsMsg(userSymbol, computerSymbol);
        _oStream << _PARTY_SYMBOL_UTF << "  You WIN this round!" << _PARTY_SYMBOL_UTF << "\n\n";
        return;
    }
    
    if (roundWinner == Player::None) {
        _oStream << "Round ends in a DRAW!\n\n";
    }
}

template<Rng::EngineC EngineT>
RpsGame<EngineT>::Symbol RpsGame<EngineT>::promptUserSymbolInput() {
    size_t userSymbolNum = 0;

    while (true) {
        printRoundInfo(_currRoundNum);
        printSymbolInfo();
        
        if (!(_iStream >> userSymbolNum)) {
            _oStream << "Please enter valid symbol number!\n\n";
            refreshConsoleInput();
              continue;
        }
        
        if (isSymbolNumberValid(userSymbolNum)) {
            return static_cast<Symbol>(userSymbolNum);	
        } else {
            _oStream << "Please enter valid symbol number!\n";
        }
    }
}

template<Rng::EngineC EngineT>
void RpsGame<EngineT>::playRound() {
    Symbol userSymbol = promptUserSymbolInput();
    
    Symbol computerSymbol = generateComputerSymbol();
    
    determineAndPronounceRoundWinner(userSymbol, computerSymbol);
}

template<Rng::EngineC EngineT>
void RpsGame<EngineT>::pronounceGameWinner() {
    _oStream << "\n------------------ "
             << "\nFINAL SCORE !"
             << "\n------------------ \n";
    
    if (_userScore > _pcScore)   { 
        _oStream  << "\n" 
                  << _PARTY_SYMBOL_UTF 
                  << _PARTY_SYMBOL_UTF 
                  << "  You WIN the game with a score " 
                  << static_cast<int32_t>(_userScore) 
                  << ":" 
                  << static_cast<int32_t>(_pcScore) 
                  << "\t"
                  << _PARTY_SYMBOL_UTF
                  << _PARTY_SYMBOL_UTF 
                  << "\n\n"; 
        
        return; 
    }
                                   
    if (_pcScore > _userScore) { 
        _oStream << "\nCOMPUTER WINS the game with a score " 
                 <<  static_cast<int32_t>(_pcScore)   
                 << ":" 
                 << static_cast<int32_t>(_userScore) 
                 << "\n\n"; 

        return; 
    }
    
    // Draw case
    _oStream << "\nGame ends in a DRAW with a score " 
             <<  static_cast<int32_t>(_pcScore)  
             << ":" 
             << static_cast<int32_t>(_userScore) 
             << "\n\n";
}

template<Rng::EngineC EngineT>
void RpsGame<EngineT>::startCompetition(size_t numRounds) {
    while (++_currRoundNum <= numRounds) {
        playRound();
        std::this_thread::sleep_for(_roundDelay);
    }
}

template<Rng::EngineC EngineT>
void RpsGame<EngineT>::run() {
    printWelcomeMsg();
    size_t numRounds = promptAndValidateNumberOfRoundsInput();
    startCompetition(numRounds);
    pronounceGameWinner();
}

} // namespace Game


