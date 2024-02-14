# Rock_paper_scissors console game made by Ivan Radmilo.

---
# Navigation

- [Info](#info)
- [Game rules](#game-rules)
- [Build project](#how-to-build)
- [Run project](#how-to-run)
- [Testing](#Testing)
---

## Info

This is a game of [Rock, Paper, Scissors](https://en.wikipedia.org/wiki/Rock_paper_scissors) between a player and the computer.

## Game rules

At the start of the game, player enters the number of rounds game is played for.

Players simultaneously open their hands to display a symbol:
>* Fist equals rock
>* Open hand equals paper
>* Crossing index and middle finger equals scissors.

Round winner is determined by the following schema:
>* paper beats (wraps) rock
>* rock beats (blunts) scissors
>* scissors beats (cuts) paper.

<br>

***Winner is pronounced when the entered number of rounds are played.***
	
## How to BUILD
Position yourself in project's **root** directory (same directory README is located in).
>BUILD: ***'make'*** command.

## How to RUN
To be able to run the game you have to [build](#how-to-build) it first.
After the code is built,
> RUN ***'make run'***

>CLEAN: ***'make clean'***.

## Testing
Gtest (gmock) framework is used for unittesting.<br><br>
To run unittest position yourself in **test** directory (root/test).
>BUILD: ***'make'*** command. 

>RUN: ***'make run'*** to run the tests after ***'make'*** command successfully builds unittest 

>CLEAN: ***'make clean'***.