#include "tile.h"
#include "constants.h"
#include "connect_4_check_win.h"
#include "Arduino.h"

int BUTTON_pin[1][COLUMNS];
int d = WHITE;
int ON = 1;
int OFF = 0;
int TilePlacement;
int ERROR = 0;
int BOARD[ROWS][COLUMNS];
int TURN = WHITE;

  void switchUser(){
    if (d == WHITE){
      d = GREEN;
    }
    else{
      d = WHITE;
    }
  }

  void displayTurn(){
	  if (d == WHITE){
		  	  digitalWrite(PLAYER_W_INDICATOR, ON);
		  	  digitalWrite(PLAYER_G_INDICATOR, OFF);
	  	  }
	  	  else{
	  		  digitalWrite(PLAYER_G_INDICATOR, ON);
	  		  digitalWrite(PLAYER_W_INDICATOR, OFF);
	  	  }
  }

  int placeDisc(int col){
	  for(int row = 0; row < ROWS; row++){
		  if (BOARD[row][col] == NO_COLOUR){
			  BOARD[row][col] = TURN;
			  Tile tile = TILES_ARRAY[row][col];
			  tile.setColour(TURN);
			  return 1;
		  }
	  }
	  Serial.println("Try again column full");
	  return 0; //column full, try again
  }

  void waitAndDisplayWinner(){
	  int val = LOW;                                   //Change according to button
	  //Display all tiles in winning colour
	  Serial.println("Displaying winner......");
	  for(int row = ROWS; row >0; row--){
		  for(int col = 0; col < COLUMNS; col++){
	  	  		Tile tile = TILES_ARRAY[row][col];
	  	  		tile.setColour(d);
	  	  	}
	  }
	  delay(5000);
	  for(int row = ROWS; row >0; row--){

		  for(int col = 0; col < COLUMNS; col++){
		  	  	Tile tile = TILES_ARRAY[row][col];
		  	  	tile.setColour(BOARD[row][col]);
		  }
	  }
	  Serial.println("Wait until restarted");
	  while(val != HIGH){
	  	val = digitalRead(START_RESET_BUTTON);
	  }
  }

  int waitTillTilePlacemant(){
	  int val = LOW;                                   //Change according to button
	  int col = -1;
	  while(val != HIGH){
		  if (col >= COLUMNS){
			  col = -1;
		  }
		  col += 1;
		  val = digitalRead(BUTTON_pin[1][col]);
	  }
	  return col;
  }

  void resetGame(){
    Serial.println("Resetting......");
    for(int row = 0; row < ROWS; row++){
          for(int col = 0; col < COLUMNS; col++){
            Tile tile = TILES_ARRAY[row][col];
            tile.setColour(NO_COLOUR);
            BOARD[row][col] = NO_COLOUR;
          }
        }
    Serial.println("All tiles set to no colour.");
  }

  void setupGame(){
	  for (int col = 0; col < COLUMNS; col++){
		  BUTTON_pin[1][col] = col;                      //Change to actual pin on arduino
		  pinMode(BUTTON_pin[1][col], INPUT);
	  }
	  pinMode(PLAYER_G_INDICATOR, OUTPUT);
	  pinMode(PLAYER_W_INDICATOR, OUTPUT);
	  resetGame();
  }

  void runGame(){

	  while(ERROR == 0){
		  resetGame();
		  int winner = NO_COLOUR;
		  Serial.println("Start new Connect 4 game...");
		  resetGame();
		  while (winner == NO_COLOUR){
			  int placed = 0;
			  switchUser();
			  displayTurn();

			  Serial.println("Turn displayed...");
			  Serial.println("Please place a tile...");

			  while (!placed){
				  TilePlacement = waitTillTilePlacemant();

				  Serial.println("Placing the tile...");

				  placed = placeDisc(TilePlacement);
			  }

			  Serial.println("Tile placed...");
			  Serial.println("Checking win...");

			  winner = checkBoard();
		  }

		  waitAndDisplayWinner();
	  }

  }
