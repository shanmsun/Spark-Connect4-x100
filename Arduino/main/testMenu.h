#ifndef TESTMENU_H
#define TESTMENU_H
void printHelp();
void runTestMenu();
void printTestMenu();
void parseResponse();
void testBoard();
void testRow(int row);
void testColumn(int column);
void testTile(int row, int column);
int testSwitch(unsigned long *buttonObj);
void testSwitchResult(bool isMultiple, bool isReset);
void turnOnGreen();
void turnOnWhite();

#endif
