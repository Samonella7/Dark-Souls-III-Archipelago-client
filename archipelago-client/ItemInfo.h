#pragma once

#include "GameTypes.h"

// Item categories to subdivide DS3's built in item types (see ItemType in GameTypes.h)
enum class DetailedItemType {
	meleeWeapon,
	catalyst,
	bow,
	shield,
	headArmor,
	bodyArmor,
	armsArmor,
	legsArmor,
	ring,
	ammo,
	covenantItem,
	goods,

	// these aren't expected to be used, they're only for error handling.
	// it's tempting to default to goods instead of these, but then this wouldn't truly subdivide ItemType
	unrecognizedWeapon,
	unrecognizedArmor,
};

enum class WeaponUpgradeType {
	regularInfusible,
	regularUninfusible,
	twinkling,
	scale,
	none, // stupid dark hand
};

class CItemInfo
{
public:
	virtual DetailedItemType GetDetailedItemType(uint32_t dItemID);
	virtual WeaponUpgradeType GetWeaponUpgradeType(uint32_t dItemID);
	
private:
	virtual bool IsItemInList(uint32_t dItem, uint32_t* pArray);
};
