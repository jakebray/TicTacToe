/**
 * File: Tic Tac Toe.cpp
 *
 * @author Jake Bray
 *
 * Last Edited: 5/8/13
 * Description: A human user plays a game of Tic Tac Toe against an Unbeatable
 *              A.I.
 */

#include <iostream>
#include <limits>
#include <stdlib.h>

// Function Declarations
void initBoard(char[9]);
void printBoard(char[9]);
void printInputBoard(char[9]);
void play(char[9]);
void playHuman(char[9]);
void playComp(char[9]);
bool isValidInput(char[9], int input);
int bestMove(char[9]);
int computerBest(char[9]);
int humanBest(char[9]);
int getState(char[9]);


int main()
{
    char board[9];

    std::cout << "Tic Tac Toe" << std::endl;

    initBoard(board);

    do
    {
        play(board);

    }while(getState(board) == 2);

    if(getState(board) == 0)
        std::cout << "It's a Draw!" << std::endl;
    else if(getState(board) == 1)
        std::cout << "You win!" << std::endl;
    else
        std::cout << "I win!" << std::endl;

    printBoard(board);

    return 0;
}

/**
 * Initializes the board with ' 's in each square
 * @param board to be initialized
 */
void initBoard(char board[9])
{
    for(int i = 0; i < 9; i++)
    {
        board[i] = ' ';
    }
}

/**
 * Prints the board
 * @param board to be printed
 */
void printBoard(char board[9])
{
    for(int i = 0; i < 9; i++)
    {
        std::cout << board[i];
        if(i % 3 != 2)
            std::cout << " | ";
        if(i % 3 == 2)
        {
            std::cout << std::endl;
            if(i != 8)
                std::cout << "- + - + -" << std:: endl;
        }
    }
}

/**
 * Prints the board with available inputs
 * @param board to be printed
 */
void printInputBoard(char board[9])
{
    std::cout << "Possible Inputs:" << std::endl;

    for(int i = 0; i < 9; i++)
    {
        if(board[i] == ' ')
            std::cout << i;
        else
            std::cout << ' ';
        if(i % 3 != 2)
            std::cout << " | ";
        if(i % 3 == 2)
        {
            std::cout << std::endl;
            if(i != 8)
                std::cout << "- + - + -" << std:: endl;
        }
    }
}

/**
 * Plays the next turn
 * @param board to be used
 */
void play(char board[9])
{
    std::cout << std::endl;
    playHuman(board);
    if(getState(board) != 0)
        playComp(board);
}

/**
 * Plays the next human turn
 * @param board to be used
 */
void playHuman(char board[9])
{
    int input;
    std::string inStr;

    std::cout << "Your Turn" << std::endl;
    printInputBoard(board);

    std::cout << "Where do you want to place your mark? [0-8]" << std::endl;

    do
    {
        std::cout << ">";
        std::getline(std::cin, inStr);
        input = atoi(inStr.c_str());
        if(!isValidInput(board, input))
            std::cout << "Please enter a valid location." << std::endl;
    }while(!isValidInput(board, input));

    board[input] = 'x';

    std::cout << std::endl;
}

/**
 * Plays the next computer turn
 * @param board to be used
 */
void playComp(char board[9])
{
    std::cout << "My Turn" << std::endl;
    int move = bestMove(board);
    std::cout << "I will take space " << move << std::endl;
    board[move] = 'o';
    printBoard(board);
    std::cout << std::endl;
}

/**
 * Checks if input is valid for current board
 * @param board to be printed
 * @param input to check
 * @return whether or not input is valid
 */
bool isValidInput(char board[9], int input)
{
    return((input < 9 && input >= 0) && (board[input] == ' '));
}

/**
 * Finds best move available
 * @param board with available move
 * @return best move available
 */
int bestMove(char board[9])
{
    int best = std::numeric_limits<int>::max();
    int move = 0;
    for(int i = 0; i < 9; i++)
    {
        if(board[i] == ' ')
        {
            board[i] = 'o';
            int val = humanBest(board);
            if(val < best)
            {
                best = val;
                move = i;
            }
            board[i] = ' ';
        }
    }
    return move;
}

/**
 * Finds the move with the best outcome for the computer
 * @param board to be analyzed
 * @return best outcome value
 */
int computerBest(char board[9])
{
    int state = getState(board);
    int best = std::numeric_limits<int>::max();
    if(state == 2)
    {
        for(int i = 0; i < 9; i++)
        {
            if(board[i] == ' ')
            {
                board[i] = 'o';
                int val = humanBest(board);
                if(val < best)
                    best = val;
                board[i] = ' ';
            }
        }
    }
    else
        best = state;

    return best;
}

/**
 * Finds the move with the best outcome for the human
 * @param board to be analyzed
 * @return best outcome value
 */
int humanBest(char board[9])
{
    int state = getState(board);
    int best = std::numeric_limits<int>::min();
    if(state == 2)
    {
        for(int i = 0; i < 9; i++)
        {
            if(board[i] == ' ')
            {
                board[i] = 'x';
                int val = computerBest(board);
                if(val > best)
                    best = val;
                board[i] = ' ';
            }
        }
    }
    else
        best = state;

    return best;
}

/**
 * Gets the state of the board (2:default, 1:x win, 0:draw, -1:o win)
 * @param board to be analyzed
 * @return integer representation of board state
 */
int getState(char board[9])
{
    int state = 2;
    if(
       (board[0] == 'x' && board[1] == 'x' && board[2] == 'x') ||
       (board[3] == 'x' && board[4] == 'x' && board[5] == 'x') ||
       (board[6] == 'x' && board[7] == 'x' && board[8] == 'x') ||
       (board[0] == 'x' && board[3] == 'x' && board[6] == 'x') ||
       (board[1] == 'x' && board[4] == 'x' && board[7] == 'x') ||
       (board[2] == 'x' && board[5] == 'x' && board[8] == 'x') ||
       (board[0] == 'x' && board[4] == 'x' && board[8] == 'x') ||
       (board[2] == 'x' && board[4] == 'x' && board[6] == 'x')
      )
       state = 1;
    else if
      (
       (board[0] == 'o' && board[1] == 'o' && board[2] == 'o') ||
       (board[3] == 'o' && board[4] == 'o' && board[5] == 'o') ||
       (board[6] == 'o' && board[7] == 'o' && board[8] == 'o') ||
       (board[0] == 'o' && board[3] == 'o' && board[6] == 'o') ||
       (board[1] == 'o' && board[4] == 'o' && board[7] == 'o') ||
       (board[2] == 'o' && board[5] == 'o' && board[8] == 'o') ||
       (board[0] == 'o' && board[4] == 'o' && board[8] == 'o') ||
       (board[2] == 'o' && board[4] == 'o' && board[6] == 'o')
      )
       state = -1;
    else if
      (
        board[0] != ' ' && board[1] != ' ' && board[2] != ' ' &&
        board[3] != ' ' && board[4] != ' ' && board[5] != ' ' &&
        board[6] != ' ' && board[7] != ' ' && board[8] != ' '
      )
       state = 0;

    return state;
}
