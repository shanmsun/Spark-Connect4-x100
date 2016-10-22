#include "check_win.h"
#include "tile.h"
#include "constants.h"
#include "Arduino.h"

int BUTTON_pin[1][COLUMNS];
int Restart_pin = 0;         	//Change to actual pin on arduino
int AI_pin = 1;
int GreenTurnIndicator = 0;   	//Change to actual pin on arduino
int WhiteTurnIndicator = 1;		//Change to actual pin on arduino
int TURN = WHITE;
int ON = 1;
int OFF = 0;
int TilePlacement;
int ERROR = 0;
int BOARD[ROWS][COLUMNS];

  void RunGame(){

	  while(ERROR == 0){
		  reset();
		  int winner = NO_COLOUR;
		  Serial.println("Start new Connect 4 game...");
		  reset();
		  while (winner == NO_COLOUR){
			  int placed = 0;
			  SwichUser();
			  DisplayTurn();

			  Serial.println("Turn displayed...");
			  Serial.println("Please place a tile...");

			  while (!placed){
				  TilePlacement = WaitTillTilePlacemant();

				  Serial.println("Placing the tile...");

				  placed = Place(TilePlacement);
			  }

			  Serial.println("Tile placed...");
			  Serial.println("Checking win...");

			  winner = checkBoard();
		  }

		  WaitAndDisplayWinner();
	  }

  }
  void DisplayTurn(){
	  if (TURN == WHITE){
		  	  digitalWrite(WhiteTurnIndicator, ON);
		  	  digitalWrite(GreenTurnIndicator, OFF);
	  	  }
	  	  else{
	  		  digitalWrite(GreenTurnIndicator, ON);
	  		  digitalWrite(WhiteTurnIndicator, OFF);
	  	  }
  }
  void Gamesetup(){
	  for (int col = 0; col < COLUMNS; col++){
		  BUTTON_pin[1][col] = col;                      //Change to actual pin on arduino
		  pinMode(BUTTON_pin[1][col], INPUT);
	  }
	  pinMode(GreenTurnIndicator, OUTPUT);
	  pinMode(WhiteTurnIndicator, OUTPUT);
	  reset();
  }

  void reset(){
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

  int WaitTillTilePlacemant(){
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
  void WaitAndDisplayWinner(){
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
	  	val = digitalRead(Restart_pin);
	  }

  }
  void SwichUser(){
	  if (TURN == WHITE){
		  TURN = GREEN;
	  }
	  else{
		  TURN = WHITE;
	  }
  }
  int Place(int col){
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
	  int diagnol[12];
	  diagnol[1] = checkDiagnolLeftUp(2,0);
	  diagnol[2] = checkDiagnolLeftUp(1,0);
	  diagnol[3] = checkDiagnolLeftUp(0,0);
	  diagnol[4] = checkDiagnolLeftUp(0,1);
	  diagnol[5] = checkDiagnolLeftUp(0,2);
	  diagnol[6] = checkDiagnolLeftUp(0,3);
	  diagnol[7] = checkDiagnolRightUp(0,3);
	  diagnol[8] = checkDiagnolRightUp(0,4);
	  diagnol[9] = checkDiagnolRightUp(0,5);
	  diagnol[10] = checkDiagnolRightUp(0,6);
	  diagnol[11] = checkDiagnolRightUp(1,6);
	  diagnol[0] = checkDiagnolRightUp(2,6);
	  for(int i = 0; i < 12; i++){
		  if (diagnol[i] != NO_COLOUR){
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
  int checkDiagnolLeftUp(int row, int col){
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
  int checkDiagnolRightUp(int row, int col){
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



