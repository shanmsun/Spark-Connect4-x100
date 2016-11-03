
#include "constants.h"
#include "connect_4_check_win.h"

int checkBoard(int currentPlayer, int winningCombo[4][2]){
  int winner = NO_COLOUR;
  for(int row = 0; row < ROWS; row++){
    winner = checkRow(currentPlayer, row, winningCombo);
    if (winner != NO_COLOUR){
      return winner;
    }
  }
  for(int col = 0; col < COLUMNS; col++){
    winner = checkColumn(currentPlayer, col, winningCombo);
    if (winner != NO_COLOUR){
      return winner;
    }
  }
  int diagonal[12];
  diagonal[1] = checkDiagonalLeftUp(currentPlayer, 2,0, winningCombo);
  diagonal[2] = checkDiagonalLeftUp(currentPlayer, 1,0, winningCombo);
  diagonal[3] = checkDiagonalLeftUp(currentPlayer, 0,0, winningCombo);
  diagonal[4] = checkDiagonalLeftUp(currentPlayer, 0,1, winningCombo);
  diagonal[5] = checkDiagonalLeftUp(currentPlayer, 0,2, winningCombo);
  diagonal[6] = checkDiagonalLeftUp(currentPlayer, 0,3, winningCombo);
  diagonal[7] = checkDiagonalRightUp(currentPlayer, 0,3, winningCombo);
  diagonal[8] = checkDiagonalRightUp(currentPlayer, 0,4, winningCombo);
  diagonal[9] = checkDiagonalRightUp(currentPlayer, 0,5, winningCombo);
  diagonal[10] = checkDiagonalRightUp(currentPlayer, 0,6, winningCombo);
  diagonal[11] = checkDiagonalRightUp(currentPlayer, 1,6, winningCombo);
  diagonal[0] = checkDiagonalRightUp(currentPlayer, 2,6, winningCombo);
  for(int i = 0; i < 12; i++){
    if (diagonal[i] != NO_COLOUR){
      return diagonal[i];
    }
  }
  return NO_COLOUR;
}
int checkRow(int currentPlayer, int row, int winningCombo[4][2]){
  int check = 0;
  for(int col = 0; col < COLUMNS; col++){
    if (TILES_ARRAY[row][col].getColour() == currentPlayer){
      check += 1;
      if (check >= 4){
        for (int j = 0; j < 4; j++) {
          winningCombo[j][0] = row;
          winningCombo[j][1] = col-j;
        }
        return currentPlayer;
      }
    }
    else{
      check = 0;
    }
  }
  return NO_COLOUR;
}
int checkColumn(int currentPlayer, int col, int winningCombo[4][2]){
  int check = 0;
  for(int row = 0; row < ROWS; row++){
    if (TILES_ARRAY[row][col].getColour() == currentPlayer){
        check += 1;
        if (check >= 4){
          for (int j = 0; j < 4; j++) {
            winningCombo[j][0] = row-j;
            winningCombo[j][1] = col;
          }
          return currentPlayer;
        }
    }
    else{
        check = 0;
    }
  }
  return NO_COLOUR;
}
int checkDiagonalLeftUp(int currentPlayer, int row, int col, int winningCombo[4][2]){
  int check = 0;
  while(row < ROWS && col < COLUMNS){
    if (TILES_ARRAY[row][col].getColour() == currentPlayer){
        check += 1;
        if (check >= 4){
          for (int j = 0; j < 4; j++) {
            winningCombo[j][0] = row-j;
            winningCombo[j][1] = col-j;
          }
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
int checkDiagonalRightUp(int currentPlayer, int row, int col, int winningCombo[4][2]){
  int check = 0;
  while(row < ROWS && col >= 0){
      if (TILES_ARRAY[row][col].getColour() == currentPlayer){
          check += 1;
          if (check >= 4){
            for (int j = 0; j < 4; j++) {
              winningCombo[j][0] = row-j;
              winningCombo[j][1] = col+j;
            }
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
