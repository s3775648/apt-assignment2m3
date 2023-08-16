#include "LinkedList.h"
#include "TileCodes.h"
#include <iostream>
#include "menu.h"
#include "Board.h"

#define EXIT_SUCCESS    0



int main(void) {

   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;

   std::cout << TXTRED << UCIRCLE << TXTDEFAULT << std::endl;

   std::cout << TXTORANGE << USQUARE << TXTDEFAULT << std::endl;

   std::cout << TXTYELLOW << UCLOVER << TXTDEFAULT << std::endl;
   std::cout << TXTGREEN << UDIAMOND << TXTDEFAULT << std::endl;
   std::cout << TXTBLUE << USTAR_4 << TXTDEFAULT << std::endl;

   std::cout << TXTPURPLE << USTAR_6 << TXTDEFAULT << std::endl;

   Tile* tile = new Tile(CIRCLE, PURPLE);
   Tile* tile2 = new Tile(STAR_4, BLUE);
   Tile* tile3 = new Tile(DIAMOND, GREEN);
   Tile* tile4 = new Tile(SQUARE, YELLOW);
   Tile* tile5 = new Tile(STAR_6, ORANGE);
   Tile* tile6 = new Tile(CLOVER, RED);
   Tile* tile7 = new Tile(DIAMOND, GREEN);
   Tile* tile8 = new Tile(CIRCLE, PURPLE);


   std::cout << std::endl;
   std::cout << tile->getTileAsSymbol() << std::endl;
   std::cout << tile2->getTileAsSymbol() << std::endl;
   std::cout << tile3->getTileAsSymbol() << std::endl;
   std::cout << tile4->getTileAsSymbol() << std::endl;
   std::cout << tile5->getTileAsSymbol() << std::endl;
   std::cout << tile6->getTileAsSymbol() << std::endl;
   std::cout << tile7->getTileAsSymbol() << std::endl;
   std::cout << tile8->getTileAsSymbol() << std::endl;

   Menu menu;

   menu.printMenu();
   std::cout << std::endl;

   std::cout << "Goodbye" << std::endl;


   return EXIT_SUCCESS;
}
