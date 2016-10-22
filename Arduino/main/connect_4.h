/*
 * connect_4.h
 *
 *  Created on: 2016Äê10ÔÂ21ÈÕ
 *      Author: Shanmeng
 */

#ifndef CONNECT_4_H_
#define CONNECT_4_H_
  void RunGame();
  void DisplayTurn();
  void Gamesetup();
  void reset();
  int WaitTillTilePlacemant();
  void WaitAndDisplayWinner();
  void SwichUser();
  int Place(int col);
  int checkBoard();
  int checkRow(int row);
  int checkColumn(int col);
  int checkDiagnolLeftUp(int row, int col);
  int checkDiagnolRightUp(int row, int col);
#endif /* CONNECT_4_H_ */
