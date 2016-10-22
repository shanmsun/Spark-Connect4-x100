#include "tile.h"
#include "IOPins.h"
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

#endif
