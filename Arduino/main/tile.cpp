#include "tile.h"
#include "LedControl.h"
#include "constants.h"

Tile::Tile(){
  setColour(NO_COLOUR);
  m_coord_is_set = false;
}

Tile::Tile(int colour){
  setColour(colour);
  m_coord_is_set = false;
}

/*
 * This sets the colour of the class based on the 2 flags
 * Afterwards, it sends the changes to the Maxim
 */
void Tile::setColour(int colour){
  bool isGreen = false;
  bool isWhite = false;

  if (colour == GREEN){
    isGreen = true;
  } else if (colour == WHITE){
    isWhite = true;
  }

  m_colour = colour;

  whiteMaxim.setLed(0, m_row, m_column, isWhite);
  greenMaxim.setLed(0, m_row, m_column, isGreen);

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
