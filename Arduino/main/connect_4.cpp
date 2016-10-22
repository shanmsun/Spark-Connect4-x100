#include "tile.h"
#include "constants.h"
#include "connect_4_check_win.h"
#include "Arduino.h"

int BUTTON_pin[1][COLUMNS];

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
		  if (tileArray[row][col].getColour() == NO_COLOUR){
			  tileArray[row][col].setColour(currentPlayer);
			  return 1;
		  }
	  }
	  Serial.println("Try again column full");
	  return ERROR; //column full, try again
  }

  /*
   *   Displays which side won by turning all the tiles to the colour of the
   *   winning side
   */
  void waitAndDisplayWinner(int currentPlayer, Tile tileArray[][COLUMNS]){
	  //Display all tiles in winning colour
	  Serial.println("Displaying winner......");
	  for(int row = 0; row >ROWS; row++){
		  for(int col = 0; col < COLUMNS; col++){
	  	  		Tile tile = tileArray[row][col];
	  	  		tile.setColour(currentPlayer);
	  	  	}
	  }
	  delay(5000);
	  Serial.println("Wait until restarted");
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
            tileArray[row][col].setColour(NO_COLOUR);
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
    resetGame(tileArray);
    int player = WHITE;
	  int winner = NO_COLOUR;
    int TilePlacement;

	  Serial.println("Start new Connect 4 game...");

	  while (winner == NO_COLOUR){
		  int isPlaced = 0;
		  switchUser(&player);
		  displayTurn(player);

		  Serial.println("Turn displayed...");
		  Serial.println("Please place a tile...");

		  while (!isPlaced){
			  TilePlacement = waitTillTilePlacemant();
			  Serial.println("Placing the tile...");
			  isPlaced = placeDisc(player, TilePlacement, tileArray);
		  }

		  Serial.println("Tile placed...");
		  Serial.println("Checking win...");

		  winner = checkBoard(player);
	  }

	  waitAndDisplayWinner(winner, tileArray);
  }
