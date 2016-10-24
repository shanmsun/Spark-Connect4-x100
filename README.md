# Spark-Connect4-x100
The 1st display of 2016-17 built by the Spark Exec Team and Sparkers. It is a magnified version of Connect 4

## About
The display is a giagantic and electronic version of Connect 4. Instead of physically dropping discs, users can simply toggle the button corrsponding to a column to drop the disc.

## Workshop- i.e. "Marathon Building Session"
This display will be built over the weekend and be completed within 2 weekend session (~10 hours). In this workshop, the exec team and volunteers/passion individual will stop by and race to build this display! The aim is to get the display out by October 23rd.   

## Code

> Issues/Important Info:
> - the board is configured to be based of the 4th quadrant (i.e. SE) in the X-Y plane; the bottom right would be 6, 7 (not zero-indexed)
> - on the MAXIM (hardware-side), the wiring is not zero-indexed; on the software-side, everything is zero-indexed. As a result, anything that is zero-index has to be shifted by 1
> - in addition, one of the segments was missed (A-B-C-E-F-G); anything past C needs to get get shifted by 2;
> - the above points **have been fixed with a helper library**. 

The code can be divided up into lots of chunks. Here is a basic breakdown
```c
 - constants.h = Shares any constants/flags and external variables that will need to be shared across the entire code
 - IOPins.h = a pin mapout of what belongs to which Arduino port
 - testMenu.h & testMenu.cpp = an in-built diagnostic tool to help test the circuit 
 - connect_4.h & connect_4.cpp = executes the connect 4 sequence
 - connect_4_check_win.h & connect_4_check_win.cpp = a algorithm to check if a player has won  

```

```c
 testMenu.h:
  void runTestMenu();
  void printTestMenu();
  void parseResponse();
  void testBoard();
  void testRow(int row);
  void testColumn(int column);
  void testTile(int row, int column);
```
```c
 connect_4.h:
  bool switchToggled(int switchPin, int* lastValue, int* lastActivated);
  void runGame(Tile tileArray[][COLUMNS]);
  void displayTurn(int currentPlayer);
  void setupGame(Tile tileArray[][COLUMNS]);
  void resetGame(Tile tileArray[][COLUMNS]);
  int waitTillTilePlacemant();
  void waitAndDisplayWinner(int currentPlayer, Tile tileArray[][COLUMNS]);
  void switchUser(int *currentPlayer);
  int placeDisc(int col, Tile tileArray[][COLUMNS]);
```
```c
 connect_4_check_wins.h:
  int checkBoard(int currentPlayer);
  int checkRow(int currentPlayer, int row);
  int checkColumn(int currentPlayer, int col);
  int checkDiagonalLeftUp(int currentPlayer, int row, int col);
  int checkDiagonalRightUp(int currentPlayer, int row, int col);
```

## Features

## Design
The display was built by a team of dedicated mechanical execs through iteration over Solidworks

## Credits
 - Credits go to: Sandro Young, Shanmeng Sun, Wenyi Yin, Jason Wong, Alessandro Sciarra, Helen Meng, James Chen, Janice Zhou, Chokpisit Kasemphaibulsuk & William Bi 
