Mancala
===

## Introduction 

This is a text version of Mancala which written with C++.

## Usage
Implement a MancalaGame instance and use function startGame() to start the game.  

    MancalaGame mancalaGame;     
    mancalaGame.startGame();

## General Gameplay
Most mancala games have a common gameplay. Players begin by placing a certain number of seeds, prescribed for the particular game, in each of the pits on the game board. A player may count their stones to plot the game. A turn consists of removing all seeds from a pit, "sowing" the seeds (placing one in each of the following pits in sequence), and capturing based on the state of the board. The game's object is to plant the most seeds in the bank. This leads to the English phrase "count and capture" sometimes used to describe the gameplay. Although the details differ greatly, this general sequence applies to all games.

If playing in capture mode, once a player ends their turn in an empty pit on their own side, they capture the opponent's pieces directly across. Once captured, the player gets to put the seeds in their own bank. After capturing, the opponent forfeits a turn.  

## Text Version Gameplay  
1. After the tutorial, enter 0 or 1 to the first hand to Player1 / Player2.  
2. Enter num 1~6 to take the seeds to sow.  
3. The right side of the board will hint that this is who's turn.  
4. When the pits of either side are all empty, the program will end the game and show who is the winner.  

## Screenshot
![MancalaPicture](https://github.com/sta256789/MancalaGame/blob/main/IMG_1501.jpeg?raw=true)  
Some information of this game.

## Demo
[Demo video from Youtube](https://youtu.be/gZNQ8c4Se9I "Demo")

## Reference
[Mancala Wiki](https://en.wikipedia.org/wiki/Mancala "Mancala")