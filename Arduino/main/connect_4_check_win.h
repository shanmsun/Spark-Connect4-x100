#ifndef CONNECT_4_CHECK_WIN_H
#define CONNECT_4_CHECK_WIN_H
  int checkBoard(int currentPlayer);
  int checkRow(int currentPlayer, int row);
  int checkColumn(int currentPlayer, int col);
  int checkDiagonalLeftUp(int currentPlayer, int row, int col);
  int checkDiagonalRightUp(int currentPlayer, int row, int col);
#endif
