#include "tile.h"
#include "IOPins.h"
#include "LedControl.h"

#ifndef CONSTANTS_H
#define CONSTANTS_H

class MockMaxim {
public:
  void setLed(int i, int j, int k, int l) { }
  void clearDisplay(int i) { }
  void shutdown(int i, bool j) { }
  void setIntensity(int i, int j) { }
};

const int ERROR = 0;

// paramters
const int ROWS = 6;
const int COLUMNS = 7;

// colour flags
const int NO_COLOUR = 0;
const int GREEN = 1;
const int WHITE = 2;

// debounce delay (ms)
const int DEBOUCE_DELAY = 200;

// How long to wait before timing out a blank game (ms)
const unsigned long TIMEOUT_VALUE = 3L * 1000L * 60L;

// Status codes
const int GAME_FINISHED = 0;
const int RESET = -1;
const int TIMEOUT = -2;

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
extern unsigned long columnButtons[COLUMNS][3];
extern unsigned long AIButton[3];
extern unsigned long startResetButton[3];

#endif
