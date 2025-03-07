//
// Created by Eric Chang on 2023/10/30.
//

#ifndef MANCALAGAME_MANCALAGAME_H
#define MANCALAGAME_MANCALAGAME_H


class MancalaGame {
public:

    MancalaGame() {
        gameStatus = CONTINUE;
        theFirstHand = 0;
        player = 0;
    };

    void startGame();

private:
    enum Player
    {
        PLAYER1,
        PLAYER2
    };

    enum GameStatus
    {
        OVER,
        CONTINUE,
        TUTORIAL
    };

    void gameTutorial();
    void initializeTheBoard();
    void displayMancalaBoard(int point = 0);
    void setTheFirstHand();
    void isEnding();
    void selectPit(int num = 1);
    void plantSeeds(int num);
    void takeSeeds(int num);
    void whoWins();

    int mancalaBoard[14] = {};
    int gameStatus;
    int theFirstHand;
    int player;
};


#endif //MANCALAGAME_MANCALAGAME_H
