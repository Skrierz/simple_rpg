#pragma once

#include "consoleColor.h"

//Constants
const int rowsCount = 15;
const int columnCount = 35;

const unsigned char CellSymbol_Empty    = ' ';
const unsigned char CellSymbol_Wall     = '#';
const unsigned char CellSymbol_Hero     = 'h';
const unsigned char CellSymbol_Exit     = 'e';
const unsigned char CellSymbol_Orc      = 'o';
const unsigned char CellSymbol_Skeleton = 's';
const unsigned char CellSymbol_Ogre     = 'O';
const unsigned char CellSymbol_Heart    = 'H';
const unsigned char CellSymbol_Stick	= '1';
const unsigned char CellSymbol_Club		= '2';
const unsigned char CellSymbol_Spear	= '3';
const unsigned char CellSymbol_Saber	= '4';
const unsigned char CellSymbol_Flail    = '5';
const unsigned char CellSymbol_Scythe   = '6';
const unsigned char CellSymbol_Claymore = '7';
const unsigned char CellSymbol_Fog      = 'F';


const unsigned char levelData0[rowsCount][columnCount + 1] =
{
	"###################################",
	"#   #H##      o           s       #",
	"# # o 4#o############## ######### #",
	"# ###### #   # #5H s  # ##s## H # #",
	"#  s       # # ###### # #s7   #s#6#",
	"###### # ### #      # # ##s##   # #",
	"##  o# # # # #### #2#   #####H# # #",
	"#H #   # # o    # ##H######s#   # #",
	"######## # ####         # H # # #s#",
	"#  3#    #      ####### # # #   # #",
	"# ### #### ######   o   # #   # H #",
	"#  o       #      ####### #########",
	"############ ######   #1# # s #   #",
	"#h                  #   #   #s  #O#",
	"#################################e#",

};

unsigned char GetRenderCellSymbol(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
		case CellSymbol_Empty:	  return ' ';
		case CellSymbol_Wall:	  return 177;
		case CellSymbol_Hero:	  return 2;
		case CellSymbol_Orc:      return 2;
		case CellSymbol_Skeleton: return 2;
		case CellSymbol_Ogre:     return 2;	
		case CellSymbol_Stick:	  return 47;
		case CellSymbol_Club:	  return 33;
		case CellSymbol_Spear:    return 24;
		case CellSymbol_Saber:    return 108;
		case CellSymbol_Exit:     return 178;
		case CellSymbol_Heart:    return 3;
		case CellSymbol_Flail:    return 64;
		case CellSymbol_Scythe:   return 251;
		case CellSymbol_Claymore: return 197;
		case CellSymbol_Fog:      return 178;
	}

	return '?';
}

ConsoleColor GetRenderCellSymbolColor(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
		case CellSymbol_Empty:	  return ConsoleColor_Black;
		case CellSymbol_Wall:	  return ConsoleColor_White;
		case CellSymbol_Hero:	  return ConsoleColor_Yellow;
		case CellSymbol_Orc:      return ConsoleColor_Green;
		case CellSymbol_Skeleton: return ConsoleColor_White;
		case CellSymbol_Ogre:     return ConsoleColor_DarkRed;
		case CellSymbol_Stick:	  return ConsoleColor_DarkYellow;
		case CellSymbol_Club:	  return ConsoleColor_DarkRed;
		case CellSymbol_Spear:    return ConsoleColor_DarkCyan;
		case CellSymbol_Saber:    return ConsoleColor_Cyan;
		case CellSymbol_Exit:     return ConsoleColor_DarkRed;
		case CellSymbol_Heart:    return ConsoleColor_Red;
		case CellSymbol_Fog:      return ConsoleColor_Gray;
	}

	return ConsoleColor_Gray;
}