#include "tile.h"
#include "constants.h"
#include "Arduino.h"

int BUTTON_pin[1][COLUMNS];
int TURN = WHITE;
int ON = 1;
int OFF = 0;
int TilePlacement;
int ERROR = 0;
int BOARD[ROWS][COLUMNS];

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

		  waitAndDisplayWinner()();
	  }

  }
  void displayTurn(){
	  if (TURN == WHITE){
		  	  digitalWrite(PLAYER_W_INDICATOR, ON);
		  	  digitalWrite(PLAYER_G_INDICATOR, OFF);
	  	  }
	  	  else{
	  		  digitalWrite(PLAYER_G_INDICATOR, ON);
	  		  digitalWrite(PLAYER_W_INDICATOR, OFF);
	  	  }
  }
  void setupGame()(){
	  for (int col = 0; col < COLUMNS; col++){
		  BUTTON_pin[1][col] = col;                      //Change to actual pin on arduino
		  pinMode(BUTTON_pin[1][col], INPUT);
	  }
	  pinMode(PLAYER_G_INDICATOR, OUTPUT);
	  pinMode(PLAYER_W_INDICATOR, OUTPUT);
	  //resetGame();
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
  void waitAndDisplayWinner()(){
	  int val = LOW;                                   //Change according to button
	  //Display all tiles in winning colour
	  Serial.println("Displaying winner......");
	  for(int row = ROWS; row >0; row--){
		  for(int col = 0; col < COLUMNS; col++){
	  	  		Tile tile = TILES_ARRAY[row][col];
	  	  		tile.setColour(TURN);
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
  void switchUser(){
	  if (TURN == WHITE){
		  TURN = GREEN;
	  }
	  else{
		  TURN = WHITE;
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

  int checkBoard(){
	  int winner = NO_COLOUR;
	  for(int row = 0; row < ROWS; row++){
		  winner = checkRow(row);
		  if (winner != NO_COLOUR){
			  return winner;
		  }
	  }
	  for(int col = 0; col < COLUMNS; col++){
		  winner = checkColumn(col);
		  if (winner != NO_COLOUR){
			  return winner;
		  }
	  }
	  int diagonal[12];
	  diagonal[1] = checkDiagonalLeftUp(2,0);
	  diagonal[2] = checkDiagonalLeftUp(1,0);
	  diagonal[3] = checkDiagonalLeftUp(0,0);
	  diagonal[4] = checkDiagonalLeftUp(0,1);
	  diagonal[5] = checkDiagonalLeftUp(0,2);
	  diagonal[6] = checkDiagonalLeftUp(0,3);
	  diagonal[7] = checkDiagonalRightUp(0,3);
	  diagonal[8] = checkDiagonalRightUp(0,4);
	  diagonal[9] = checkDiagonalRightUp(0,5);
	  diagonal[10] = checkDiagonalRightUp(0,6);
	  diagonal[11] = checkDiagonalRightUp(1,6);
	  diagonal[0] = checkDiagonalRightUp(2,6);
	  for(int i = 0; i < 12; i++){
		  if (diagonal[i] != NO_COLOUR){
			  return winner;
		  }
	  }
	  return winner;
  }
  int checkRow(int row){
	  int check = 0;
	  for(int col = 0; col < COLUMNS; col++){
		  if (BOARD[row][col] == TURN){
			  check += 1;
			  if (check >= 4){
				  return TURN;
			  }
		  }
		  else{
			  check = 0;
		  }
	  }
	  return NO_COLOUR;
  }
  int checkColumn(int col){
	  int check = 0;
	  for(int row = 0; row < ROWS; row++){
		  if (BOARD[row][col] == TURN){
			  	check += 1;
		  		if (check >= 4){
		  			return TURN;
		  		}
		  }
		  else{
		  		check = 0;
		  }
	  }
	  return NO_COLOUR;
  }
  int checkDiagonalLeftUp(int row, int col){
	  int check = 0;
	  while(row < ROWS && col < COLUMNS){
		  if (BOARD[row][col] == TURN){
		  		check += 1;
		  		if (check >= 4){
		  			return TURN;
		  		}
		  }
		  else{
		  		check = 0;
		  }
		  row += 1;
		  col += 1;
	  }
	  return NO_COLOUR;
  }
  int checkDiagonalRightUp(int row, int col){
	  int check = 0;
	  while(row < ROWS && col >= 0){
	 		  if (BOARD[row][col] == TURN){
	 		  		check += 1;
	 		  		if (check >= 4){
	 		  			return TURN;
	 		  		}
	 		  }
	 		  else{
	 		  		check = 0;
	 		  }
	 		  row += 1;
	 		  col -= 1;
	 	  }
	 	  return NO_COLOUR;
  }
