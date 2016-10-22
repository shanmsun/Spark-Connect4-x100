/*
 * connect_4.h
 *
 *  Created on: 2016��10��21��
 *      Author: Shanmeng
 */

#ifndef CONNECT_4_H_
#define CONNECT_4_H_
  void runGame();
  void displayTurn();
  void setupGame()();
  void resetGame();
  int waitTillTilePlacemant();
  void waitAndDisplayWinner()();
  void switchUser();
  int placeDisc(int col);
  int checkBoard();
  int checkRow(int row);
  int checkColumn(int col);
  int checkDiagonalLeftUp(int row, int col);
  int checkDiagonalRightUp(int row, int col);
#endif /* CONNECT_4_H_ */
