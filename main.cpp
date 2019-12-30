// Tetris ~TEST~
#include <iostream>
#include <vector>

/*
- check if occupied when updating
- read the input, store values, etc.
- ask where you want to put the block (cin)
- generate random block sizes (rand blockSize)
- check if we won or lost (cout)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
If wanted to make 2D (Normal tetris):
- have the blocks come down (moveBlockPos)
- show babidik a version of "Collapsed!! (Mode 4(A Mode))"
*/
#define _GAME_
  void printBoard(const std::vector<bool>& board){
        // |_|_|_|_|_|_|
        // |X|_|_|_|_|_|

        std::cout << "|";
        for(auto cell : board){
                if(cell == true){
                        std::cout << "#";
                } else{
                        std::cout << "_";
                }
                std::cout << "|";
        }
        std::cout << std::endl;
}

bool updateBoard(std::vector<bool>& board, 
                int blockPos, 
                int blockSize){
        if(blockPos < 0 || 
           blockPos >= board.size() || 
           (blockPos + blockSize - 1) >= board.size()){
                // throw std::invalid_argument("You cannot place the block here.");
                // std::cerr << "You cannot place this block here." << std::endl;
                return false;
        }
        
        auto newBoard{board};

        for(int i = blockPos; i < blockPos + blockSize; ++i){
                // TODO: check if occupied
                if(newBoard[i] == true){
                        // std::cerr << "You cannot place this block here." << std::endl;
                        return false;
                }
                newBoard[i] = true;
        }
        board = newBoard;
        return true;
}

int makeBlock(){
        // return a block between 1 and 3
        return std::rand() % 3 + 1;
}

bool didWeWin(const std::vector<bool>& board){
        for(auto cell : board){
                if(cell == false){
                        return false;
                }
        }
        return true;
}

bool askKeepPlaying(){
        // ask if the player wants keep Playing
        std::cout << "Keep Playing? (Y/N)" << std::endl;
        std::string keepPlayingText = "Y";
        std::cin >> keepPlayingText;
        if(keepPlayingText == "Y" || keepPlayingText == "y"){
                return true;
        } else if(keepPlayingText == "N" || keepPlayingText == "n"){
                return false;
        } else{
                std::cout << "I don't know that option. I guess that is a no? :)" << std::endl;
                return false;       
        }
}

int main(int argc, char* argv[]){
        std::vector<bool> board(10, false);
        
        bool keepPlaying = true;
        while(keepPlaying){
                // make random block
                int newBlock = makeBlock();

                // ask where to put it
                printBoard(board);

                std::cout << "New block size: " << newBlock << std::endl;

                std::cout << "Where do you want to place the new block? \n Type index [0,9]" << std::endl;
                int newPos = 0;
                std::cin >> newPos;

                // try to place the block 
                int placementSuccess = updateBoard(board, newPos, newBlock);

                // if it doesn't work print a message
                if(!placementSuccess){
                        std::cerr << "You cannot place this block here." << std::endl;
                }

                // check if we won
                if(didWeWin(board)){
                        std::cout << "YOU WON!" << std::endl;
                        return EXIT_SUCCESS;
                }

                // printBoard(board);

                keepPlaying = true;// askKeepPlaying();
        }

        return EXIT_SUCCESS;
}
