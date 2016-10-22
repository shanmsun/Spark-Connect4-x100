#include "tile.h"
#include "LedControl.h"

#ifndef CONSTANTS_H
#define CONSTANTS_H

  const int ERROR = 0;

  // paramters
  const int ROWS = 6;
  const int COLUMNS = 7;

  // colour flags
  const int NO_COLOUR = 0;
  const int GREEN = 1;
  const int WHITE = 2;

  // external variables that will need to be shared
  extern Tile TILES_ARRAY[ROWS][COLUMNS];
  extern LedControl whiteMaxim;
  extern LedControl greenMaxim;
  extern int BOARD[ROWS][COLUMNS];
  extern int TURN;

  // MAXIM pin configuraitons
  const int W_DATA_PIN = 12;
  const int W_CS_PIN = 11;
  const int W_CLOCK_PIN = 10;

  const int G_DATA_PIN = 5;
  const int G_CS_PIN = 4;
  const int G_CLOCK_PIN = 3;

  const int NUM_MAXIMS_PER_COLOUR = 1;

  // turn indicator pins
  const int PLAYER_G_INDICATOR = 0;     //Change to actual pin on arduino
  const int PLAYER_W_INDICATOR = 1;   //Change to actual pin on arduino

  // toggle/feature button
  const int START_RESET_BUTTON = 4;
  const int AI_BUTTON = 3;

#endif
