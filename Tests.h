#include <iostream>

#include "GameFunctions.h"

/*
* Check if we can make a board correctly.
*/
void TestMakeBoard(){
        auto board0 = makeBoard(10, 5);
        if(board0.size() != 10 || board0[0].size() != 5){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }
}

void TestCheckIfPositionValid(){
        // fits nicely
        if(!checkIfPositionValid(3, 0, 5)){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }
        // blocksize same as row size and placement
        if(!checkIfPositionValid(3, 0, 3)){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }
        // block position is outside of the bounds
        if(checkIfPositionValid(3, -1, 3)){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }
        // end of the placed block is out of bounds
        if(checkIfPositionValid(4, 0, 3)){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }
}

void TestUpdateRow(){
        std::vector<bool> row(5, false);
        bool updateSuccess = updateRow(row, 0, 3);

        if(!updateSuccess){
                std::cerr << __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ <<  std::endl;
        }

        updateSuccess = updateRow(row, 0, 3);

        if(updateSuccess){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }

        int freeCells = 0;
        for(auto cell : row){
                if(cell == false){
                        freeCells++;
                }
        }
        
        if(freeCells != 2){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }

}

/**
* Given a single row board check if we can update it correctly.
*/
void TestUpdateSingleRowBoard(){
        auto board = makeBoard(1, 5);
        bool updateSuccess = updateBoard(board, 0, 3);
        if(!updateSuccess){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }
}

void TestIsRowFull(){
        std::vector<bool> rowF(5, false);
        if(isRowFull(rowF)){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }

        rowF[2] = true;
        if(isRowFull(rowF)){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }

        std::vector<bool> rowT(5, true);
        if(!isRowFull(rowT)){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }

}

void TestUpdateFullBoard(){
        auto board = makeBoard(10, 5);
        bool updateSuccess = updateBoard(board, 0, 3);
        if(!updateSuccess){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }
        std::cout << "After first update to the same column: " << std::endl;
        printBoard(board);
        
        updateSuccess = updateBoard(board, 0, 3);
        if(!updateSuccess){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }
        std::cout << "After second update: " << std::endl;
        printBoard(board);

        // complete the first row.
        updateSuccess = updateBoard(board, 3, 2);
        if(!updateSuccess){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }
        if(board.size() != 10){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }
        std::cout << "After third update: " << std::endl;
        printBoard(board);

        // complete the first row again
        updateSuccess = updateBoard(board, 3, 2);
        if(!updateSuccess){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }
        if(board.size() != 10){
                std::cerr <<  __func__ <<  " failed. Line: " << __LINE__ << " " << __FILE__ << std::endl;
        }
        std::cout << "After fourth update: " << std::endl;
        printBoard(board);
}

void TestGameLost(){
        auto board = makeBoard(2, 5);        
        try{
                updateBoard(board, 0, 3);
                updateBoard(board, 0, 3);
                updateBoard(board, 0, 3);
        } catch(std::runtime_error& e){
                std::cerr << e.what() << " Test passed." << std::endl;
        }
}

void RunTests(){
        TestMakeBoard();
        TestCheckIfPositionValid();
        TestIsRowFull();
        TestUpdateRow();
        TestUpdateSingleRowBoard();
        TestUpdateFullBoard();
        TestGameLost();

        std::cout << "End of tests." << std::endl;
}