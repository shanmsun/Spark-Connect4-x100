#include "testMenu.h"
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
  Serial.println("----------Mega Connect 4 Boot Menu-----------");
  for(int i=0; i<5; i++){
    char option[100]; 
    sprintf(option, "%i - %s", i, testMenuOptions[i]);
    Serial.println(option);
  }
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
 //todo 
}

void testRow(){
  //todo
}

void testColumn(){
  //todo
}
void testTile(){
  //todo
}
