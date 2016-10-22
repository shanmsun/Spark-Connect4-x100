
#include "constants.h"
#include "connect_4_check_win.h"

int checkBoard(int currentPlayer){
  int winner = NO_COLOUR;
  for(int row = 0; row < ROWS; row++){
    winner = checkRow(currentPlayer, row);
    if (winner != NO_COLOUR){
      return winner;
    }
  }
  for(int col = 0; col < COLUMNS; col++){
    winner = checkColumn(currentPlayer, col);
    if (winner != NO_COLOUR){
      return winner;
    }
  }
  int diagonal[12];
  diagonal[1] = checkDiagonalLeftUp(currentPlayer, 2,0);
  diagonal[2] = checkDiagonalLeftUp(currentPlayer, 1,0);
  diagonal[3] = checkDiagonalLeftUp(currentPlayer, 0,0);
  diagonal[4] = checkDiagonalLeftUp(currentPlayer, 0,1);
  diagonal[5] = checkDiagonalLeftUp(currentPlayer, 0,2);
  diagonal[6] = checkDiagonalLeftUp(currentPlayer, 0,3);
  diagonal[7] = checkDiagonalRightUp(currentPlayer, 0,3);
  diagonal[8] = checkDiagonalRightUp(currentPlayer, 0,4);
  diagonal[9] = checkDiagonalRightUp(currentPlayer, 0,5);
  diagonal[10] = checkDiagonalRightUp(currentPlayer, 0,6);
  diagonal[11] = checkDiagonalRightUp(currentPlayer, 1,6);
  diagonal[0] = checkDiagonalRightUp(currentPlayer, 2,6);
  for(int i = 0; i < 12; i++){
    if (diagonal[i] != NO_COLOUR){
      return winner;
    }
  }
  return winner;
}
int checkRow(int currentPlayer, int row){
  int check = 0;
  for(int col = 0; col < COLUMNS; col++){
    if (TILES_ARRAY[row][col].getColour() == currentPlayer){
      check += 1;
      if (check >= 4){
        return currentPlayer;
      }
    }
    else{
      check = 0;
    }
  }
  return NO_COLOUR;
}
int checkColumn(int currentPlayer, int col){
  int check = 0;
  for(int row = 0; row < ROWS; row++){
    if (TILES_ARRAY[row][col].getColour() == currentPlayer){
        check += 1;
        if (check >= 4){
          return currentPlayer;
        }
    }
    else{
        check = 0;
    }
  }
  return NO_COLOUR;
}
int checkDiagonalLeftUp(int currentPlayer, int row, int col){
  int check = 0;
  while(row < ROWS && col < COLUMNS){
    if (TILES_ARRAY[row][col].getColour() == currentPlayer){
        check += 1;
        if (check >= 4){
          return currentPlayer;
        }
    }
    else{
        check = 0;
    }
    row += 1;
    col += 1;
  }
  return NO_COLOUR;
}
int checkDiagonalRightUp(int currentPlayer, int row, int col){
  int check = 0;
  while(row < ROWS && col >= 0){
      if (TILES_ARRAY[row][col].getColour() == currentPlayer){
          check += 1;
          if (check >= 4){
            return currentPlayer;
          }
      }
      else{
          check = 0;
      }
      row += 1;
      col -= 1;
    }
    return NO_COLOUR;
}
