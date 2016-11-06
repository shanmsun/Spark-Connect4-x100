#include "tile.h"
#include "LedControl.h"
#include "constants.h"

Tile::Tile(){
  m_colour = NO_COLOUR;
  m_coord_is_set = false;
}

Tile::Tile(int colour){
  m_colour = colour;
  m_coord_is_set = false;
}

/*
 * This sets the colour of the class based on the 2 flags
 * Afterwards, it sends the changes to the Maxim
 */
void Tile::setColour(int colour){
  bool isGreen = false;
  bool isWhite = false;

  char status[100];
  sprintf(status, "Row: %d - Col :%d", m_row, m_column);
  Serial.println(status);

  if (colour == GREEN){
    isGreen = true;
    Serial.print("Green - ");
  } else if (colour == WHITE){
    isWhite = true;
    Serial.print("White - ");
  }

  m_colour = colour;

  // transposed because the dig and segs are transposed;
  whiteMaxim.setLed(0, m_column, m_row, isWhite);
  //delay(5);
  greenMaxim.setLed(0, m_column, m_row, isGreen);

  return;
}

/*
 * Assigns each instantiated Tile class to a co-ordinate system
 */
void Tile::setCoordinates(int row, int column){
  if(!m_coord_is_set){
    m_column = column;
    m_row = row;
  }

  m_coord_is_set = true;
}

int Tile::getColumn(){
  return m_column;
}

int Tile::getRow(){
  return m_row;
}

int Tile::getColour(){
  return m_colour;
}
