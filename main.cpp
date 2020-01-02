// Tetris NO LAG
#include <iostream>
#include <vector>
#include <deque>

#include "Tests.h"
#include "GameFunctions.h"
#define RUNTESTS false

int main(int argc, char* argv[]){
        auto board = makeBoard(rows, columns);

        if(RUNTESTS){
                RunTests();
        } else{
                printGameRules();
                bool updateSuccess = true;
                bool validPos = true;
                int newBlock = 0;
                while(true){
                        std::cout << "Points: " << points << std::endl;
                        // make random block
                        if(updateSuccess && validPos){
                                newBlock = makeBlock();
                        }

                        // ask where to put it
                        printBoard(board);

                        std::string newBlockStr(newBlock, '#');
                        std::cout << "New block: " << newBlockStr << std::endl;

                        std::cout << "Where do you want to place the block?" << std::endl;
                        int newPos = 0;
                        std::cin >> newPos;

                        validPos = checkIfPositionValid(newBlock, newPos, columns);
                        if(!validPos){
                                points--;
                                std::cerr << "You cannot place the block here." << std::endl;
                                continue;
                        }

                        // try to place the block 
                        try{
                                updateSuccess = updateBoard(board, newPos, newBlock);
                        } catch(std::runtime_error& e){
                                std::cerr << e.what() << std::endl;
                                return EXIT_SUCCESS;
                        }
                }
        }

        return EXIT_SUCCESS;
}
