#include "pch.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <ctype.h>

#include "consoleColor.h"
#include "level.h"
#include "weaponType.h"
#include "weaponData.h"
#include "unitData.h"
#include "unitType.h"

//Constants
const int maxUnitsCount = 35;
const int weapons = 12;

//Logics variables
HANDLE consoleHandle = 0;
bool isGameActive = true;

int currentLevel = 0;
int heroHP = GetUnitDefaultHealth(UnitType_Hero);
WeaponType heroWpn = GetUnitDefaultWeapon(UnitType_Hero);

unsigned char levelData[rowsCount][columnCount];
unsigned char fogOfWar[rowsCount][columnCount];

UnitData unitsData[maxUnitsCount];
WeaponData weaponData[weapons];
int unitsCount = 0;
int heroIndex = 0;
int ogreIndex = 0;

char stringBuffer[200];
char output[1000];

//Functions
void SetupSystem()
{
	srand(time(0));

	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Hide console cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void Initialize(int heroHealth = GetUnitDefaultHealth(UnitType_Hero), WeaponType heroWeapon = GetUnitDefaultWeapon(UnitType_Hero))
{
	//Initialize weapons
	for (int w = 0; w <= weapons + 1; w++)
	{
		weaponData[w].type = WeaponType(w);
		weaponData[w].min_dmg = GetWeaponMinDamage(WeaponType(w));
	}

	//Initialize fog of war
	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			fogOfWar[i][j] = CellSymbol_Fog;
		}
	}

	memset(unitsData, 0, sizeof(unitsData));
	unitsCount = 0;

	//Load level
	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{


			unsigned char cellSymbol = levelsData[currentLevel][i][j];

			levelData[i][j] = cellSymbol;

			switch (cellSymbol)
			{
				case CellSymbol_Ogre:
				{
					ogreIndex = unitsCount;
					break;
				}
					
					
			}

			switch (cellSymbol)
			{
				case CellSymbol_Hero:
					heroIndex = unitsCount;
					fogOfWar[i][j] = ' ';
					fogOfWar[i - 1][j] = ' ';
					fogOfWar[i + 1][j] = ' ';
					fogOfWar[i][j - 1] = ' ';
					fogOfWar[i][j + 1] = ' ';
					fogOfWar[i - 1][j - 1] = ' ';
					fogOfWar[i + 1][j - 1] = ' ';
					fogOfWar[i - 1][j + 1] = ' ';
					fogOfWar[i + 1][j + 1] = ' ';

				case CellSymbol_Orc:
				case CellSymbol_Skeleton:
				case CellSymbol_Ogre:
				case CellSymbol_Werewolf:
				case CellSymbol_Vampire:
				case CellSymbol_GreenOrc:
				case CellSymbol_Troll:
				case CellSymbol_ArmoredSkeleton:
				case CellSymbol_Zombie:
				{
					UnitType unitType = GetUnitTypeFromCell(cellSymbol);
					unitsData[unitsCount].type = unitType;
					unitsData[unitsCount].row = i;
					unitsData[unitsCount].column = j;
					unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
					unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
					unitsData[unitsCount].savedSymbol = ' ';
					unitsCount++;

					break;
				}
			}

			//Set hero hp and weapon if it isn't first level
			if (currentLevel > 0)
			{
				unitsData[heroIndex].weapon = heroWeapon;
				unitsData[heroIndex].health = heroHealth;
			}
		}
	}
}

void Render()
{
	//Move console cursore to (0,0)
	COORD cursoreCord;
	cursoreCord.X = 0;
	cursoreCord.Y = 0;
	SetConsoleCursorPosition(consoleHandle, cursoreCord);

	//Draw game title
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_DarkYellow);
	printf("\tCRAPPY DUNGEONS");

	//Draw hero HP
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Red);
	printf("\n\n\tHP:");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("%i\t", unitsData[heroIndex].health);

	//Draw hero weapon
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_DarkCyan);
	printf("\tWeapon:");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("%s", GetWeaponName(unitsData[heroIndex].weapon));
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Gray);
	printf("(Dmg: %i - %i)\t\t\t\t\t\t", GetWeaponMinDamage(unitsData[heroIndex].weapon), GetWeaponMaxDamage(unitsData[heroIndex].weapon));

	//Draw level
	printf("\n\n\t");
	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			unsigned char cellSymbol = levelData[i][j];

			unsigned char renderCellSymbol = GetRenderCellSymbol(cellSymbol);
			ConsoleColor cellColor = GetRenderCellSymbolColor(cellSymbol);

			//Draw fog of war
			if (fogOfWar[i][j] == CellSymbol_Fog)
			{
				SetConsoleTextAttribute(consoleHandle, ConsoleColor_Gray);
				printf("%c", GetRenderCellSymbol(fogOfWar[i][j]));
			}
			else
			{
				SetConsoleTextAttribute(consoleHandle, cellColor);
				printf("%c", renderCellSymbol);
			}
		}
		printf("\n\t");
	}

	//Draw output
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Yellow);
	printf(output);
}

void MoveUnitTo(UnitData* pointerToUnitData, int row, int column)
{
	//Ignore dead units
	if (pointerToUnitData->health <= 0)
	{
		return;
	}

	unsigned char unitSymbol = levelData[pointerToUnitData->row][pointerToUnitData->column];
	unsigned char destinationCellSymbol = levelData[row][column];
	bool canMoveToCell = false;
	bool saveSymbol = false;

	//All unit actions
	switch (destinationCellSymbol)
	{
		//Empty cell
		case CellSymbol_Empty:
		{
			canMoveToCell = true;
			break;
		}

		//Units cells
		case CellSymbol_Hero:
		case CellSymbol_Orc:
		case CellSymbol_Skeleton:
		case CellSymbol_Ogre:
		case CellSymbol_Werewolf:
		case CellSymbol_Vampire:
		case CellSymbol_GreenOrc:
		case CellSymbol_Troll:
		case CellSymbol_ArmoredSkeleton:
		case CellSymbol_Zombie:
		{
			//U CANT HIT THE OGRE!!!
			//Except you are a Hero
			if ((GetUnitTypeFromCell(destinationCellSymbol) == UnitType_Ogre) && (pointerToUnitData->type != UnitType_Hero))
			{
				break;
			}
			UnitType destinationUnitType = GetUnitTypeFromCell(destinationCellSymbol);

			//If destination unit have different type
			if (pointerToUnitData->type != destinationUnitType)
			{
				//Find enemy unit struct
				for (int u = 0; u < unitsCount; u++)
				{
					//Ignore dead units
					if (unitsData[u].health <= 0)
					{
						continue;
					}
					

					if (unitsData[u].row == row && unitsData[u].column == column)
					{
						//Calculate weapon damage
						int damage = GetWeaponDamage(pointerToUnitData->weapon);

						//Deal damage
						unitsData[u].health = unitsData[u].health - damage;

						//Save info
						sprintf_s(stringBuffer, "\n\t%s dealt %i damage to %s\t\t\t\t\t\t", GetUnitName(pointerToUnitData->type), damage, GetUnitName(destinationUnitType));
						strcat_s(output, stringBuffer);

						//If enemy unit die
						if (unitsData[u].health <= 0.0f)
						{
							//Save info
							sprintf_s(stringBuffer, "\n\t%s died\t\t\t\t\t\t", GetUnitName(destinationUnitType));
							strcat_s(output, stringBuffer);

							//If there was saved symbol
							if (unitsData[u].savedSymbol)
							{
								levelData[row][column] = unitsData[u].savedSymbol;
							}
							else
							{
								levelData[row][column] = CellSymbol_Empty;
							}
						}

						break;
					}
				}
			}
			break;
		}

		// Useless cells (e.g. hearts/weapon)
		case CellSymbol_Stick:
		case CellSymbol_Club:
		case CellSymbol_Spear:
		case CellSymbol_Saber:
		case CellSymbol_Heart:
		case CellSymbol_Flail:
		case CellSymbol_Scythe:
		case CellSymbol_Claymore:
		case CellSymbol_Axe:
		case CellSymbol_Crossbow:
		case CellSymbol_Slingshot:
		case CellSymbol_Mace:
		{
			canMoveToCell = true;
			saveSymbol = true;
			break;
		}
	}

	//Only hero actions
	if (pointerToUnitData->type == UnitType_Hero)
	{
		//Hero pickup all items
		saveSymbol = false;

		switch (destinationCellSymbol)
		{
			//Weapon Cell
			case CellSymbol_Stick:
			case CellSymbol_Club:
			case CellSymbol_Spear:
			case CellSymbol_Saber:
			case CellSymbol_Flail:
			case CellSymbol_Scythe:
			case CellSymbol_Claymore:
			case CellSymbol_Axe:
			case CellSymbol_Crossbow:
			case CellSymbol_Slingshot:
			case CellSymbol_Mace:
			{
				canMoveToCell = true;

				WeaponType weaponType = GetWeaponTypeFromCell(destinationCellSymbol);
				if (unitsData[heroIndex].weapon < weaponType)
				{
					unitsData[heroIndex].weapon = weaponType;

					//Save info
					sprintf_s(stringBuffer, "\n\t%s found %s\t\t\t\t\t\t", GetUnitName(pointerToUnitData->type), GetWeaponName(pointerToUnitData->weapon));
					strcat_s(output, stringBuffer);

				}

				break;
			}

			//Heart cell
			case CellSymbol_Heart:
			{
				canMoveToCell = true;
				if (unitsData[heroIndex].health <= GetUnitDefaultHealth(unitsData[heroIndex].type) - 100)
				{
					//Save info
					sprintf_s(stringBuffer, "\n\t%s healed from %i to %i\t\t\t\t\t\t", GetUnitName(pointerToUnitData->type), pointerToUnitData->health, pointerToUnitData->health + 100);
					strcat_s(output, stringBuffer);

					unitsData[heroIndex].health += 100;
				}
				else
				{
					//Save info
					sprintf_s(stringBuffer, "\n\t%s healed from %i to %i\t\t\t\t\t\t", GetUnitName(pointerToUnitData->type), pointerToUnitData->health, GetUnitDefaultHealth(unitsData[heroIndex].type));
					strcat_s(output, stringBuffer);

					unitsData[heroIndex].health = GetUnitDefaultHealth(unitsData[heroIndex].type);
				}
				
				break;
			}

			//Exit cell
			case CellSymbol_Exit:
			{
				if (currentLevel < levels - 1)
				{
					currentLevel++;
					heroHP = pointerToUnitData->health;
					heroWpn = pointerToUnitData->weapon;
					Initialize(heroHP, heroWpn);
				}
				else
				{
					isGameActive = false;
				}
				break;
			}
		}

		//Decrease fog of war
		bool upperCellsIsFog = false;
		bool midCellsIsFog = false;
		bool lowerCellsIsFog = false;
		if (canMoveToCell)
		{
			upperCellsIsFog = ((fogOfWar[row - 1][column] == 'F') || (fogOfWar[row - 1][column - 1] == 'F') || (fogOfWar[row - 1][column + 1] == 'F'));
			midCellsIsFog = ((fogOfWar[row][column] == 'F') || (fogOfWar[row][column - 1] == 'F') || (fogOfWar[row][column + 1] == 'F'));
			lowerCellsIsFog = ((fogOfWar[row + 1][column] == 'F') || (fogOfWar[row + 1][column - 1] == 'F') || (fogOfWar[row + 1][column + 1] == 'F'));

			//Heal Hero if fog was decreased
			if (upperCellsIsFog || midCellsIsFog || lowerCellsIsFog)
			{
				if (unitsData[heroIndex].health < GetUnitDefaultHealth(UnitType_Hero))
				{
					unitsData[heroIndex].health++;
				}
				fogOfWar[row - 1][column] = ' ';
				fogOfWar[row + 1][column] = ' ';
				fogOfWar[row][column - 1] = ' ';
				fogOfWar[row][column + 1] = ' ';
				fogOfWar[row - 1][column - 1] = ' ';
				fogOfWar[row + 1][column - 1] = ' ';
				fogOfWar[row - 1][column + 1] = ' ';
				fogOfWar[row + 1][column + 1] = ' ';
			}
		}
	}

	if (canMoveToCell)
	{
		//Remove unit symbol from previous position
		if (pointerToUnitData->savedSymbol != ' ')
		{
			levelData[pointerToUnitData->row][pointerToUnitData->column] = pointerToUnitData->savedSymbol;
			pointerToUnitData->savedSymbol = ' ';
		}
		else
		{
			levelData[pointerToUnitData->row][pointerToUnitData->column] = CellSymbol_Empty;
		}

		//Save symbol
		if (saveSymbol)
		{
			pointerToUnitData->savedSymbol = destinationCellSymbol;
		}

		//Set new unit position
		pointerToUnitData->row = row;
		pointerToUnitData->column = column;

		//Set unit symbol to new position
		levelData[pointerToUnitData->row][pointerToUnitData->column] = unitSymbol;
	}
}

void UpdateAI()
{
	//Pass all units
	for (int u = 0; u < unitsCount; u++)
	{
		//Ignote hero
		if (u == heroIndex)
		{
			continue;
		}

		//Ignore dead units
		if (unitsData[u].health <= 0)
		{
			continue;
		}

		//Distance to hero
		int distanceToHeroI = abs(unitsData[heroIndex].row - unitsData[u].row);
		int distanceToHeroJ = abs(unitsData[heroIndex].column - unitsData[u].column);

		//If hero nearby
		if ((distanceToHeroI + distanceToHeroJ) == 1)
		{
			//Attack hero
			MoveUnitTo(&unitsData[u], unitsData[heroIndex].row, unitsData[heroIndex].column);
		}
		else
		{
			//Ogre must not move
			if (GetUnitName(unitsData[u].type) != "Ogre")
			{
				//Random move
				switch (rand() % 4)
				{
				case 0:
				{
					MoveUnitTo(&unitsData[u], unitsData[u].row - 1, unitsData[u].column);
					break;
				}

				case 1:
				{
					MoveUnitTo(&unitsData[u], unitsData[u].row + 1, unitsData[u].column);
					break;
				}

				case 2:
				{
					MoveUnitTo(&unitsData[u], unitsData[u].row, unitsData[u].column - 1);
					break;
				}

				case 3:
				{
					MoveUnitTo(&unitsData[u], unitsData[u].row, unitsData[u].column + 1);
					break;
				}
				}
			}
		}
	}
}

void Update()
{
	bool trashInput = false;

	unsigned char inputChar = _getch();
	inputChar = tolower(inputChar);

	//Zeroing output
	memset(output, 0, sizeof(output));

	switch (inputChar)
	{
		//Up
		case 'w':
		{
			MoveUnitTo(&unitsData[heroIndex], unitsData[heroIndex].row - 1, unitsData[heroIndex].column);
			break;
		}

		//Down
		case 's':
		{
			MoveUnitTo(&unitsData[heroIndex], unitsData[heroIndex].row + 1, unitsData[heroIndex].column);
			break;
		}

		//Right
		case 'd':
		{
			MoveUnitTo(&unitsData[heroIndex], unitsData[heroIndex].row, unitsData[heroIndex].column + 1);
			break;
		}

		//Left
		case 'a':
		{
			MoveUnitTo(&unitsData[heroIndex], unitsData[heroIndex].row, unitsData[heroIndex].column - 1);
			break;
		}

		//Restart level
		case 'r':
		{

			Initialize(heroHP, heroWpn);
			break;
		}

		default:
			trashInput = true;
			break;
	}
	
	//Don't register trash input
	if (trashInput)
		return;

	//AI turn
	UpdateAI();

	//Hero death
	if (unitsData[heroIndex].health <= 0)
	{
		isGameActive = false;

		system("cls");
		printf("\n\tYou died\n\tPress 'r' for restart");
		char button = _getch();
		if (tolower(button) == 'r')
		{
			system("cls");
			Initialize(heroHP, heroWpn);
			isGameActive = true;
		}

	}


	//Clear all printed output
	sprintf_s(stringBuffer, "\n\t\t\t\t\t\t\t\t\t\n\t\t\t\t\t\t\t\t\t\n\t\t\t\t\t\t\t\t\t\n\t\t\t\t\t\t\t\t\t\n\t\t\t\t\t\t\t\t\t");
	strcat_s(output, stringBuffer);
	
}

void Shutdown()
{
	system("cls");
	printf("\n\tGame over...\n\t");
	_getch();
}


int main()
{
	/*Test ascii symbols
	unsigned char test;
	for (int i = 0; i < 500; i++)
	{
		test = i;
		printf("%c",test);
	}*/

	SetupSystem();
	Initialize();

	while (isGameActive)
	{
		Render();
		Update();
	}

	Shutdown();

	return 0;
}