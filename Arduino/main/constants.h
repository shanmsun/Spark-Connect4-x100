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

  // debounce delay (ms)
  const int DEBOUNCE_DELAY = 30;

  // external variables that will need to be shared
  extern Tile TILES_ARRAY[ROWS][COLUMNS];
  extern LedControl whiteMaxim;
  extern LedControl greenMaxim;

  /*  a multiarray that stores the button values due to debouncing issues
   *  each column contains (in order from top-0 to bottom-2):
   *   - assigned pin
   *   - previous value
   *   - time when previous value was obtained
   */
  extern int columnButtons[COLUMNS][3];
  extern int AIButton[3];
  extern int startResetButton[3];

#endif
