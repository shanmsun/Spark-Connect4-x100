#include "testMenu.h"
#include "connect_4.h"
#include "constants.h"

void setup() {
  // put your setup code here, to run once:
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
