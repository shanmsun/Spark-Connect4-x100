#include "tile.h"
#include "LedControl.h"

#ifndef CONSTANTS_H
#define CONSTANTS_H
  const int ROWS = 6;
  const int COLUMNS = 7;

  const int NO_COLOUR = 0;
  const int GREEN = 1;
  const int WHITE = 2;
  
  extern Tile TILES_ARRAY[ROWS][COLUMNS]; 
  extern LedControl whiteMaxim;
  extern LedControl greenMaxim; 

  const int W_DATA_PIN = 12;
  const int W_CS_PIN = 11; 
  const int W_CLOCK_PIN = 10;

  const int G_DATA_PIN = 5;
  const int G_CS_PIN = 4; 
  const int G_CLOCK_PIN = 3;

  const int NUM_MAXIMS_PER_COLOUR = 1;

  const int PLAYER_G_INDICATOR = 0;     //Change to actual pin on arduino
  const int PLAYER_W_INDICATOR = 1;   //Change to actual pin on arduino
  
#endif
