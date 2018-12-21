#pragma once

#include "level.h"
#include "weaponType.h"

enum UnitType
{
	UnitType_None,
	UnitType_Hero,
	UnitType_Orc,
	UnitType_Skeleton,
	UnitType_Ogre,
	UnitType_Werewolf,
	UnitType_Vampire,
	UnitType_GreenOrc,
	UnitType_Troll,
	UnitType_ArmoredSkeleton,
	UnitType_Zombie,
};

const char* UnitName_None     = "None";
const char* UnitName_Hero     = "Hero";
const char* UnitName_Orc      = "Orc";
const char* UnitName_Skeleton = "Skeleton";
const char* UnitName_Ogre     = "Ogre";
const char* UnitName_Werewolf = "Werewolf";
const char* UnitName_Vampire = "Vampire";
const char* UnitName_GreenOrc = "GreenOrc";
const char* UnitName_Troll = "Troll";
const char* UnitName_ArmoredSkeleton = "Armored Skeleton";
const char* UnitName_Zombie = "Zombie";


const char* GetUnitName(UnitType unitType)
{
	switch (unitType)
	{
	case UnitType_Hero:     return UnitName_Hero;
	case UnitType_Orc:      return UnitName_Orc;
	case UnitType_Skeleton: return UnitName_Skeleton;
	case UnitType_Ogre:     return UnitName_Ogre;
	case UnitType_Werewolf: return UnitName_Werewolf;
	case UnitType_Vampire:  return UnitName_Vampire;
	case UnitType_GreenOrc: return UnitName_GreenOrc;
	case UnitType_Troll:    return UnitName_Troll;
	case UnitType_ArmoredSkeleton:return UnitName_ArmoredSkeleton;
	case UnitType_Zombie:   return UnitName_Zombie;
	}

	return UnitName_None;
}

WeaponType GetUnitDefaultWeapon(UnitType unitType)
{
	switch (unitType)
	{
	case UnitType_Hero:     return WeaponType_Fist;
	case UnitType_Orc:      return WeaponType_Club;
	case UnitType_Skeleton: return WeaponType_Saber;
	case UnitType_Ogre:     return WeaponType_Claymore;
	case UnitType_Werewolf: return WeaponType_Flail;
	case UnitType_Vampire:  return WeaponType_Scythe;
	case UnitType_GreenOrc: return WeaponType_Club;
	case UnitType_Troll:    return WeaponType_Scythe;
	case UnitType_ArmoredSkeleton:return WeaponType_Saber;
	case UnitType_Zombie:   return WeaponType_Spear;
	}

	return WeaponType_None;
}

int GetUnitDefaultHealth(UnitType unitType)
{
	switch (unitType)
	{
	case UnitType_Hero:     return 400;
	case UnitType_Orc:      return 60;
	case UnitType_Skeleton: return 80;
	case UnitType_Ogre:     return 300;
	case UnitType_Werewolf: return 120;
	case UnitType_Vampire:  return 150;
	case UnitType_GreenOrc: return 145;
	case UnitType_Troll:    return 400;
	case UnitType_ArmoredSkeleton:return 130;
	case UnitType_Zombie:   return 200;

	}

	return 0;
}

UnitType GetUnitTypeFromCell(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
		case CellSymbol_Hero: return UnitType_Hero;
		case CellSymbol_Orc: return UnitType_Orc;
		case CellSymbol_Skeleton: return UnitType_Skeleton;
		case CellSymbol_Ogre: return UnitType_Ogre;
		case CellSymbol_Werewolf : return UnitType_Werewolf;
		case CellSymbol_Vampire : return UnitType_Vampire;
		case CellSymbol_GreenOrc : return UnitType_GreenOrc;
		case CellSymbol_Troll : return UnitType_Troll;
		case CellSymbol_ArmoredSkeleton : return UnitType_ArmoredSkeleton;
		case CellSymbol_Zombie : return UnitType_Zombie;
	}

	return UnitType_None;
}