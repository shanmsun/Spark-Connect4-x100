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

void runTestMenu(){
  printTestMenu();
  while(option != 0){
    parseResponse();  
  }
  Serial.println("Exiting Test");
}

void printTestMenu(){
  Serial.println("----------Connect 4 x100 Boot Menu-----------");
  for(int i=0; i<5; i++){
    char option[100]; 
    sprintf(option, "%i - %s", i, testMenuOptions[i]);
    Serial.println(option);
  }
  Serial.println("---------------------------------------------");
}

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
  tile.setColour(true, false);
  delay(500);
  tile.setColour(false, false);
  delay(500);
  tile.setColour(false, true);
  delay(500);
}
