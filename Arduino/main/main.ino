#include "testMenu.h"
#include "connect_4.h"
#include "constants.h"

Tile TILES_ARRAY[ROWS][COLUMNS];
int columnButtons[COLUMNS][3];
int AIButton[3];
int startResetButton[3];

LedControl whiteMaxim = LedControl(W_DATA_PIN, W_CS_PIN, W_CLOCK_PIN, NUM_MAXIMS_PER_COLOUR);
LedControl greenMaxim = LedControl(G_DATA_PIN, G_CS_PIN, G_CLOCK_PIN, NUM_MAXIMS_PER_COLOUR);

void setup() {
  for(int row = 0; row < ROWS; row++){
    for(int col= 0; col < COLUMNS; col++){
      //segment was wired from A-B-C-E-F (D is missing...)
      if(row >= 3){
        TILES_ARRAY[row][col].setCoordinates(row+2, col+1); 
      } else {
        TILES_ARRAY[row][col].setCoordinates(row+1, col+1);  
      }
    }
  }
  
  whiteMaxim.clearDisplay(0);
  whiteMaxim.shutdown(0,false);
  whiteMaxim.setIntensity(0, 15);

  
  greenMaxim.clearDisplay(0);
  greenMaxim.shutdown(0,false);
  greenMaxim.setIntensity(0, 15);
  
  // put your setup code here, to run once:
  setupGame(TILES_ARRAY); //set up board for Connect 4 game

  //this is a test comment
  if(Serial){
    Serial.begin(115200);
    //the following line should be moved to before the loop is executed
    //otherwise pins will not be set correctly unless serial port
    //is available
    runTestMenu();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
	runGame(TILES_ARRAY);
}
