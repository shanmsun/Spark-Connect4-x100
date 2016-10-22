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
  void runGame(Tile tileArray[][COLUMNS]);
  void displayTurn();
  void setupGame(Tile tileArray[][COLUMNS]);
  void resetGame(Tile tileArray[][COLUMNS]);
  int waitTillTilePlacemant();
  void waitAndDisplayWinner(Tile tileArray[][COLUMNS]);
  void switchUser();
  int placeDisc(int col, Tile tileArray[][COLUMNS]);
#endif /* CONNECT_4_H_ */
