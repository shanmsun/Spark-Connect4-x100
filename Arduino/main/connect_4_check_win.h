#ifndef CONNECT_4_CHECK_WIN_H
#define CONNECT_4_CHECK_WIN_H
  int checkBoard(int currentPlayer, int winningCombo[4][2]);
  int checkRow(int currentPlayer, int row, int winningCombo[4][2]);
  int checkColumn(int currentPlayer, int col, int winningCombo[4][2]);
  int checkDiagonalLeftUp(int currentPlayer, int row, int col, int winningCombo[4][2]);
  int checkDiagonalRightUp(int currentPlayer, int row, int col, int winningCombo[4][2]);
#endif
