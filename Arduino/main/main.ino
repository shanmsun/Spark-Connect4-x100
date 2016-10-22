#include "testMenu.h"
#include "connect_4.h"
#include "constants.h"

Tile TILES_ARRAY[ROWS][COLUMNS];
int columnButtons[3][COLUMNS];
int AIButton[3];
int startResetButton[3];

LedControl whiteMaxim = LedControl(W_DATA_PIN, W_CLOCK_PIN, W_CS_PIN, NUM_MAXIMS_PER_COLOUR);
LedControl greenMaxim = LedControl(G_DATA_PIN, G_CLOCK_PIN, G_CS_PIN, NUM_MAXIMS_PER_COLOUR);

void setup() {
  // put your setup code here, to run once:

  //this is a test comment
  if(Serial){
    Serial.begin(9600);
    runTestMenu();
  }
	setupGame(TILES_ARRAY); //set up board for Connect 4 game
}

void loop() {
  // put your main code here, to run repeatedly:

	runGame(TILES_ARRAY);
}
