// Tetris ~TEST~
#include <iostream>
#include <vector>
#include <queue>
#include <deque>

#include "Tests.h"
#include "GameFunctions.h"

/** 
* If set to true, it will run tests instead of the game.
* I used this during development.
*/ 
#define RUNTESTS false

/**
* Gaining points:
* +1 every time you place a block successfully.
* +5 every time you complate and clear a row.
* -1 everytime you try to incorrectly place a block.
*/

int main(int argc, char* argv[]){
        auto board = makeBoard(rows, columns);

        if(RUNTESTS){
                RunTests();
        } else{
                bool keepPlaying = true;
                while(keepPlaying){
                        std::cout << "Points: " << points << std::endl;
                        // make random block
                        int newBlock = makeBlock();

                        // ask where to put it
                        printBoard(board);

                        std::string newBlockStr(newBlock, '#');
                        std::cout << "New block: " << newBlockStr << std::endl;

                        std::cout << "Where do you want to place the block?" << std::endl;
                        int newPos = 0;
                        std::cin >> newPos;

                        bool validPos = checkIfPositionValid(newBlock, newPos, columns);
                        if(!validPos){
                                points--;
                                std::cerr << "You cannot place the block here." << std::endl;
                                continue;
                        }

                        // try to place the block 
                        bool placementSuccess = false;
                        try{
                                placementSuccess = updateBoard(board, newPos, newBlock);
                        } catch(std::runtime_error& e){
                                std::cerr << e.what() << std::endl;
                                return EXIT_SUCCESS;
                        }

                        keepPlaying = true;
                }
        }

        return EXIT_SUCCESS;
}
