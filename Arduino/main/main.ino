#include "constants.h"
#include "testMenu.h"

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
//  initializeTilesArray();
  
  if(Serial){
    Serial.begin(115200); 
    runTestMenu(); 
  } 

}


void loop() {
  // put your main code here, to run repeatedly:

}

