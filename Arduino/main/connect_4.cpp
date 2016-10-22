#include "tile.h"
#include "constants.h"
#include "connect_4_check_win.h"
#include "Arduino.h"

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
   * Instantiates the initial state of the switch (think of an RC capacitor)
   */
  void initializeButton(int *buttonObject, int pinID){
    buttonObject[0] = pinID;
    buttonObject[1] = HIGH;
    buttonObject[2] = (int) millis();

    //note: default value is HIGH because of the INPUT_PULLUP state
    pinMode(pinID, INPUT_PULLUP);
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
  	  digitalWrite(PLAYER_W_INDICATOR_PIN, HIGH);
  	  digitalWrite(PLAYER_G_INDICATOR_PIN, LOW);
	  } else{
		  digitalWrite(PLAYER_G_INDICATOR_PIN, HIGH);
		  digitalWrite(PLAYER_W_INDICATOR_PIN, LOW);
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

  /*
   * Sets up the pin configurations and resets the tile
   */
  void setupGame(Tile tileArray[][COLUMNS]){
	  for (int col = 0; col < COLUMNS; col++){
      initializeButton(columnButtons[col], COLUMN_BUTTON_PINS[col]);
	  }

    initializeButton(AIButton, AI_BUTTON_PIN);
    initializeButton(startResetButton, START_RESET_BUTTON);

	  pinMode(PLAYER_G_INDICATOR_PIN, OUTPUT);
	  pinMode(PLAYER_W_INDICATOR_PIN, OUTPUT);
	  resetGame(tileArray);
  }

  void runGame(Tile tileArray[][COLUMNS]){
    resetGame(tileArray);
    int player = WHITE;
	  int winner = NO_COLOUR;
    int TilePlacement;
    bool isReset = false;

	  Serial.println("Start new Connect 4 game...");

	  while (winner == NO_COLOUR || isReset){
		  int isPlaced = 0;
		  switchUser(&player);
		  displayTurn(player);

		  Serial.println("Turn displayed...");
		  Serial.println("Please place a tile...");

		  while (!isPlaced || isReset ){
			  TilePlacement = waitTillTilePlacemant();
        isReset = switchToggled(startResetButton[0], &startResetButton[1], &startResetButton[2]);
			  Serial.println("Placing the tile...");
			  isPlaced = placeDisc(player, TilePlacement, tileArray);
		  }

		  Serial.println("Tile placed...");
		  Serial.println("Checking win...");

		  winner = checkBoard(player);
	  }

    if(!isReset){
      waitAndDisplayWinner(winner, tileArray);
    }
  }
