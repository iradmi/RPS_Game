/// (c) Copyright:
/// This file is part of Rock-Paper-Scissors project.
/// This is a free software: you can redistribute it and/or modify it under 
/// the terms of the GNU General Public License as published by Free Software Foundation, 
/// either version 3 of the License, or (at your option) any later version.

#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include <memory>
#include <iostream>
#include <string_view>

#include "RpsGame.h"
#include "../src/RpsGame.cpp"

using namespace testing;

namespace GameTest {

class RngEngineMock : public Rng::IRandomNumberGenerator {
 public:
  MOCK_METHOD(int64_t, generateRandomNumber, (int64_t upperBound, int64_t lowerBound), (override));
};

class RockPapersScissorsGameFixtureTest : public Test {
 protected:
    virtual void SetUp() {
        _rngMock = std::make_shared<RngEngineMock>();
        _game = std::make_unique<Game::RpsGame>(_rngMock, std::chrono::milliseconds(0), _input, _output);
    }
    
    virtual void TearDown() {}

    static constexpr std::string_view computerWinsRoundTxt = "Computer WINS this round!";
    static constexpr std::string_view userWinsRoundTxt     = "You WIN this round!";
    static constexpr std::string_view drawRoundTxt         = "Round ends in a DRAW!";

    std::unique_ptr<Game::IGame>   _game;
    std::shared_ptr<RngEngineMock> _rngMock;
    std::istringstream             _input;
    std::ostringstream             _output;
};

TEST_F(RockPapersScissorsGameFixtureTest, GameRun_FinalGameOutcome_UserWins) {
    // setup
    _input.str("2 2 2");		 
    
    EXPECT_CALL(*_rngMock, generateRandomNumber(1, 3))
        .Times(2)
        .WillOnce(Return(1))
        .WillOnce(Return(2));
    // execute												 
    _game->run();
    
    // assert
    EXPECT_THAT(_output.str(), HasSubstr("You WIN the game with a score 1:0"));
}

TEST_F(RockPapersScissorsGameFixtureTest, GameRun_FinalGameOutcome_ComputerWins) {												 
    _input.str("1 3"); // round scissors		
    
    EXPECT_CALL(*_rngMock, generateRandomNumber(1, 3))
        .Times(1)
        .WillOnce(Return(1));
    // execute
    _game->run(); 

 
    // assert
    EXPECT_THAT(_output.str(), HasSubstr("COMPUTER WINS the game with a score 1:0"));

}

TEST_F(RockPapersScissorsGameFixtureTest, GameRun_FinalGameOutcome_MatchDraw) {												 
    _input.str("101 1 5 3"); // round(invalid) round symbol(invalid) symbol(scissors)

    EXPECT_CALL(*_rngMock, generateRandomNumber(1, 3))
        .Times(1)
        .WillOnce(Return(3));
    // execute
    _game->run();

    // assert
    EXPECT_THAT(_output.str(), HasSubstr("Please enter valid symbol number!"));
    EXPECT_THAT(_output.str(), HasSubstr("Please enter valid number of rounds!"));
    EXPECT_THAT(_output.str(), HasSubstr("Game ends in a DRAW with a score 0:0"));
}

TEST_F(RockPapersScissorsGameFixtureTest, GameRun_RoundOutcome_RockBeatsScissors_UserWin) {
    int Rock = 1;
    int Scissors = 3;
    // setup
    _input.str("1 1"); // rounds symbol

    EXPECT_CALL(*_rngMock, generateRandomNumber(Rock, Scissors))
        .Times(1)
        .WillOnce(Return(Scissors));

    // execute
    _game->run();

    // assert
    EXPECT_THAT(_output.str(), HasSubstr(userWinsRoundTxt));
}

TEST_F(RockPapersScissorsGameFixtureTest, GameRun_RoundOutcome_PaperBeatsRock_UserWin) {
    int Rock = 1;
    //int Paper = 2;
    int Scissors = 3;
    // setup
    _input.str("1 2"); // rounds symbol

    EXPECT_CALL(*_rngMock, generateRandomNumber(Rock, Scissors))
        .Times(1)
        .WillOnce(Return(Rock));

    // execute
    _game->run();

    // assert
    EXPECT_THAT(_output.str(), HasSubstr(userWinsRoundTxt));
}

TEST_F(RockPapersScissorsGameFixtureTest, GameRun_RoundOutcome_ScissorsBeatPaper_UserWin) {
    int Rock = 1;
    int Paper = 2;
    int Scissors = 3;
    // setup
    _input.str("1 3");  // rounds symbol

    EXPECT_CALL(*_rngMock, generateRandomNumber(Rock, Scissors))
        .Times(1)
        .WillOnce(Return(Paper));

    // execute
    _game->run();

    // assert
    EXPECT_THAT(_output.str(), HasSubstr(userWinsRoundTxt));
}

TEST_F(RockPapersScissorsGameFixtureTest, GameRun_RoundOutcome_RockBeatsScissors_PCWins) {
    int Rock = 1;
    int Scissors = 3;
    // setup
    _input.str("1 3"); // rounds symbol

    EXPECT_CALL(*_rngMock, generateRandomNumber(Rock, Scissors))
        .Times(1)
        .WillOnce(Return(Rock));

    // execute
    _game->run();

    // assert
    EXPECT_THAT(_output.str(), HasSubstr(computerWinsRoundTxt));
}

TEST_F(RockPapersScissorsGameFixtureTest, GameRun_RoundOutcome_PaperBeatsRock_PCWins) {
    int Rock = 1;
    int Paper = 2;
    int Scissors = 3;
    // setup
    _input.str("1 1"); // rounds symbol

    EXPECT_CALL(*_rngMock, generateRandomNumber(Rock, Scissors))
        .Times(1)
        .WillOnce(Return(Paper));

    // execute
    _game->run();

    // assert
    EXPECT_THAT(_output.str(), HasSubstr(computerWinsRoundTxt));
}

TEST_F(RockPapersScissorsGameFixtureTest, GameRun_RoundOutcome_ScissorsBeatPaper_PCWins) {
    int Rock = 1;
    //int Paper = 2;
    int Scissors = 3;

    // setup
    _input.str("1 2");

    EXPECT_CALL(*_rngMock, generateRandomNumber(Rock, Scissors))
        .Times(1)
        .WillOnce(Return(Scissors));

    // execute
    _game->run();

    // assert
    EXPECT_THAT(_output.str(), HasSubstr(computerWinsRoundTxt));
}

TEST_F(RockPapersScissorsGameFixtureTest, GameRun_RoundOutcome_RockAll_Draw) {
    int Rock = 1;
    //int Paper = 2;
    int Scissors = 3;

    // setup
    _input.str("1 1");  // rounds symbol

    EXPECT_CALL(*_rngMock, generateRandomNumber(Rock, Scissors))
        .Times(1)
        .WillOnce(Return(Rock));

    // execute
    _game->run();

    // assert
    EXPECT_THAT(_output.str(), HasSubstr(drawRoundTxt));
}


TEST_F(RockPapersScissorsGameFixtureTest, GameRun_RoundOutcome_PaperAll_Draw) {
    int Rock = 1;
    int Paper = 2;
    int Scissors = 3;

    // setup
    _input.str("1 2");  // rounds symbol

    EXPECT_CALL(*_rngMock, generateRandomNumber(Rock, Scissors))
        .Times(1)
        .WillOnce(Return(Paper));

    // execute
    _game->run();

    // assert
    EXPECT_THAT(_output.str(), HasSubstr(drawRoundTxt));
}

TEST_F(RockPapersScissorsGameFixtureTest, GameRun_RoundOutcome_ScissorsAll_Draw) {
    int Rock = 1;
    //int Paper = 2;
    int Scissors = 3;

    // setup
    _input.str("1 3");  // rounds symbol

    EXPECT_CALL(*_rngMock, generateRandomNumber(Rock, Scissors))
        .Times(1)
        .WillOnce(Return(Scissors));

    // execute
    _game->run();

    // assert
    EXPECT_THAT(_output.str(), HasSubstr(drawRoundTxt));
}

TEST_F(RockPapersScissorsGameFixtureTest, GameRun_NumberOfRoundsPlayed) {
    int Rock = 1;
    int Scissors = 3;

    // setup
    _input.str("2 1 1"); // rounds symbol

    EXPECT_CALL(*_rngMock, generateRandomNumber(Rock, Scissors))
        .Times(2)
        .WillOnce(Return(Scissors))
        .WillOnce(Return(Scissors));

    // execute
    _game->run();

    // assert
    EXPECT_THAT(_output.str(), HasSubstr("ROUND NUMBER 1!"));
    EXPECT_THAT(_output.str(), HasSubstr("ROUND NUMBER 2!"));
    EXPECT_THAT(_output.str(), Not(HasSubstr("ROUND NUMBER 3!")));
}

} // namespace GameTest
