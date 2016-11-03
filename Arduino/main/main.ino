#include "testMenu.h"
#include "connect_4.h"
#include "constants.h"

Tile TILES_ARRAY[ROWS][COLUMNS];
unsigned long columnButtons[COLUMNS][3];
unsigned long AIButton[3];
unsigned long startResetButton[3];

LedControl whiteMaxim = LedControl(W_DATA_PIN, W_CS_PIN, W_CLOCK_PIN, NUM_MAXIMS_PER_COLOUR);
LedControl greenMaxim = LedControl(G_DATA_PIN, G_CS_PIN, G_CLOCK_PIN, NUM_MAXIMS_PER_COLOUR);
//MockMaxim whiteMaxim, greenMaxim;

void setup() {
  if(Serial){
    Serial.begin(115200);
    //runTestMenu();
  }
  
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

  //this is a test comment

  setupGame(TILES_ARRAY); //set up board for Connect 4 game
  playIntro(TILES_ARRAY);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("Loop");
  int result = runGame(TILES_ARRAY);
  if (result == TIMEOUT) {
    playIntro(TILES_ARRAY);
  }
}
