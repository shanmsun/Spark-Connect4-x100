#include "testMenu.h"
#include "check_win.h"

void setup() {
  // put your setup code here, to run once:
  if(Serial){
    Serial.begin(9600); 
    runTestMenu(); 
  } 
	Gamesetup(); //set up board for Connect 4 game
}

void loop() {
  // put your main code here, to run repeatedly:
	
	RunGame();
}