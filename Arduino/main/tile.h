#ifndef TILE_H
#define TILE_H
  class Tile{
    private:
      bool m_coord_is_set; 
      int m_row;
      int m_column; 
      int m_colour; 

    public:
      Tile();
      Tile(int colour); 
      void setColour(int colour);
      void setCoordinates(int row, int column); 
      int getColumn();
      int getRow();
  };

#endif
