#ifndef TILE_H
#define TILE_H
  class Tile{
    private:
      bool m_green;
      bool m_white;
      bool m_coord_is_set; 
      int m_row;
      int m_column; 

    public:
      Tile();
      Tile(bool green, bool white); 
      void setColour(bool green, bool white);
      void setCoordinates(int row, int column); 
      int getColumn();
      int getRow();
  };

#endif
