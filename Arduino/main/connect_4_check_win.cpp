
#include "constants.h"
#include "connect_4_check_win.h"

int checkBoard(){
  int winner = NO_COLOUR;
  for(int row = 0; row < ROWS; row++){
    winner = checkRow(row);
    if (winner != NO_COLOUR){
      return winner;
    }
  }
  for(int col = 0; col < COLUMNS; col++){
    winner = checkColumn(col);
    if (winner != NO_COLOUR){
      return winner;
    }
  }
  int diagonal[12];
  diagonal[1] = checkDiagonalLeftUp(2,0);
  diagonal[2] = checkDiagonalLeftUp(1,0);
  diagonal[3] = checkDiagonalLeftUp(0,0);
  diagonal[4] = checkDiagonalLeftUp(0,1);
  diagonal[5] = checkDiagonalLeftUp(0,2);
  diagonal[6] = checkDiagonalLeftUp(0,3);
  diagonal[7] = checkDiagonalRightUp(0,3);
  diagonal[8] = checkDiagonalRightUp(0,4);
  diagonal[9] = checkDiagonalRightUp(0,5);
  diagonal[10] = checkDiagonalRightUp(0,6);
  diagonal[11] = checkDiagonalRightUp(1,6);
  diagonal[0] = checkDiagonalRightUp(2,6);
  for(int i = 0; i < 12; i++){
    if (diagonal[i] != NO_COLOUR){
      return winner;
    }
  }
  return winner;
}
int checkRow(int row){
  int check = 0;
  for(int col = 0; col < COLUMNS; col++){
    if (BOARD[row][col] == TURN){
      check += 1;
      if (check >= 4){
        return TURN;
      }
    }
    else{
      check = 0;
    }
  }
  return NO_COLOUR;
}
int checkColumn(int col){
  int check = 0;
  for(int row = 0; row < ROWS; row++){
    if (BOARD[row][col] == TURN){
        check += 1;
        if (check >= 4){
          return TURN;
        }
    }
    else{
        check = 0;
    }
  }
  return NO_COLOUR;
}
int checkDiagonalLeftUp(int row, int col){
  int check = 0;
  while(row < ROWS && col < COLUMNS){
    if (BOARD[row][col] == TURN){
        check += 1;
        if (check >= 4){
          return TURN;
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
int checkDiagonalRightUp(int row, int col){
  int check = 0;
  while(row < ROWS && col >= 0){
      if (BOARD[row][col] == TURN){
          check += 1;
          if (check >= 4){
            return TURN;
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
