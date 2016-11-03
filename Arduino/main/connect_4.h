/*
 * connect_4.h
 *
 *  Created on: 2016��10��21��
 *      Author: Shanmeng
 */

#include "tile.h"
#include "constants.h"

#ifndef CONNECT_4_H_
#define CONNECT_4_H_
  bool switchToggled(unsigned long switchPin, unsigned long* lastValue, unsigned long* lastActivated);
  void playIntro(Tile tileArray[][COLUMNS]);
  int runGame(Tile tileArray[][COLUMNS]);
  void displayTurn(int currentPlayer);
  void setupGame(Tile tileArray[][COLUMNS]);
  void resetGame(Tile tileArray[][COLUMNS]);
  int waitTillTilePlacemant();
  void waitAndDisplayWinner(int currentPlayer, Tile tileArray[][COLUMNS]);
  void switchUser(int *currentPlayer);
  bool placeDisc(int col, Tile tileArray[][COLUMNS]);
#endif /* CONNECT_4_H_ */
