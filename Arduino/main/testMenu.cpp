#include "tile.h"
#include "testMenu.h"
#include "constants.h"
#include "Arduino.h"
#include "connect_4.h"

char* testMenuOptions[] = {
  "Skip Test",
  "Test Entire Board",
  "Test Entire Row",
  "Test Entire Column",
  "Test Individual Tile",
  "Read Column Switches",
  "Read Start/Reset Switch",
  "Read AI Switch",
  "Turn on indicator for white",
  "Turn on indicator for green",
  "Layout"
};

String rowPrompt = "Row (Zero-indexed)> ";
String colPrompt = "Col (Zero-indexed)> ";
//
String colConfig ="0 1 2 3 4 5 6\n";
String rowConfig ="1\n2\n3\n4\n5";

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
  for(int i=0; i<11; i++){
    char option[100]; 
    sprintf(option, "%i - %s", i, testMenuOptions[i]);
    Serial.println(option);
  }
  Serial.println("---------------------------------------------");
}

int readInt(){
  while(Serial.available() <= 0){
  }

  return Serial.parseInt(); 
}

/*
 * Parses the option the user selects. The number associated to the menu option 
 * are based on the order in which the options are in the array 
 */
void parseResponse(){ 
  Serial.print("> ");

  option = readInt();
  Serial.println((int) option);
  switch ((int) option){
    case 0:
      Serial.println("Quitting...");
      break;
    case 1:
      Serial.println("Testing board...");
      testBoard();
      break;
    case 2:{
      Serial.println("Testing row...");
      Serial.print(rowPrompt);
      int row = readInt();
      
      Serial.println(row);
      testRow(row);}
      break;
    case 3:{
      Serial.println("Testing col...");
      Serial.print(colPrompt);
      int col = readInt();

      Serial.println(col);
      testColumn(col);
    }
      break;
    case 4:{
      Serial.println("Testing individual tile...");
      Serial.print(rowPrompt);
      int row = readInt();
      Serial.println(row);
      
      Serial.print(colPrompt);
      int col = readInt();
      Serial.println(col);
     
      testTile(row, col);}
      break;
    case 5:
      Serial.println("Testing column switches...");
      testSwitchResult(true, false);
      break;
    case 6:
      Serial.println("Testing start/reset switch tile...");
      testSwitchResult(false, true);
      break;
    case 7:
      Serial.println("Testing AI switch...");
      testSwitchResult(false, true);
      break;
    case 8:
      Serial.println("Testing white indicator...");
      turnOnWhite();
      break;
    case 9:
      Serial.println("Testing green indicator...");
      turnOnGreen();
      break;
    case 10:
      printHelp();
      break;
    default:
      Serial.println("Invalid option entered");
      break;
  }
  Serial.println("Done");
}

void printHelp(){
  Serial.println("Configuration of board: ");
  Serial.print(colConfig);
  Serial.print(rowConfig);
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
  Serial.print(row);
  Serial.print(col);
  
  Tile tile = TILES_ARRAY[row][col];
  tile.setColour(WHITE);
  delay(200);
  tile.setColour(NO_COLOUR);
  delay(200);
  tile.setColour(GREEN);
  delay(200);
  Serial.println();
}

int testSwitch(unsigned long *buttonObj){
  return switchToggled(buttonObj[0], &buttonObj[1], &buttonObj[2]) ? 1 : 0;
}

void testSwitchResult(bool isMultiple, bool isReset){
  Serial.println("This will print out when the switch transitioned from 0->1 over the span of 10 seconds");

  unsigned long endTime = millis() + 10000;
  while( millis() < endTime){

    int result[] = {0, 0, 0, 0, 0, 0, 0};
    if(isMultiple){
      result[0] = testSwitch(columnButtons[0]);
      result[1] = testSwitch(columnButtons[1]);
      result[2] = testSwitch(columnButtons[2]);
      result[3] = testSwitch(columnButtons[3]);
      result[4] = testSwitch(columnButtons[4]);
      result[5] = testSwitch(columnButtons[5]);
      result[6] = testSwitch(columnButtons[6]);
    } else {
      result[0] = testSwitch(startResetButton);
      result[1] = testSwitch(AIButton);
      result[2] = -1;
      result[3] = -1;
      result[4] = -1;
      result[5] = -1;
      result[6] = -1;
    }

    char option[100];
    sprintf(option, "%d \t%d \t%d \t%d \t%d \t%d \t%d", result[0], result[1], result[2],
    result[3], result[4], result[5], result[6]);
    Serial.println(option);
  }
}

void turnOnGreen(){
  Serial.println("Turning on green");
  displayTurn(GREEN);
  delay(1000);
  digitalWrite(PLAYER_G_INDICATOR_PIN, LOW); 
}

void turnOnWhite(){
  Serial.println("Turning on white");
  displayTurn(WHITE);
  delay(1000);
  digitalWrite(PLAYER_W_INDICATOR_PIN, LOW); 
}

