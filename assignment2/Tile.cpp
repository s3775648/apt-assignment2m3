#include "Tile.h"



Tile::Tile(Shape shape, Colour colour) {

   this->shape = shape;
   this->colour = colour;

}


bool Tile::isSameTile(Tile* other) {

   bool isSame = false;

   if (shape == other->getShape() && colour == other->getColour()) {
      isSame = true;
   }
   return isSame;
}


std::string Tile::getTileAsSymbol() {

   std::string symbol;

   // cycle through colors
   if (this->colour == RED) {
      symbol = TXTRED;
   }
   else if (this->colour == ORANGE) {
      symbol = TXTORANGE;
   }
   else if (this->colour == YELLOW) {
      symbol = TXTYELLOW;
   }
   else if (this->colour == GREEN) {
      symbol = TXTGREEN;
   }
   else if (this->colour == BLUE) {
      symbol = TXTBLUE;
   }
   else {
      symbol = TXTPURPLE;
   }

   // cycle through shapes
   if (this->shape == CIRCLE) {
      symbol.append(UCIRCLE);
   }
   else if (this->shape == STAR_4) {
      symbol.append(USTAR_4);
   }
   else if (this->shape == DIAMOND) {
      symbol.append(UDIAMOND);
   }
   else if (this->shape == SQUARE) {
      symbol.append(USQUARE);
   }
   else if (this->shape == STAR_6) {
      symbol.append(USTAR_6);
   }
   else {
      symbol.append(UCLOVER);
   }

   // Remove colour component
   symbol.append(TXTDEFAULT);

   return symbol;
}


Shape Tile::getShape() {
   return this->shape;
}


Colour Tile::getColour() {
   return this->colour;
}



