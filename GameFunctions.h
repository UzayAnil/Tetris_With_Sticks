#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

static int points = 0;
const static int rows = 10;
const static int columns = 6;
const static int cols = columns;

void printGameRules(){
        std::cout << "Game Play:\n" <<
        "In each turn, you are given a block of varying length.\n" <<
        "Type in the position to place the block on the board.\n" << 
        "The block will be placed in the first available row from the bottom at the given position.\n" <<
        "If the placement is outside of the board, you will be given the same block again.\n" <<
        "Earning (or losing :)) points:\n" <<
        "Successful block placement: +1\n" <<
        "Unsuccessful block placement: -1\n" <<
        "Clearing a row: +5\n" <<
        "Winning and Losing: \n" <<
        "If the blocks reach the top, you lose!\n" <<
        "There is no Winning, so play until you lose.\n" <<
        "Comment your highscore in the comment section below!\n" <<
        "----------------------------" << std::endl;
}

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

        const int rowSize = board.size();
        const int colSize = board[0].size();

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
                newBoard.push_back(std::vector<bool>(colSize, false));
        }

        board = newBoard;

        return updateSuccess;
}

int makeBlock(){
        // return a block between 1 and 4
        return rand() % 5 + 1;
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