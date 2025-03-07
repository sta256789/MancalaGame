//
// Created by Eric Chang on 2023/10/30.
//

#include "MancalaGame.h"
#include <iostream>
#include <string>
#define BASEBOARDSIZE 36
#define BASEHALFSPACESIZE 4
#define BASESPACESIZE 16
#define PLAYERSPOCKET 6
#define OPPOSITESPOCKET 13
using namespace std;

void MancalaGame::initializeTheBoard() {
    if (gameStatus == TUTORIAL) {
        player = PLAYER1;
        for (int & pit : mancalaBoard) {
            pit = 0;
        }
        mancalaBoard[13] = 17;
        mancalaBoard[6] = 21;
        mancalaBoard[5] = 1;
        mancalaBoard[12] = 2;
        mancalaBoard[10] = 3;
        mancalaBoard[9] = 4;
    }
    else {
        for (int i = 0; i < 14; i++) {
            if (i == PLAYERSPOCKET || i == OPPOSITESPOCKET) {
                mancalaBoard[i] = 0;
            } else {
                mancalaBoard[i] = 4;
            }
        }
    }
}

void MancalaGame::gameTutorial() {
    cout << "1. The game's object is to plant the most seeds in your own pocket.\n" << endl;
    displayMancalaBoard();

    cout << "2. If player1 selects the 6th pit, all seeds from the 6th pit will be removed and sow." << endl
        << "  (placing one in each of the following pits in sequence counterclockwise) \n" << endl;
    selectPit(6);
    displayMancalaBoard(6);

    cout << "3. Player2 selects the 3th." << endl;
    selectPit(3);
    displayMancalaBoard(3);

    cout << "4. If Player1 plants the last seed into an empty pit on his own side," << endl
        << "   player1 can take the seeds from the both sides.\n" << endl;
    selectPit(1);
    displayMancalaBoard(6);

    cout << "5. If Player2 selects the 5th pit, the last seed will be plant into his own pocket" << endl
        << "    and he can select a pit again!\n" << endl;
    selectPit(5);
    displayMancalaBoard(5);

    cout << "6. If the pits on either side are all empty, the other side can take the remaining seeds." << endl
        << "    And the game is over. (Player1 selects the sixth pit.)\n" << endl;
    initializeTheBoard();
    displayMancalaBoard(6);
    selectPit(6);

    cout << "7. The player who has more seeds on his own pocket is the winner!" << endl;
    whoWins();

    cout << "\nPress any key to start the game..." << endl;
    cin.get();
    gameStatus = CONTINUE;
}

void MancalaGame::startGame()
{
    initializeTheBoard();
    gameStatus = TUTORIAL;

    while (gameStatus == TUTORIAL) {
        gameTutorial();
    }

    initializeTheBoard();
    gameStatus = CONTINUE;

    setTheFirstHand();

    // Start the game loop
    while (gameStatus == CONTINUE) {
        displayMancalaBoard();
        selectPit();
        isEnding();
    }

    displayMancalaBoard();
    whoWins();
}

/*
 *  Array indices compare to the macala board
 *  Pit 　 ①　  ②　  ③　 ④　 ⑤　 ⑥
 *  ┌───────────────────────────────────────┐
 *  │　︻　【12】【11】【10】【9】【8】【7】　︻　│
 *  │　13      　　　　　　　　　　　　　　　　6　│
 *  │　︼　【 0】【 1】【 2】【3】【4】【5】　︼　│
 *  └───────────────────────────────────────┘
 */

void MancalaGame::displayMancalaBoard(int point)
{
    int boardSizeOffset = 0;
    int middleSpaceOffset;
    string mancalaBoardString[14];


    for (int i = 0; i < 14; ++i) {
        mancalaBoardString[i] = to_string(mancalaBoard[i]);
    }

    if (mancalaBoard[13] > 9 && mancalaBoard[6] < 10 || mancalaBoard[13] < 10 && mancalaBoard[6] > 9) {
        middleSpaceOffset = -1;
    }
    else if (mancalaBoard[13] > 9 && mancalaBoard[6] > 9) {
        middleSpaceOffset = -2;
    }
    else {
        middleSpaceOffset = 0;
    }

    for (int i = 0; i < 6; ++i) {
        // Increase the board size if either sides of the seeds greater than 9
        if (mancalaBoard[i] > 9 || mancalaBoard[12 - i] > 9) {
            ++boardSizeOffset;
        }

        // Add space to the other side if lower number of the seeds greater than the upper
        if (mancalaBoard[i] > 9 && mancalaBoard[12 - i] < 10) {
            mancalaBoardString[12 - i] = " " + mancalaBoardString[12 - i];
        }

        // Add space to the other side if upper number of the seeds greater than the lower
        if (mancalaBoard[i] < 10 && mancalaBoard[12 - i] > 9) {
            mancalaBoardString[i] = " " + mancalaBoardString[i];
        }
    }

    // Draw the board

    if (gameStatus == TUTORIAL) {
        cout << "　　　　　　　　　　　　　　　　Player1's pocket";
    }
    cout << endl;


    // First Row
    cout << "    ";
    for (int i = 0; i < 6; ++i) {
        cout << " 　";
        if (mancalaBoard[i] > 9 || mancalaBoard[12-i] > 9) {
            cout << " ";
        }
        if (i == 0) {
            cout << "①";
        }
        else if (i == 1) {
            cout << "②";
        }
        else if (i == 2) {
            cout << "③";
        }
        else if (i == 3) {
            cout << "④";
        }
        else if (i == 4) {
            cout << "⑤";
        }
        else if (i == 5) {
            cout << "⑥";
        }
    }
    if (gameStatus == TUTORIAL) {
        cout << " 　 ⬆";
    }
    cout << endl;


    // Second Row
    cout << "┌";
    for (int i = 0; i < BASEBOARDSIZE + boardSizeOffset; ++i) {
        cout << "─";
    }
    cout << "┐" << endl;


    // Third Row
    cout << "│　︹　";

    for (int i = 12; i > 6; i--)
        cout << "〖" << mancalaBoardString[i] << "〗";

    if (player == PLAYER2 && gameStatus == CONTINUE) {
        cout << "　︻　│ ← Select a pit!" << endl;
    }
    else if  (gameStatus == TUTORIAL) {
        cout << "　︻　│ ← Player2's pits!" << endl;
    }
    else {
        cout << "　︻　│" << endl;
    }


    // Forth Row
    cout << "│　" << mancalaBoard[13];

    // Print 4 half spaces because Six "4" - Two "0" = Four "half spaces" is needed to align the line.
    for (int i = 0; i < BASEHALFSPACESIZE + boardSizeOffset + middleSpaceOffset; ++i) {
        cout << " ";
    }

    for (int i = 0; i < BASESPACESIZE; ++i) {
        cout << "　";
    }
    cout << mancalaBoard[6] << + "　│" << endl;


    // Fifth Row
    cout << "│　︺　";

    for (int i = 0; i < 6; i++)
        cout << "【" << mancalaBoardString[i] << "】";

    if (player == PLAYER1 && gameStatus == CONTINUE) {
        cout << "　︼　│ ← Select a pit!" << endl;
    }
    else if  (gameStatus == TUTORIAL) {
        cout << "　︼　│ ← Player1's pits!" << endl;
    }
    else {
        cout << "　︼　│" << endl;
    }


    // Sixth Row
    cout << "└";
    for (int i = 0; i < BASEBOARDSIZE + boardSizeOffset; ++i) {
        cout << "─";
    }
    cout << "┘" << endl;

    if (gameStatus == TUTORIAL) {
        cout << "　 ⬇　";
        if (point > 0) {
            point -= 1;
            for (int i = 0; i < point; ++i) {
                cout << "　　 ";
            }
            cout << " ⬆";
        }
        cout << endl;
        cout << "Player2's pocket" << endl;
        cout << "\nPress any key to continue..." << endl;
        cin.get();
    }
}

void MancalaGame::setTheFirstHand() {
    cout << "\nEnter 0 or 1 to set the first hand to Player1 / Player2." << endl;
    cout << "Ans: ";
    cin >> theFirstHand;

    // Set the first hand to player2 if number is neither 0 and 1.
    if (theFirstHand) {
        player = PLAYER2;
    }
    else {
        player = PLAYER1;
    }
    cout << "Player" << player + 1 << " is first!" << endl;

}

void MancalaGame::isEnding()
{
    if (gameStatus != TUTORIAL) {
        // Either sides of pits are all empty
        if (mancalaBoard[0] == 0 && mancalaBoard[1] == 0 && mancalaBoard[2] == 0 &&
            mancalaBoard[3] == 0 && mancalaBoard[4] == 0 && mancalaBoard[5] == 0 ||
            mancalaBoard[7] == 0 && mancalaBoard[8] == 0 && mancalaBoard[9] == 0 &&
            mancalaBoard[10] == 0 && mancalaBoard[11] == 0 && mancalaBoard[12] == 0) {
            gameStatus = OVER;
        }
        else {
            gameStatus = CONTINUE;
        }
    }
}

void MancalaGame::selectPit(int num) {

    if (gameStatus == CONTINUE) {
        cin >> num;
    }

    // bottom
    if (player == PLAYER1) {
        // To match the array index of the bottom
        num -= 1;

        if (num >= 0 && num < 6 && mancalaBoard[num] != 0) {
            plantSeeds(num);
        }
        else {
            cout << "Invalid Pit!" << endl;
        }
    }
    // top
    else {
        // To match the array index of the top
        num = 13 - num;

        if (num > 6 && num < 13 && mancalaBoard[num] != 0) {
            plantSeeds(num);
        }
        else {
            cout << "Invalid Pit!" << endl;
        }
    }
}

void MancalaGame::plantSeeds(int num) {
    int seeds = mancalaBoard[num];

    mancalaBoard[num] = 0;

    // Plant the seeds
    for (int i = 1; i <= seeds; i++) {
        // Pass the opposite pocket(mancalaBoard[6]), when the player is PLAYER2
        if (player == PLAYER2 && num + 1 == 6) {
            num += 2;
        }
        // Pass the opposite pocket(mancalaBoard[13]), when the player is PLAYER1
        else if (player == PLAYER1 && num + 1 == 13 || num + 1 > 13) {
            num = 0;
        }
        else {
            num += 1;
        }
        mancalaBoard[num] += 1;
    }

    takeSeeds(num);

    // Check if the last seed is planted into the player's own pocket, or switch the player
    if (player == PLAYER1 && num == 6 || player == PLAYER2 && num == 13) {
        isEnding();
        // Plant the seeds again if the last seed is be planted into your own pocket
        if (gameStatus == CONTINUE) {
            cout << "You can plant the seeds again!" << endl;
        }
    }
    else {
        player = !player;
    }
}

void MancalaGame::takeSeeds(int num)
{
    // For player1, test the final seed whether be planted into an empty pit of the bottom
    // and the opposite pit isn't empty
    if (player == PLAYER1 && num >= 0 && num < 6 && mancalaBoard[num] == 1 && mancalaBoard[12 - num] != 0) {
        // Add the seeds of the both sides to the player1's pocket and empty the both pits
        mancalaBoard[6] += mancalaBoard[12 - num] + mancalaBoard[num];
        mancalaBoard[num] = 0;
        mancalaBoard[12 - num] = 0;
        cout << "Player1 takes the seeds from the pit " << num + 1 << "!" << endl;
    }
    else if (player == PLAYER2 && num >= 7 && num < 13 && mancalaBoard[num] == 1 && mancalaBoard[12 - num] != 0) {
        mancalaBoard[13] += mancalaBoard[12 - num] + mancalaBoard[num];
        mancalaBoard[num] = 0;
        mancalaBoard[12 - num] = 0;
        cout << "Player2 takes the seeds from the pit " << 13 - num << "!" << endl;
    }
    isEnding();
}

void MancalaGame::whoWins()
{
    // Take the remaining seeds if the pits of either side are all empty
    cout << endl << "Take the remaining seeds!" << endl;
    for (int i = 0; i < 6; i++) {
        mancalaBoard[6] += mancalaBoard[i];
        mancalaBoard[i] = 0;
        mancalaBoard[13] += mancalaBoard[12 - i];
        mancalaBoard[12 - i] = 0;
    }

    displayMancalaBoard();

    // Show the result
    cout << endl << "Player1【" << mancalaBoard[6] << "】: Player2【" << mancalaBoard[13] << "】" << endl;
    if (mancalaBoard[6] > mancalaBoard[13]) {
        cout << "PLAYER1 IS WIN!!" << endl;
    }
    else if (mancalaBoard[6] < mancalaBoard[13]) {
        cout << "PLAYER2 IS WIN!!" << endl;
    }
    else {
        cout << "DRAW!" << endl;
    }

}

/*
 * 0
 * 5561122316
 * 2441613415
 * 1221366314
 * 456
 */

