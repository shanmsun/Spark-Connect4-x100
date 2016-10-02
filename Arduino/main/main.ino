#include "constants.h"
#include "testMenu.h"

Tile TILES_ARRAY[ROWS][COLUMNS];
LedControl whiteMaxim = LedControl(W_DATA_PIN, W_CLOCK_PIN, W_CS_PIN, NUM_MAXIMS_PER_COLOUR); 
LedControl greenMaxim = LedControl(G_DATA_PIN, G_CLOCK_PIN, G_CS_PIN, NUM_MAXIMS_PER_COLOUR); 

/*
 * This assigns an id to each tile (basically the coordinates). 
 * This should only be set once- a boolean flag in the Tile class avoids
 * setting the row and coordinates more than once
 */
void initializeTilesArray(){
  for(int row = 0; row < ROWS; row++){
    for(int col = 0; col < COLUMNS; col++){
      TILES_ARRAY[row][col].setCoordinates(row, col);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  initializeTilesArray();
  
  if(Serial){
    Serial.begin(115200); 
    runTestMenu(); 
  } 

}


void loop() {
  // put your main code here, to run repeatedly:

}

