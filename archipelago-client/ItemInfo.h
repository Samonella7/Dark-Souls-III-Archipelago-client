#pragma once

#include <optional>

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
	// returns a specific item type of the given item, or std::nullopt if it was unrecognized
	virtual std::optional<DetailedItemType> GetDetailedItemType(uint32_t dItemID);

	// returns infusion/reinforcement info of the given item, or std::nullopt if it is not a weapon
	virtual std::optional<WeaponUpgradeType> GetWeaponUpgradeType(uint32_t dItemID);
	
private:
	virtual bool IsItemInList(uint32_t dItem, uint32_t* pArray);
};
