#include "tile.h"
#include "constants.h"
#include "connect_4_check_win.h"
#include "Arduino.h"
  
  //This matrix saves a copy of the connect 4 game board
  int Board[ROWS][COLUMNS];
  
  /*
  * This function checks if a mechanical switch has been activated. The time constant, 'DEBOUNCE_DELAY'
  * avoids activated a false signal due to bouncing in the switch
  */
  bool switchToggled(int switchPin, int *lastValue, int *lastActivated){
    int now = (int) millis();
    int currentValue = digitalRead(switchPin) == HIGH ? 1 : 0;

	// time interval too small, don't check 
    if( (now - *lastActivated) < DEBOUNCE_DELAY){
      return false;
    }

	// we only care if the button is being unpressed
    if ((*lastValue == LOW) && (currentValue == HIGH)){
      // inverted because it's pulled HIGH by default
      *lastValue = currentValue;
      *lastActivated = now;
      return true;
    }
	
	// either button is being pressed or nothing happened. Save the value in lastValue
	*lastValue = currentValue;
	return false;
  }

  /*
   * Instantiates the initial state of the switch (think of an RC capacitor)
   */
  void initializeButton(int *buttonObject, int pinID){
    buttonObject[0] = pinID;
    buttonObject[1] = HIGH;
    buttonObject[2] = (int) millis();

    //note: default value is HIGH because of the INPUT_PULLUP state
    Serial.print(pinID);
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
	  for(int row = ROWS-1; row >= 0; row--){
		  if (tileArray[row][col].getColour() == NO_COLOUR){
			  tileArray[row][col].setColour(currentPlayer);
        Board[row][col] = currentPlayer;
			  return 1;
		  }
	  }
	  Serial.println("\tTry again column full");
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
    for(int row = 0; row >ROWS; row++){
      for(int col = 0; col < COLUMNS; col++){
            Tile tile = tileArray[row][col];
            tile.setColour(Board[row][col]);
          }
    }
	  Serial.println("Wait until restarted");
  }

  /*
   * Resets the game
   */
  void resetGame(Tile tileArray[][COLUMNS]){
    Serial.println("Resetting......");
    for(int row = 0; row < ROWS; row++){
          for(int col = 0; col < COLUMNS; col++){
            tileArray[row][col].setColour(NO_COLOUR);
            Board[row][col] = NO_COLOUR;
          }
        }
    Serial.println("All tiles set to no colour.");
  }

  /*
   * Sets up the pin configurations and resets the tile
   */
  void setupGame(Tile tileArray[][COLUMNS]){
	  for (int col = 0; col < COLUMNS; col++){
      Serial.println("Initializing buttons...");
      initializeButton(columnButtons[col], COLUMN_BUTTON_PINS[col]);
	  }

    initializeButton(AIButton, AI_BUTTON_PIN);
    initializeButton(startResetButton, START_RESET_BUTTON_PIN);

	  pinMode(PLAYER_G_INDICATOR_PIN, OUTPUT);
	  pinMode(PLAYER_W_INDICATOR_PIN, OUTPUT);
	  resetGame(tileArray);
  }

  void runGame(Tile tileArray[][COLUMNS]){
	// define some variables
    int player, winner, lastPlayed, col, isPlaced;
	// begin the game
    START:
	// reset board
    resetGame(tileArray);
	player = WHITE;
	winner = NO_COLOUR;
	
	Serial.println("Start new Connect 4 game...");

	// while there is no winner, loop
	while (winner == NO_COLOUR){
	  // no button has been pressed
	  isPlaced = 0;
	  // display which player's turn it is
	  displayTurn(player);
      Serial.print("Current player: ");
      Serial.println(player);

	  Serial.println("\tPlease place a tile...");
      // poll all buttons until one is pressed
	  while (!isPlaced){
		// check the reset button. If pressed, return to beginning of function
		if (switchToggled(startResetButton[0], &startResetButton[1], &startResetButton[2])) {
			goto START;
		}
		// otherwise sweep the column buttons once
		for (col = 0; col < COLUMNS; col++) {
			// if button pressed, place the tile
			if (switchToggled(columnButtons[col][0], &columnButtons[col][1], &columnButtons[col][2])) {
				Serial.println("\tPlacing the tile...");
				// if the column is full, isPlaced will be 0, we won't exit the inner while loop, and it'll
				// still be this player's turn
				isPlaced = placeDisc(player, col, tileArray);
				break; // break out of for loop
			}
			// reduces glitchiness
	        delay(5);
		} // for col       
	  } // while !isPlaced
	  
	  // check for a win
	  Serial.println("\tTile placed...");
	  Serial.println("\tChecking win...");
	  winner = checkBoard(player);
	  
	  // switch the player and go back to the main loop
      switchUser(&player);
      delay(300);
	} // while !winner
	// display the winner and exit
    waitAndDisplayWinner(winner, tileArray);
  }

  void easterEgg(){
    //what is a cool easter egg? 
  }

