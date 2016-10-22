#include "tile.h"
#include "constants.h"
#include "connect_4_check_win.h"
#include "Arduino.h"

int BUTTON_pin[1][COLUMNS];
  /*
  * This function checks if a mechanical switch has been activated. The time constant, 'DEBOUNCE_DELAY'
  * avoids activated a false signal due to bouncing in the switch
  */
  bool switchToggled(int switchPin, int* lastValue, int* lastActivated){
    int now = millis();
    int currentValue = digitalRead(switchPin) == HIGH ? 1 : 0;

    if( (now - *lastActivated) < DEBOUCE_DELAY){
      return false;
    }

    if(*lastValue != currentValue){
      *lastValue = currentValue;
      *lastActivated = now;
      return currentValue;
    }
  }

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
		  val = switchToggled(columnButtons[0][col], &columnButtons[1][col], &columnButtons[2][col]);
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
      columnButtons[0][col] = COLUMN_BUTTONS[col];
      columnButtons[1][col] = (int) millis();
      columnButtons[2][col] = HIGH;

		  pinMode(COLUMN_BUTTONS[col], INPUT_PULLUP);
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
