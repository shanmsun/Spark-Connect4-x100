#include "tile.h"
#include "testMenu.h"
#include "constants.h"
#include "Arduino.h"

char* testMenuOptions[] = {
  "Skip Test",
  "Test Entire Board",
  "Test Entire Row",
  "Test Entire Column",
  "Test Individual Tile"
};

int option = -1;

/*
 * Print out the menu and parses for a response. 
 * This function is in an infinite loop unless the user manually enters
 * the option to quit
 */
void runTestMenu(){
  printTestMenu();
  while(option != 0){
    parseResponse();  
  }
  Serial.println("Exiting Test");
}

/*
 * Prints out the options based on the array defined at the top. 
 */
void printTestMenu(){
  Serial.println("----------Connect 4 x100 Boot Menu-----------");
  for(int i=0; i<5; i++){
    char option[100]; 
    sprintf(option, "%i - %s", i, testMenuOptions[i]);
    Serial.println(option);
  }
  Serial.println("---------------------------------------------");
}

/*
 * Parses the option the user selects. The number associated to the menu option 
 * are based on the order in which the options are in the array 
 */
void parseResponse(){ 
  Serial.print("> ");
  
  while(Serial.available() <= 0){
  }

  option = Serial.read();
  Serial.println((char) option);
  switch ((char) option){
    case '0':
      Serial.println("Quitting...");
      break;
    case '1':
      break;
    case '2':
      break;
    case '3':
      break;
    case '4':
      break;
    default:
      Serial.println("Invalid option entered");
      break;
  }
}

void testBoard(){
  for(int row = 0; row < ROWS; row++){
    testRow(row); 
  }
}

void testRow(int row){
  for(int column = 0; column < COLUMNS; column++){
     testTile(row, column); 
  }
}

void testColumn(int column){
  for(int row = 0; row < ROWS; row++){
    testTile(row, column); 
  }
}

void testTile(int row, int col){
  Tile tile = TILES_ARRAY[row][col];
  tile.setColour(WHITE);
  delay(500);
  tile.setColour(NO_COLOUR);
  delay(500);
  tile.setColour(GREEN);
  delay(500);
}
