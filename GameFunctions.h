#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

static int points = 0;
const static int rows = 10;
const static int columns = 6;

template <typename TRow>
void printRow(const TRow& row){
        std::cout << "|";
                for(auto cell : row){
                        if(cell == true){
                                std::cout << "#";
                        } else{
                                std::cout << "_";
                        }
                        std::cout << "|";
                }
                std::cout << std::endl;
}

template <typename TBoard>
void printBoard(const TBoard& board){
        // |_|_|_|_|_|_|
        // |X|_|_|_|_|_|
        
        for(auto it = board.crbegin(); it != board.crend(); ++it){
                printRow(*it);
        }
        for(int i = 0; i < board[0].size(); ++i){
                std::cout << " " << i;
        }
        std::cout << std::endl;
}

template <typename TRow>
bool updateRow(TRow& row, 
                int blockPos, 
                int blockSize){        
        TRow newRow{row};

        for(int i = blockPos; i < blockPos + blockSize; ++i){
                if(newRow[i] == true){
                        return false;
                }
                newRow[i] = true;
        }
        row = newRow;
        return true;
}

template <typename TRow>
bool isRowFull(const TRow& row){
        for(auto cell : row){
                if(cell == false){
                        return false;
                }
        }
        return true;
}

template <typename TBoard>
bool updateBoard(TBoard& board, 
                int blockPos, 
                int blockSize){
        TBoard newBoard;

        bool updateSuccess = false;
        int extraRow = 0;
        while(!board.empty()){
                auto row = board.front();
                board.pop_front();
                if(!updateSuccess){
                        updateSuccess = updateRow(row, blockPos, blockSize);
                        if(!isRowFull(row)){
                                newBoard.push_back(row);
                        } 
                        if(isRowFull(row)){
                                extraRow++;
                        }
                } else{
                        newBoard.push_back(row);
                }
        }

        if(board.empty() && !updateSuccess){
                throw std::runtime_error("You lost the game!");
        }
        // +1 for successful placement.
        points++;
        if(extraRow > 0){
                // +5 for every cleared row.
                points += 5;
                newBoard.push_back(std::vector<bool>(columns, false));
        }

        board = newBoard;

        return updateSuccess;
}

int makeBlock(){
        // return a block between 1 and 3
        return rand() % 4 + 1;
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

bool checkIfPositionValid(int blockSize, int blockPos, int rowSize){
                
        if(blockPos < 0 || blockPos >= rowSize || 
           (blockPos + blockSize - 1) >= rowSize){
                return false;
        }
        return true;
}

std::deque<std::vector<bool>> makeBoard(int row, int col){
        std::deque<std::vector<bool>> board;
        for(int i = 0; i < row; ++i){
                board.push_back(std::vector<bool>(col, false));
        }
        return board;
}

#endif