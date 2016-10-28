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
  bool switchToggled(int switchPin, int* lastValue, int* lastActivated);
  void runGame(Tile tileArray[][COLUMNS]);
  void displayTurn(int currentPlayer);
  void setupGame(Tile tileArray[][COLUMNS]);
  void resetGame(Tile tileArray[][COLUMNS]);
  int waitTillTilePlacemant();
  void waitAndDisplayWinner(int currentPlayer, Tile tileArray[][COLUMNS]);
  void switchUser(int *currentPlayer);
  int placeDisc(int col, Tile tileArray[][COLUMNS]);
  void easterEgg();
#endif /* CONNECT_4_H_ */
