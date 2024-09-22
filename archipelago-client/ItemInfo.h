#pragma once

#include "GameTypes.h"

// Item categories to subdivide DS3's built in item types (see ItemType in GameTypes.h)
enum class DetailedItemType : uint32_t {
	meleeWeapon,
	catalyst,
	spell,
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

	// these aren't expected to be used, they're only for error handling
	unrecognizedWeapon,
	unrecognizedArmor,
};

class CItemInfo
{
public:
	virtual DetailedItemType GetDetailedItemType(uint32_t dItemID);
	
private:
	virtual bool IsItemInList(uint32_t dItem, uint32_t* pArray);
};
