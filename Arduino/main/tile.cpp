#include "tile.h"

Tile::Tile(){
  setColour(false, false);
}

Tile::Tile(bool green, bool white){
  setColour(green, white); 
}

void Tile::setColour(bool green, bool white){
  if(green && white)
    return; 
  
  m_green = green;
  m_white = white;

  return;
}

