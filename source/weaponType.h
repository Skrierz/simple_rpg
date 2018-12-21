#pragma once

#include "level.h"

enum WeaponType
{
	WeaponType_None,
	WeaponType_Fist,
	WeaponType_Stick,
	WeaponType_Club,
	WeaponType_Spear,
	WeaponType_Saber,
	WeaponType_Flail,
	WeaponType_Scythe,
	WeaponType_Claymore,
	WeaponType_Axe,
	WeaponType_Crossbow,
	WeaponType_Slingshot,
	WeaponType_Mace,
};

const char* WeaponName_None = "None";
const char* WeaponName_Fist = "Fist";
const char* WeaponName_Stick = "Stick";
const char* WeaponName_Club = "Club";
const char* WeaponName_Spear = "Spear";
const char* WeaponName_Saber = "Saber";
const char* WeaponName_Flail = "Flail";
const char* WeaponName_Scythe = "Scythe";
const char* WeaponName_Claymore = "Claymore";
const char* WeaponName_Axe = "Axe";
const char* WeaponName_Crossbow = "Crossbow";
const char* WeaponName_Slingshot = "Slingshot";
const char* WeaponName_Mace = "Mace";



const char* GetWeaponName(WeaponType weaponType)
{
	switch (weaponType)
	{
		case WeaponType_Fist:  return WeaponName_Fist;
		case WeaponType_Stick: return WeaponName_Stick;
		case WeaponType_Club:  return WeaponName_Club;
		case WeaponType_Spear: return WeaponName_Spear;
		case WeaponType_Saber: return WeaponName_Saber;
		case WeaponType_Flail: return WeaponName_Flail;
		case WeaponType_Scythe: return WeaponName_Scythe;
		case WeaponType_Claymore: return WeaponName_Claymore;
		case WeaponType_Axe: return WeaponName_Axe;
		case WeaponType_Crossbow: return WeaponName_Crossbow;
		case WeaponType_Slingshot: return WeaponName_Slingshot;
		case WeaponType_Mace: return WeaponName_Mace;

	}

	return WeaponName_None;
}

int GetWeaponMinDamage(WeaponType weaponType)
{
	switch (weaponType)
	{
	case WeaponType_Fist: return 1;
	case WeaponType_Stick: return 6;
	case WeaponType_Club: return 14;
	case WeaponType_Spear: return 19;
	case WeaponType_Saber: return 25;
	case WeaponType_Flail: return 35;
	case WeaponType_Scythe: return 45;
	case WeaponType_Claymore: return 61;
	case WeaponType_Axe: return 84;
	case WeaponType_Crossbow: return 90;
	case WeaponType_Slingshot: return 100;
	case WeaponType_Mace: return 110;
	default: return 0;
	}
}

int GetWeaponMaxDamage(WeaponType weaponType)
{
	switch (weaponType)
	{
	case WeaponType_Fist: return 2;
	case WeaponType_Stick: return 8;
	case WeaponType_Club: return 18;
	case WeaponType_Spear: return 25;
	case WeaponType_Saber: return 35;
	case WeaponType_Flail: return 41;
	case WeaponType_Scythe: return 57;
	case WeaponType_Claymore: return 84;
	case WeaponType_Axe: return 90;
	case WeaponType_Crossbow: return 100;
	case WeaponType_Slingshot: return 110;
	case WeaponType_Mace: return 125;
	default: return 0;
	}
}

int GetWeaponDamage(WeaponType weaponName)
{
	int min = GetWeaponMinDamage(weaponName);
	int max = GetWeaponMaxDamage(weaponName);

	return min + (rand() % (max - min));
}

WeaponType GetWeaponTypeFromCell(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
		case CellSymbol_Stick: return WeaponType_Stick;
		case CellSymbol_Club:  return WeaponType_Club;
		case CellSymbol_Spear: return WeaponType_Spear;
		case CellSymbol_Saber: return WeaponType_Saber;
		case CellSymbol_Flail: return WeaponType_Flail;
		case CellSymbol_Scythe: return WeaponType_Scythe;
		case CellSymbol_Claymore: return WeaponType_Claymore;
		case CellSymbol_Axe: return WeaponType_Axe;
		case CellSymbol_Crossbow: return WeaponType_Crossbow;
		case CellSymbol_Slingshot: return WeaponType_Slingshot;
		case CellSymbol_Mace: return WeaponType_Mace;
	}

	return WeaponType_None;
}
