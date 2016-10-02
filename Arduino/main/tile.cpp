#include "tile.h"
#include "LedControl.h"
#include "constants.h"

Tile::Tile(){
  setColour(false, false);
  m_coord_is_set = false; 
}

Tile::Tile(bool green, bool white){
  setColour(green, white);
  m_coord_is_set = false;  
}

/*
 * This sets the colour of the class based on the 2 flags
 * Afterwards, it sends the changes to the Maxim
 */
void Tile::setColour(bool green, bool white){
  if(green && white)
    return; 
  
  m_green = green;
  m_white = white;

  whiteMaxim.setLed(0, m_row, m_column, m_white);
  greenMaxim.setLed(0, m_row, m_column, m_green);

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

