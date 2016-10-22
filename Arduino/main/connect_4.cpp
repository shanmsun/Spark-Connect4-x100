#include "tile.h"
#include "constants.h"
#include "connect_4_check_win.h"
#include "Arduino.h"

int BUTTON_pin[1][COLUMNS];
int TilePlacement;
int BOARD[ROWS][COLUMNS];
int TURN = WHITE;

  /*  
   * Swaps the current user 
   */
  void switchUser(int *currentPlayer){
    if (*currentPlayer == WHITE){
      *currentPlayer = GREEN;
    }
    else{
      *currentPlayer = WHITE;
    }
  }

  /*
   * Displays which user should play by activating the corresponding LED
   */
  void displayTurn(int currentPlayer){
	  if (currentPlayer == WHITE){
  	  digitalWrite(PLAYER_W_INDICATOR, HIGH);
  	  digitalWrite(PLAYER_G_INDICATOR, LOW);
	  } else{
		  digitalWrite(PLAYER_G_INDICATOR, HIGH);
		  digitalWrite(PLAYER_W_INDICATOR, LOW);
	  }
  }

  /*
   * Places the disc in the column the user selected
   */
  int placeDisc(int currentPlayer, int col, Tile tileArray[][COLUMNS]){
	  for(int row = 0; row < ROWS; row++){
		  if (BOARD[row][col] == NO_COLOUR){
			  BOARD[row][col] = currentPlayer;
			  Tile tile = tileArray[row][col];
			  tile.setColour(currentPlayer);
			  return 1;
		  }
	  }
	  Serial.println("Try again column full");
	  return ERROR; //column full, try again
  }

  void waitAndDisplayWinner(int currentPlayer, Tile tileArray[][COLUMNS]){
	  int val = LOW;                                   //Change according to button
	  //Display all tiles in winning colour
	  Serial.println("Displaying winner......");
	  for(int row = ROWS; row >0; row--){
		  for(int col = 0; col < COLUMNS; col++){
	  	  		Tile tile = tileArray[row][col];
	  	  		tile.setColour(currentPlayer);
	  	  	}
	  }
	  delay(5000);
	  for(int row = ROWS; row >0; row--){

		  for(int col = 0; col < COLUMNS; col++){
		  	  	Tile tile = tileArray[row][col];
		  	  	tile.setColour(BOARD[row][col]);
		  }
	  }
	  Serial.println("Wait until restarted");
	  while(val != HIGH){
	  	val = digitalRead(START_RESET_BUTTON);
	  }
  }

  /*
   * Infinite-loop program that does not exit until the user selects a tile
   */
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

  /*
   * Resets the game
   */
  void resetGame(Tile tileArray[][COLUMNS]){
    Serial.println("Resetting......");
    for(int row = 0; row < ROWS; row++){
          for(int col = 0; col < COLUMNS; col++){
            Tile tile = tileArray[row][col];
            tile.setColour(NO_COLOUR);
            BOARD[row][col] = NO_COLOUR;
          }
        }
    Serial.println("All tiles set to no colour.");
  }

  void setupGame(Tile tileArray[][COLUMNS]){
	  for (int col = 0; col < COLUMNS; col++){
		  BUTTON_pin[1][col] = col;                      //Change to actual pin on arduino
		  pinMode(BUTTON_pin[1][col], INPUT);
	  }
	  pinMode(PLAYER_G_INDICATOR, OUTPUT);
	  pinMode(PLAYER_W_INDICATOR, OUTPUT);
	  resetGame(tileArray);
  }

  void runGame(Tile tileArray[][COLUMNS]){
    int player = WHITE;
	  while(ERROR == 0){
		  int winner = NO_COLOUR;
		  Serial.println("Start new Connect 4 game...");
		  resetGame(tileArray);

		  while (winner == NO_COLOUR){
			  int placed = 0;
			  switchUser(&player);
			  displayTurn(player);

			  Serial.println("Turn displayed...");
			  Serial.println("Please place a tile...");

			  while (!placed){
				  TilePlacement = waitTillTilePlacemant();

				  Serial.println("Placing the tile...");

				  placed = placeDisc(player, TilePlacement, tileArray);
			  }

			  Serial.println("Tile placed...");
			  Serial.println("Checking win...");

			  winner = checkBoard();
		  }

		  waitAndDisplayWinner(winner, tileArray);
	  }

  }
