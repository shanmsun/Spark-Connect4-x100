#ifndef TILE_H
#define TILE_H
  class Tile{
    private:
      bool m_green;
      bool m_white;

    public:
      Tile();
      Tile(bool green, bool white); 
      void setColour(bool green, bool white); 
  };

#endif
