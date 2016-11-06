#include "tile.h"
#include "constants.h"
#include "connect_4_check_win.h"
#include "Arduino.h"

//This matrix saves a copy of the connect 4 game board
int Board[ROWS][COLUMNS]; // I don't think we need this anymore.

// TODO UNTESTED does this work, and if so, does it help?
void resetMaxChips() {
  whiteMaxim = LedControl(W_DATA_PIN, W_CS_PIN, W_CLOCK_PIN, NUM_MAXIMS_PER_COLOUR);
  greenMaxim = LedControl(G_DATA_PIN, G_CS_PIN, G_CLOCK_PIN, NUM_MAXIMS_PER_COLOUR);
  whiteMaxim.clearDisplay(0);
  whiteMaxim.shutdown(0,false);
  whiteMaxim.setIntensity(0, 15);
  greenMaxim.clearDisplay(0);
  greenMaxim.shutdown(0,false);
  greenMaxim.setIntensity(0, 15);
}

/*
 * This function checks if a mechanical switch has been activated. The time
 * constant, 'DEBOUNCE_DELAY' avoids activated a false signal due to bouncing in
 * the switch
 */
bool switchToggled(unsigned long switchPin, unsigned long* lastValue, unsigned long* lastActivated){
  unsigned long now = millis();
  int currentValue = digitalRead(switchPin) == HIGH ? 1 : 0;

  if( (now - *lastActivated) < DEBOUCE_DELAY){
    return false;
  }

  if(*lastValue != currentValue){
    // inverted because it's pulled HIGH by default
    *lastValue = !currentValue;
    *lastActivated = now;
    return !currentValue;
  }

  return false;
}

/*
 * Instantiates the initial state of the switch (think of an RC capacitor)
 */
void initializeButton(unsigned long *buttonObject, unsigned long pinID){
  buttonObject[0] = pinID;
  buttonObject[1] = HIGH;
  buttonObject[2] = millis();

  //note: default value is HIGH because of the INPUT_PULLUP state
  Serial.print(pinID);
  pinMode(pinID, INPUT_PULLUP); // TODO: pretty sure we have explicit pulldown resistors tho
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
bool placeDisc(int currentPlayer, int col, Tile tileArray[][COLUMNS]){
  for(int row = ROWS-1; row >= 0; row--){
    if (tileArray[row][col].getColour() == NO_COLOUR){
      for (int r = 0; r < row; r++) {
        tileArray[r][col].setColour(currentPlayer);
        delay(50);
        tileArray[r][col].setColour(NO_COLOUR);
      }
      tileArray[row][col].setColour(currentPlayer);
      Board[row][col] = currentPlayer;
      return true;
    }
  }
  Serial.println("Try again column full");
  return false; //column full, try again
}

/*
 *   Displays which side won by turning all the tiles to the colour of the
 *   winning side. If it's a tie, the display will go blank. Is this what
 *   we want?
 */
void waitAndDisplayWinner(int currentPlayer, Tile tileArray[][COLUMNS], int winningCombo[4][2]){
  //Display all tiles in winning colour
  Serial.println("Displaying winner......");
  int currentColour = currentPlayer;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 4; j++) {
      tileArray[winningCombo[j][0]][winningCombo[j][1]].setColour(currentColour);
    }
    delay(500);
    currentColour = (currentColour == NO_COLOUR) ? currentPlayer : NO_COLOUR;
  }
  for (int r = 0; r < ROWS + ROWS/2; r++) {
    for (int c = COLUMNS-1; c >= 0; c--) {
      if (r < ROWS) {
        tileArray[r][c].setColour(currentPlayer);
      }
      if (r - 3 >= 0) {
        tileArray[r-3][c].setColour(NO_COLOUR);
      }
      delay(10);
    }
  }
}

/*
 * Infinite-loop program that does not exit until the user selects a tile.
 * Returns -1 on reset.
 */
int waitTillTilePlacemant(){
  unsigned long start = millis();
  bool val = false;                                   //Change according to button
  int col = -1;
  while(!val){
    if (col >= COLUMNS-1){
      col = -1;
      if (switchToggled(startResetButton[0], &startResetButton[1], &startResetButton[2])) {
        return RESET;
      }
    }
    col += 1;
    val = switchToggled(columnButtons[col][0], &columnButtons[col][1], &columnButtons[col][2]);
    // Check for timeout
    if (millis() - start > TIMEOUT_VALUE) {
      Serial.println("TIMEOUT!");
      return TIMEOUT;
    }
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
      Board[row][col] = NO_COLOUR;
    }
  }
  Serial.println("All tiles set to no colour.");
}

// TODO Test if this version of resetGame helps the glitches
//void resetGame(Tile tileArray[][COLUMNS]){
//  Serial.println("Resetting......");
//  resetMaxChips();
//  for(int row = 0; row < ROWS; row++){
//    for(int col = 0; col < COLUMNS; col++){
//      tileArray[row][col].m_colour = NO_COLOUR;
//      Board[row][col] = NO_COLOUR;
//    }
//  }
//  Serial.println("All tiles set to no colour.");
//}

/*
 * Sets up the pin configurations and resets the tile
 */
void setupGame(Tile tileArray[][COLUMNS]){
  for (int col = 0; col < COLUMNS; col++){
    Serial.println("Initializing buttons...");
    initializeButton(columnButtons[col], COLUMN_BUTTON_PINS[col]);
  }

  initializeButton(AIButton, AI_BUTTON_PIN);
  initializeButton(startResetButton, START_RESET_BUTTON);

  pinMode(PLAYER_G_INDICATOR_PIN, OUTPUT);
  pinMode(PLAYER_W_INDICATOR_PIN, OUTPUT);
  resetGame(tileArray);
}

// TODO UNTESTED: new arrow intro
void playIntro(Tile tileArray[][COLUMNS]) {
  resetGame(tileArray);
  
  // Each point is {row, col}
  // (0,0) is top left of display
  // These are the points in an arrow
  int pattern_pnts[][2] = {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {0, 5}, {1, 5}, {2, 5}, {1, 6}};
  int num_pnts = sizeof(pattern_pnts) / sizeof(int[2]);
  int total_delay = 500;
  Serial.println("Playing intro");

  int i = 0;
  int colour = WHITE;
  while (true) {
    int row = pattern_pnts[i][0];
    int col = pattern_pnts[i][1];
    tileArray[row][col].setColour(colour);
    ++i;
    if (i >= num_pnts) {
      i = 0;
      colour = (colour == WHITE ? GREEN : WHITE);
    }

    // We can't just do delay(total_delay) because we might miss the reset button
    // press. So we do a bunch of small delays, waking up periodically to check for
    // a button press.
    for (int t = 0; t < total_delay; t += 50) {
      delay(50);
      if (switchToggled(startResetButton[0], &startResetButton[1], &startResetButton[2])) {
        Serial.println("Intro over");
        return;
      }
    }
  }
}

//void playIntro(Tile tileArray[][COLUMNS]) {
//  return;
//  Serial.println("Playing intro");
//  while (true) {
//    for (int r = 0; r < ROWS; r++) {
//      for (int c = COLUMNS-1; c >= 0; c--) {
//        if (r % 2 == 0) {
//          tileArray[r][c].setColour(GREEN);
//          tileArray[(r + 3) % ROWS][COLUMNS - 1 - c].setColour(WHITE);
//        } else {
//          tileArray[r][COLUMNS - 1 - c].setColour(GREEN);
//          tileArray[(r + 3) % ROWS][c].setColour(WHITE);
//        }
//        delay(100);
//        if (switchToggled(startResetButton[0], &startResetButton[1], &startResetButton[2])) {
//          Serial.println("Intro over");
//          return;
//        }
//      }
//    }
//  }
//}

// TODO: Use this intro with very short delay to stress-test the display and try to cause glitches
//  void playIntro(Tile tileArray[][COLUMNS]) {
//    Serial.println("Playing intro");
//    int len = 5;
//    int fullLen = len * 2;
//    int offset = 0;
//    while (!switchToggled(startResetButton[0], &startResetButton[1], &startResetButton[2])) {
//      for (int c = 0; c < COLUMNS; c++) {
//        for (int r = 0; r < ROWS; r++) {
//          int my_id = fullLen * 10 + r - c + offset;
//          tileArray[r][c].setColour((my_id % fullLen < len) ? WHITE : GREEN);
//        }
//      }
//      offset = (offset + 1) % fullLen;
//      delay(100);
//    }
//    Serial.println("Intro over");
//  }

//    void playIntro(Tile tileArray[][COLUMNS]) {
//    Serial.println("Playing intro");
//    int len = 5;
//    int fullLen = len * 2;
//    int offset = 0;
//    while (!switchToggled(startResetButton[0], &startResetButton[1], &startResetButton[2])) {
//      unsigned long green_col = 0;
//      unsigned long white_col = 0;
//      for (int c = 0; c < COLUMNS; c++) {
//        int c_index = tileArray[0][c].getColumn();
//        for (int r = 0; r < ROWS; r++) {
//          int r_index = tileArray[r][c].getRow();
//          int my_id = fullLen * 10 + r - c + offset;
//          if (my_id % fullLen < len) {
//            white_col |= 1 << (7 - r_index);
//          } else {
//            green_col |= 1 << (7 - r_index);
//          }
//        }
//        greenMaxim.setRow(0, c_index,
//      }
//      offset = (offset + 1) % fullLen;
//      delay(100);
//    }
//    Serial.println("Intro over");
//  }

// TODO UNTESTED: timeout on unclean board.
int runGame(Tile tileArray[][COLUMNS]){
  resetGame(tileArray);
  int player = WHITE;
  int winner = NO_COLOUR;
  int TilePlacement;
  bool isReset = false;
  int winningCombo[4][2];

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      winningCombo[i][j] = 0;
    }
  }

  Serial.println("Start new Connect 4 game...");

  while (winner == NO_COLOUR && !isReset){
    int isPlaced = 0;
    switchUser(&player);
    displayTurn(player);

    Serial.println("Turn displayed...");
    Serial.println("Please place a tile...");

    while (!isPlaced || isReset ){
      TilePlacement = waitTillTilePlacemant();
      if (TilePlacement == RESET) {
        return RESET;
      }
      if (TilePlacement == TIMEOUT) {
        return TIMEOUT;
      }
      Serial.println("Placing the tile...");
      isPlaced = placeDisc(player, TilePlacement, tileArray);
    }

    Serial.println("Tile placed...");
    Serial.println("Checking win...");

    winner = checkBoard(player, winningCombo);
  }

  waitAndDisplayWinner(winner, tileArray, winningCombo);
  return GAME_FINISHED;
}
