#include <optional>

#include "ItemInfo.h"
#include "AutoEquip.h"
#include "GameHook.h"

extern CCore* Core;
extern CAutoEquip* AutoEquip;
extern CGameHook* GameHook;
extern CItemInfo* ItemInfo;

uint32_t pInfusibleMeleeWeapons[];
uint32_t pUninfusibleMeleeWeapons[];
uint32_t pScaleMeleeWeapons[];
uint32_t pTwinklingMeleeWeapons[];
uint32_t pUnupgradeableMeleeWeapons[];

uint32_t pCatalysts[];
uint32_t pTwinklingCatalysts[];
uint32_t pScaleCatalysts[];

uint32_t pBows[];
uint32_t pTwinklingBows[];
uint32_t pScaleBows[];

uint32_t pInfusibleShields[];
uint32_t pUninfusibleShields[];
uint32_t pTwinklingShields[];
uint32_t pScaleShields[];

uint32_t pHelmetList[];
uint32_t pBodyList[];
uint32_t pHandsList[];
uint32_t pLegsList[];

std::optional<DetailedItemType> CItemInfo::GetDetailedItemType(uint32_t dItemID) {

	auto baseItemType = (ItemType)(dItemID >> 0x1C);
	switch (baseItemType) {
	case ItemType::weapon: {
		if ((dItemID >> 0x10) == 6) return DetailedItemType::ammo;

		// strip infusion and reinforcements
		dItemID = dItemID - (dItemID % 10000);

		if ((dItemID & 0xFF000000) == 0x01000000) return DetailedItemType::shield;

		else if (IsItemInList(dItemID, pInfusibleMeleeWeapons)) return DetailedItemType::meleeWeapon;
		else if (IsItemInList(dItemID, pUninfusibleMeleeWeapons)) return DetailedItemType::meleeWeapon;
		else if (IsItemInList(dItemID, pTwinklingMeleeWeapons)) return DetailedItemType::meleeWeapon;
		else if (IsItemInList(dItemID, pScaleMeleeWeapons)) return DetailedItemType::meleeWeapon;
		else if (IsItemInList(dItemID, pUnupgradeableMeleeWeapons)) return DetailedItemType::meleeWeapon;

		else if (IsItemInList(dItemID, pCatalysts)) return DetailedItemType::catalyst;
		else if (IsItemInList(dItemID, pTwinklingCatalysts)) return DetailedItemType::catalyst;
		else if (IsItemInList(dItemID, pScaleCatalysts)) return DetailedItemType::catalyst;

		else if (IsItemInList(dItemID, pBows)) return DetailedItemType::bow;
		else if (IsItemInList(dItemID, pTwinklingBows)) return DetailedItemType::bow;
		else if (IsItemInList(dItemID, pScaleBows)) return DetailedItemType::bow;
		else {
			spdlog::trace("Unrecognized weapon: {}", dItemID);
			return std::nullopt;
		}
	};
	case ItemType::protector: {
		if (IsItemInList(dItemID, pHelmetList)) return DetailedItemType::headArmor;
		else if (IsItemInList(dItemID, pBodyList)) return DetailedItemType::bodyArmor;
		else if (IsItemInList(dItemID, pHandsList)) return DetailedItemType::armsArmor;
		else if (IsItemInList(dItemID, pLegsList)) return DetailedItemType::legsArmor;
		else {
			spdlog::trace("Unrecognized protector item: {}", dItemID);
			return std::nullopt;
		}
	};
	case ItemType::accessory: {
		if ((dItemID & 0xFFFFFF00) == 0x20002700) return DetailedItemType::covenantItem;
		else return DetailedItemType::ring;
	};
	case ItemType::goods: return DetailedItemType::goods;
	default: {
		spdlog::trace("Unrecognized item type: {}", (byte)baseItemType);
		return std::nullopt;
	};
	};
};

std::optional<WeaponUpgradeType> CItemInfo::GetWeaponUpgradeType(uint32_t dItemID) {

	auto baseItemType = (ItemType)(dItemID >> 0x1C);
	if (baseItemType != ItemType::weapon)
		return WeaponUpgradeType::none;

	if ((dItemID >> 0x10) == 6) return WeaponUpgradeType::none; // ammo

	// strip infusion and reinforcements
	dItemID = (dItemID / 10000) * 10000;

	if ((dItemID & 0xFF000000) == 0x01000000) {
		if (IsItemInList(dItemID, pInfusibleShields)) return WeaponUpgradeType::regularInfusible;
		else if (IsItemInList(dItemID, pUninfusibleShields)) return WeaponUpgradeType::regularUninfusible;
		else if (IsItemInList(dItemID, pTwinklingShields)) return WeaponUpgradeType::twinkling;
		else return WeaponUpgradeType::scale;
	}

	else if (IsItemInList(dItemID, pInfusibleMeleeWeapons)) return WeaponUpgradeType::regularInfusible;

	else if (IsItemInList(dItemID, pUninfusibleMeleeWeapons)) return WeaponUpgradeType::regularUninfusible;
	else if (IsItemInList(dItemID, pCatalysts)) return WeaponUpgradeType::regularUninfusible;
	else if (IsItemInList(dItemID, pBows)) return WeaponUpgradeType::regularUninfusible;

	else if (IsItemInList(dItemID, pTwinklingMeleeWeapons)) return WeaponUpgradeType::twinkling;
	else if (IsItemInList(dItemID, pTwinklingCatalysts)) return WeaponUpgradeType::twinkling;
	else if (IsItemInList(dItemID, pTwinklingBows)) return WeaponUpgradeType::twinkling;

	else if (IsItemInList(dItemID, pScaleMeleeWeapons)) return WeaponUpgradeType::scale;
	else if (IsItemInList(dItemID, pScaleCatalysts)) return WeaponUpgradeType::scale;
	else if (IsItemInList(dItemID, pScaleBows)) return WeaponUpgradeType::scale;

	else if (IsItemInList(dItemID, pUnupgradeableMeleeWeapons)) return WeaponUpgradeType::none;

	else return std::nullopt;
};

bool CItemInfo::IsItemInList(uint32_t dItem, uint32_t* pArray) {
	if (!pArray) {
		spdlog::trace("Null array pointer in ItemInfo::IsItemInList");
		return false;
	};

	while (*pArray) {
		if (dItem == *pArray) return true;
		pArray++;
	};

	return false;
};

extern uint32_t pInfusibleMeleeWeapons[]{
	0x000F4240, // "Dagger"
	0x000F6950, // "Bandit's Knife"
	0x000F9060, // "Parrying Dagger"
	0x000FDE80, // "Rotten Ghru Dagger"
	0x00102CA0, // "Harpe"
	0x0010A1D0, // "Corvian Greatknife"
	0x00118C30, // "Murky Hand Scythe"
	0x001E8480, // "Shortsword"
	0x001EAB90, // "Longsword"
	0x001ED2A0, // "Broadsword"
	0x001EF9B0, // "Broken Straight Sword"
	0x001F6EE0, // "Lothric Knight Sword"
	0x00205940, // "Rotten Ghru Curved Sword"
	0x002191C0, // "Astora Straight Sword"
	0x0021B8D0, // "Barbed Straight Sword"
	0x002DC6C0, // "Estoc"
	0x002DEDD0, // "Mail Breaker"
	0x002E14E0, // "Rapier"
	0x002E3BF0, // "Ricard's Rapier"
	0x003D3010, // "Shotel"
	0x003D7E30, // "Scimitar"
	0x003DA540, // "Falchion"
	0x003DCC50, // "Carthus Curved Sword"
	0x003DF360, // "Carthus Curved Greatsword"
	0x003E6890, // "Painting Guardian's Curved Sword"
	0x003EB6B0, // "Carthus Shotel"
	0x003EDDC0, // "Follower Sabre"
	0x004C4B40, // "Uchigatana"
	0x004C7250, // "Washing Pole"
	0x004CC070, // "Black Blade"
	0x005B8D80, // "Bastard Sword"
	0x005BDBA0, // "Claymore"
	0x005C29C0, // "Zweihander"
	0x005C50D0, // "Greatsword"
	0x005C9EF0, // "Astora Greatsword"
	0x005CC600, // "Murakumo"
	0x005D1420, // "Lothric Knight Greatsword"
	0x005DB060, // "Flamberge"
	0x005DD770, // "Exile Greatsword"
	0x005E73B0, // "Cathedral Knight Greatsword"
	0x005F3700, // "Dark Sword"
	0x00609690, // "Drakeblood Greatsword"
	0x006159E0, // "Harald Curved Greatsword"
	0x006ACFC0, // "Hand Axe"
	0x006AF6D0, // "Battle Axe"
	0x006B1DE0, // "Brigand Axe"
	0x006B6C00, // "Crescent Axe"
	0x006B9310, // "Greataxe"
	0x006C0840, // "Dragonslayer's Axe"
	0x006C5660, // "Thrall Axe"
	0x006D19B0, // "Man Serpent Hatchet"
	0x006D67D0, // "Millwood Battle Axe"
	0x007A1200, // "Club"
	0x007A3910, // "Mace"
	0x007A6020, // "Morning Star"
	0x007A8730, // "Reinforced Club"
	0x007AFC60, // "Large Club"
	0x007B4A80, // "Great Club"
	0x007BBFB0, // "Great Mace"
	0x007C8300, // "Great Wooden Hammer"
	0x007DBB80, // "Warpick"
	0x007DE290, // "Pickaxe"
	0x007E57C0, // "Blacksmith Hammer"
	0x007EA5E0, // "Spiked Mace"
	0x00895440, // "Spear"
	0x00897B50, // "Winged Spear"
	0x0089C970, // "Partizan"
	0x008A8CC0, // "Greatlance"
	0x008AB3D0, // "Lothric Knight Long Spear"
	0x008ADAE0, // "Heavy Four-pronged Plow"
	0x008B2900, // "Rotten Ghru Spear"
	0x008C6180, // "Pike"
	0x008CD6B0, // "Follower Javelin"
	0x008D24D0, // "Lothric War Banner"
	0x00989680, // "Great Scythe"
	0x0098BD90, // "Lucerne"
	0x0098E4A0, // "Glaive"
	0x00990BB0, // "Halberd"
	0x0099CF00, // "Great Corvian Scythe"
	0x0099F610, // "Winged Knight Halberd"
	0x009AB960, // "Red Hilted Halberd"
	0x009B2E90, // "Splitleaf Greatsword"
	0x00A7D8C0, // "Claw"
	0x00A7FFD0, // "Caestus"
	0x00A826E0, // "Manikin Claws"
	0x00A89C10, // "Crow Talons"
	0x00B71B00, // "Whip"
	0x00B7DE50, // "Notched Whip"
	0x00F42400, // "Sellsword Twinblades"
	0x00F47220, // "Warden Twinblades"
	0x00F49930, // "Winged Knight Twinaxes"
	0x00F4E750, // "Great Machete"
	0x00F50E60, // "Brigand Twindaggers"
	0x00F53570, // "Gotthard Twinswords"
	0x00F58390, // "Onikiri and Ubadachi"
	0x00F5AAA0, // "Drang Twinspears"
	0x00F5F8C0, // "Giant Door Shield"
	0x00F61FD0, // "Drang Hammers"
	0x00F66DF0, // "Crow Quills"
	0x00000000
};

extern uint32_t pUninfusibleMeleeWeapons[]{
	0x001053B0, // "Scholar's Candlestick"
	0x00107AC0, // "Tailbone Short Sword"
	0x00111700, // "Handmaid's Dagger"
	0x0021DFE0, // "Executioner's Greatsword"
	0x006AFA54, // "Deep Battle Axe"
	0x006BE130, // "Butcher Knife"
	0x007CAA10, // "Gargoyle Flame Hammer"
	0x008B01F0, // "Gargoyle Flame Spear"
	0x008B7720, // "Soldering Iron"
	0x008C1360, // "Saint Bident"
	0x00B80560, // "Spotted Whip"
	0x00000000
};

extern uint32_t pTwinklingMeleeWeapons[]{
	0x00116520, // "Aquamarine Dagger"
	0x00203230, // "Sunlight Straight Sword"
	0x0020A760, // "Irithyll Straight Sword"
	0x0020F580, // "Cleric's Candlestick"
	0x002143A0, // "Morion Blade"
	0x002206F0, // "Anri's Straight Sword"
	0x00222E00, // "Onyx Blade"
	0x00225510, // "Ringed Knight Straight Sword"
	0x002E8A10, // "Irithyll Rapier"
	0x003E1A70, // "Pontiff Knight Curved Sword"
	0x004C9960, // "Chaos Blade"
	0x004CE780, // "Bloodlust"
	0x004D0E90, // "Darkdrift"
	0x005F5E10, // "Black Knight Sword"
	0x0060E4B0, // "Fume Ultra Greatsword"
	0x00610BC0, // "Old Wolf Curved Sword"
	0x007D6D60, // "Heysel Pick"
	0x007E30B0, // "Smough's Great Hammer"
	0x007E7ED0, // "Morne's Great Hammer"
	0x007ECCF0, // "Quakestone Hammer"
	0x007EF400, // "Ledo's Great Hammer"
	0x008C3A70, // "Yorshka's Spear"
	0x008CAFA0, // "Dragonslayer Spear"
	0x008CFDC0, // "Ringed Knight Spear"
	0x008D4BE0, // "Crucifix of the Mad King"
	0x009959D0, // "Black Knight Greataxe"
	0x0099A7F0, // "Pontiff Knight Great Scythe"
	0x009AE070, // "Black Knight Glaive"
	0x009B0780, // "Immolation Tinder"
	0x00B7B740, // "Witch's Locks"
	0x00F646E0, // "Valorheart"
	0x00F69500, // "Ringed Knight Paired Greatswords"
	0x00C83200, // "Golden Ritual Spear"
	0x00000000
};

extern uint32_t pScaleMeleeWeapons[]{
	0x00227C20, // "Gael's Greatsword"
	0x002E6300, // "Crystal Sage's Rapier"
	0x003E4180, // "Storm Curved Sword"
	0x003E8FA0, // "Crescent Moon Sword"
	0x003F04D0, // "Demon's Scar"
	0x004D35A0, // "Frayed Blade"
	0x005E2590, // "Greatsword of Judgment"
	0x005E4CA0, // "Profaned Greatsword"
	0x005E9AC0, // "Farron Greatsword"
	0x005F0FF0, // "Yhorm's Great Machete"
	0x005F8520, // "Lorian's Greatsword"
	0x005FAC30, // "Twin Princes' Greatsword"
	0x005FD340, // "Lothric's Holy Sword"
	0x005FFA50, // "Wolnir's Holy Sword"
	0x00602160, // "Wolf Knight's Greatsword"
	0x0060216A, // "Greatsword of Artorias"
	0x00604870, // "Hollowslayer Greatsword"
	0x00606F80, // "Moonlight Greatsword"
	0x0060BDA0, // "Firelink Greatsword"
	0x006132D0, // "Storm Ruler"
	0x006C7D70, // "Dragonslayer Greataxe"
	0x006CA480, // "Demon's Greataxe"
	0x006CCB90, // "Eleonora"
	0x006D8EE0, // "Earth Seeker"
	0x007CD120, // "Vordt's Great Hammer"
	0x007CF830, // "Old King's Great Hammer"
	0x007E09A0, // "Dragon Tooth"
	0x008B5010, // "Tailbone Spear"
	0x008BC540, // "Dragonslayer Swordspear"
	0x008BEC50, // "Arstor's Spear"
	0x009A1D20, // "Gundyr's Halberd"
	0x009B55A0, // "Friede's Great Scythe"
	0x00A84DF0, // "Demon's Fist"
	0x00B82C70, // "Rose of Ariandel"
	0x00F4C040, // "Dancer's Enchanted Swords"
	0x00000000
};

extern uint32_t pUnupgradeableMeleeWeapons[]{
	0x00A87500, // "Dark Hand"
	0x00000000
};

extern uint32_t pCatalysts[]{
	0x00C72090, // "Talisman"
	0x00C747A0, // "Sorcerer's Staff"
	0x00C76EB0, // "Storyteller's Staff"
	0x00C795C0, // "Mendicant's Staff"
	0x00C88020, // "Yorshka's Chime"
	0x00C8F550, // "Heretic's Staff"
	0x00C91C60, // "Court Sorcerer's Staff"
	0x00C94370, // "Witchtree Branch"
	0x00C99190, // "Cleric's Sacred Chime"
	0x00C9B8A0, // "Priest's Chime"
	0x00C9DFB0, // "Saint-tree Bellvine"
	0x00CA54E0, // "Sunlight Talisman"
	0x00CA7BF0, // "Canvas Talisman"
	0x00CACA10, // "Saint's Talisman"
	0x00CC77C0, // "Pyromancy Flame"
	0x00CC9ED0, // "Pyromancer's Parting Flame"
	0x00CCC5E0, // "Murky Longstaff"
	0x00000000
};

extern uint32_t pTwinklingCatalysts[]{
	0x00C7E3E0, // "Man-grub's Staff"
	0x00C80AF0, // "Archdeacon's Great Staff"
	0x00C96A80, // "Izalith Staff"
	0x00CA06C0, // "Caitha's Chime"
	0x00CA2DD0, // "Crystal Chime"
	0x00CAA300, // "Sunless Talisman"
	0x00CAF120, // "White Hair Talisman"
	0x00CCECF0, // "Sacred Chime of Filianore"
	0x00CD1400, // "Preacher's Right Arm"
	0x00000000
};

extern uint32_t pScaleCatalysts[]{
	0x00C8CE40, // "Sage's Crystal Staff"
	0x00000000
};

extern uint32_t pBows[]{
	0x00D5C690, // "Short Bow"
	0x00D5EDA0, // "Composite Bow"
	0x00D63BC0, // "Light Crossbow"
	0x00D662D0, // "Arbalest"
	0x00D689E0, // "Longbow"
	0x00D6FF10, // "Avelyn"
	0x00D72620, // "Knight's Crossbow"
	0x00D74D30, // "Heavy Crossbow"
	0x00D7E970, // "Black Bow of Pharis"
	0x00D83790, // "Sniper Crossbow"
	0x00000000
};

extern uint32_t pTwinklingBows[]{
	0x00CF8500, // "Dragonslayer Greatbow"
	0x00D77440, // "White Birch Bow"
	0x00D7C260, // "Onislayer Greatbow"
	0x00D85EA0, // "Millwood Greatbow"
	0x00000000
};

extern uint32_t pScaleBows[]{
	0x00D6B0F0, // "Dragonrider Bow"
	0x00D79B50, // "Darkmoon Longbow"
	0x00D885B0, // "Repeating Crossbow"
	0x00000000
};

extern uint32_t pInfusibleShields[]{
	0x01312D00, // "Buckler"
	0x01315410, // "Small Leather Shield"
	0x0131A230, // "Round Shield"
	0x0131C940, // "Large Leather Shield"
	0x01323E70, // "Hawkwood's Shield"
	0x01326580, // "Iron Round Shield"
	0x0132DAB0, // "Wooden Shield"
	0x013301C0, // "Kite Shield"
	0x013328D0, // "Ghru Rotshield"
	0x01339E00, // "Target Shield"
	0x0133C510, // "Elkhorn Round Shield"
	0x0133EC20, // "Warrior's Round Shield"
	0x01341330, // "Caduceus Round Shield"
	0x01343A40, // "Red and White Shield"
	0x01346150, // "Plank Shield"
	0x01348860, // "Leather Shield"
	0x0134AF70, // "Crimson Parma"
	0x0134D680, // "Eastern Iron Shield"
	0x0134FD90, // "Llewellyn Shield"
	0x01354BB0, // "Golden Falcon Shield"
	0x0135C0E0, // "Follower Shield"
	0x01409650, // "Lothric Knight Shield"
	0x01410B80, // "Knight Shield"
	0x014180B0, // "Carthus Shield"
	0x01426B10, // "Spiked Shield"
	0x01429220, // "Pierce Shield"
	0x0142B930, // "East-West Shield"
	0x0142E040, // "Sunlight Shield"
	0x01435570, // "Spider Shield"
	0x0143A390, // "Sunset Shield"
	0x0143F1B0, // "Blue Wooden Shield"
	0x014418C0, // "Silver Eagle Kite Shield"
	0x01443FD0, // "Stone Parma"
	0x01448DF0, // "Porcine Shield"
	0x0144DC10, // "Wargod Wooden Shield"
	0x014FD890, // "Lothric Knight Greatshield"
	0x014FFFA0, // "Cathedral Knight Greatshield"
	0x0150EA00, // "Black Iron Greatshield"
	0x01513820, // "Twin Dragon Greatshield"
	0x0151AD50, // "Bonewheel Shield"
	0x0151D460, // "Stone Greatshield"
	0x00000000
};

extern uint32_t pUninfusibleShields[]{
	0x015EF3C0, // "Torch"
	0x015F1AD0, // "Follower Torch"
	0x00000000
};

extern uint32_t pTwinklingShields[]{
	0x013376F0, // "Havel's Greatshield"
	0x013572C0, // "Sacred Bloom Shield"
	0x013599D0, // "Ancient Dragon Greatshield"
	0x014159A0, // "Pontiff Knight Shield"
	0x0141F5E0, // "Black Knight Shield"
	0x01424400, // "Silver Knight Shield"
	0x01430750, // "Crest Shield"
	0x01432E60, // "Dragon Crest Shield"
	0x01437C80, // "Grass Crest Shield"
	0x0143CAA0, // "Golden Wing Crest Shield"
	0x014466E0, // "Spirit Tree Crest Shield"
	0x01450320, // "Ethereal Oak Shield"
	0x015074D0, // "Moaning Shield"
	0x01511110, // "Wolf Knight's Greatshield"
	0x01515F30, // "Greatshield of Glory"
	0x00000000
};

extern uint32_t pScaleShields[]{
	0x0135E7F0, // "Dragonhead Shield"
	0x0144B500, // "Shield of Want"
	0x01452A30, // "Dragonhead Greatshield"
	0x01504DC0, // "Dragonslayer Greatshield"
	0x0150C2F0, // "Yhorm's Greatshield"
	0x01518640, // "Curse Ward Greatshield"
	0x00000000
};

extern uint32_t pHelmetList[]{
	0x14ADD0A0, // "Symbol of Avarice"
	0x14153A20, // "White Preacher Head"
	0x1121EAC0, // "Fallen Knight Helm"
	0x11298BE0, // "Knight Helm"
	0x11312D00, // "Vilhelm's Helm"
	0x11406F40, // "Firelink Helm"
	0x11481060, // "Sellsword Helm"
	0x114FB180, // "Herald Helm"
	0x115752A0, // "Sunless Veil"
	0x115EF3C0, // "Black Hand Hat"
	0x11607A60, // "Assassin Hood"
	0x116694E0, // "Xanthous Crown"
	0x116E3600, // "Northern Helm"
	0x1175D720, // "Morne's Helm"
	0x117D7840, // "Silver Mask"
	0x11851960, // "Sneering Mask"
	0x118CBA80, // "Sunset Helm"
	0x11945BA0, // "Old Sage's Blindfold"
	0x119BFCC0, // "Executioner Helm"
	0x11A39DE0, // "Billed Mask"
	0x11AB3F00, // "Pyromancer Crown"
	0x11BA8140, // "Court Sorcerer Hood"
	0x11C9C380, // "Sorcerer Hood"
	0x11D905C0, // "Cleric Hat"
	0x11E84800, // "Lapp's Helm"
	0x11F78A40, // "Grotto Hat" (unused)
	0x12625A00, // "Steel Soldier Helm"
	0x1263E0A0, // "Soldier's Hood" (unused)
	0x12656740, // "Thief Mask"
	0x129020C0, // "Sage's Big Hat"
	0x129F6300, // "Aristocrat's Mask"
	0x12A70420, // "Saint's Veil" (unused)
	0x12AEA540, // "Footman's Hood" (unused)
	0x12BDE780, // "Grave Warden Hood"
	0x12CD29C0, // "Worker Hat"
	0x12D4CAE0, // "Thrall Hood"
	0x12DC6C00, // "Evangelist Hat"
	0x12E40D20, // "Scholar's Shed Skin" (unused)
	0x12EBAE40, // "Winged Knight Helm"
	0x130291A0, // "Cathedral Knight Helm"
	0x13197500, // "Lothric Knight Helm"
	0x1328B740, // "Outrider Knight Helm"
	0x1337F980, // "Black Knight Helm"
	0x133F9AA0, // "Dark Mask"
	0x13473BC0, // "Exile Mask"
	0x13567E00, // "Pontiff Knight Crown"
	0x1365C040, // "Golden Crown"
	0x136D6160, // "Wolnir's Crown"
	0x13750280, // "Undead Legion Helm"
	0x138BE5E0, // "Man Serpent's Mask" (unused)
	0x13938700, // "Fire Witch Helm"
	0x13A2C940, // "Lorian's Helm"
	0x13AA6A60, // "Hood of Prayer"
	0x13B20B80, // "Giant's Crown" (unused)
	0x13C14DC0, // "Dancer's Crown"
	0x13D09000, // "Gundyr's Helm"
	0x13DFD240, // "Old Monarch's Crown" (unused)
	0x13EF1480, // "Archdeacon White Crown"
	0x13FE56C0, // "Frigid Valley Mask" (unused)
	0x140D9900, // "Dingy Hood" (unused)
	0x142C1D80, // "Chain Helm"
	0x143B5FC0, // "Nameless Knight Helm"
	0x144AA200, // "Elite Knight Helm"
	0x1459E440, // "Faraam Helm"
	0x14692680, // "Catarina Helm"
	0x1470C7A0, // "Standard Helm"
	0x147868C0, // "Havel's Helm"
	0x148009E0, // "Brigand Hood"
	0x1487AB00, // "Pharis's Hat"
	0x148F4C20, // "Ragged Mask"
	0x1496ED40, // "Old Sorcerer Hat"
	0x149E8E60, // "Conjurator Hood"
	0x14B571C0, // "Creighton's Steel Mask"
	0x14BD12E0, // "Maiden Hood"
	0x14C4B400, // "Alva Helm"
	0x14D3F640, // "Shadow Mask"
	0x14E33880, // "Eastern Helm"
	0x14F27AC0, // "Helm of Favor"
	0x1501BD00, // "Brass Helm"
	0x1510FF40, // "Silver Knight Helm"
	0x15204180, // "Lucatiel's Mask"
	0x152F83C0, // "Iron Helm"
	0x153EC600, // "Drakeblood Helm"
	0x155D4A80, // "Black Iron Helm"
	0x156C8CC0, // "Painting Guardian Hood"
	0x157BCF00, // "Wolf Knight Helm"
	0x158B1140, // "Dragonslayer Helm"
	0x159A5380, // "Smough's Helm"
	0x15A995C0, // "Hexer's Hood" (unused)
	0x15B8D800, // "Helm of Thorns"
	0x15C81A40, // "Varangian Helm" (unused)
	0x15D75C80, // "Crown of Dusk"
	0x15E69EC0, // "Karla's Pointed Hat"
	0x137CA3A0, // "Follower Helm"
	0x134EDCE0, // "Slave Knight Hood"
	0x139B2820, // "Millwood Knight Helm"
	0x135E1F20, // "Ordained Hood"
	0x11C22260, // "Shira's Crown"
	0x13C8EEE0, // "Ringed Knight Hood"
	0x1405F7E0, // "Iron Dragonslayer Helm"
	0x14CC5520, // "Ruin Helm"
	0x14DB9760, // "Desert Pyromancer Hood"
	0x14FA1BE0, // "Black Witch Veil"
	0x14EAD9A0, // "Black Witch Hat"
	0x15095E20, // "Blindfold Mask"
	0x00000000
};

extern uint32_t pBodyList[]{
	0x14B575A8, // "Mirrah Chain Mail"
	0x15204568, // "Mirrah Vest"
	0x156C90A8, // "Painting Guardian Gown"
	0x148F5008, // "Master's Attire"
	0x1121EEA8, // "Fallen Knight Armor"
	0x11298FC8, // "Knight Armor"
	0x113130E8, // "Vilhelm's Armor"
	0x11407328, // "Firelink Armor"
	0x11481448, // "Sellsword Armor"
	0x114FB568, // "Herald Armor"
	0x11575688, // "Sunless Armor"
	0x115EF7A8, // "Black Hand Armor"
	0x11607E48, // "Assassin Armor"
	0x116698C8, // "Xanthous Overcoat"
	0x116E39E8, // "Northern Armor"
	0x1175DB08, // "Morne's Armor"
	0x117D7C28, // "Leonhard's Garb"
	0x11851D48, // "Pale Shade Robe"
	0x118CBE68, // "Sunset Armor"
	0x11945F88, // "Cornyx's Garb"
	0x119C00A8, // "Executioner Armor"
	0x11A3A1C8, // "Black Dress"
	0x11AB42E8, // "Pyromancer Garb"
	0x11BA8528, // "Court Sorcerer Robe"
	0x11C9C768, // "Sorcerer Robe"
	0x11CB4E08, // "Clandestine Coat"
	0x11D909A8, // "Cleric Blue Robe"
	0x11DA9048, // "Dingy Maiden's Overcoat" (unused)
	0x11F78E28, // "Grotto Robe" (unused)
	0x129024A8, // "Elder's Robe" (unused)
	0x129F66E8, // "Jailer Robe"
	0x12A70808, // "Saint's Dress" (unused)
	0x12AEA928, // "Footman's Overcoat" (unused)
	0x12BDEB68, // "Grave Warden Robe"
	0x12CD2DA8, // "Worker Garb"
	0x12DC6FE8, // "Evangelist Robe"
	0x12E41108, // "Scholar's Robe"
	0x12EBB228, // "Winged Knight Armor"
	0x13029588, // "Cathedral Knight Armor"
	0x131978E8, // "Lothric Knight Armor"
	0x1328BB28, // "Outrider Knight Armor"
	0x1337FD68, // "Black Knight Armor"
	0x133F9E88, // "Dark Armor"
	0x13473FA8, // "Exile Armor"
	0x135681E8, // "Pontiff Knight Armor"
	0x1365C428, // "Dragonscale Armor"
	0x13750668, // "Undead Legion Armor"
	0x138BE9C8, // "Man Serpent's Robe" (unused)
	0x13938AE8, // "Fire Witch Armor"
	0x13A2CD28, // "Lorian's Armor"
	0x13AA6E48, // "Robe of Prayer"
	0x13B20F68, // "Giant's Armor"
	0x13C151A8, // "Dancer's Armor"
	0x13D093E8, // "Gundyr's Armor"
	0x13DFD628, // "Old Monarch's Robe" (unused)
	0x13EF1868, // "Archdeacon Holy Garb"
	0x13F6B988, // "Deacon Robe"
	0x140D9CE8, // "Fire Keeper Robe"
	0x142C2168, // "Chain Armor"
	0x143B63A8, // "Nameless Knight Armor"
	0x144AA5E8, // "Elite Knight Armor"
	0x1459E828, // "Faraam Armor"
	0x14692A68, // "Catarina Armor"
	0x1470CB88, // "Hard Leather Armor"
	0x14786CA8, // "Havel's Armor"
	0x14800DC8, // "Brigand Armor"
	0x1487AEE8, // "Leather Armor"
	0x1496F128, // "Old Sorcerer Coat"
	0x149E9248, // "Conjurator Robe"
	0x14A63368, // "Black Leather Armor"
	0x14BD16C8, // "Maiden Robe"
	0x14C4B7E8, // "Alva Armor"
	0x14D3FA28, // "Shadow Garb"
	0x14E33C68, // "Eastern Armor"
	0x14F27EA8, // "Embraced Armor of Favor"
	0x1501C0E8, // "Brass Armor"
	0x15110328, // "Silver Knight Armor"
	0x152F87A8, // "Armor of the Sun"
	0x153EC9E8, // "Drakeblood Armor"
	0x154E0C28, // "Drang Armor"
	0x155D4E68, // "Black Iron Armor"
	0x157BD2E8, // "Wolf Knight Armor"
	0x158B1528, // "Dragonslayer Armor"
	0x159A5768, // "Smough's Armor"
	0x15A999A8, // "Hexer's Robes" (unused)
	0x15B8DBE8, // "Armor of Thorns"
	0x15C81E28, // "Varangian Armor" (unused)
	0x15D76068, // "Antiquated Dress"
	0x15E6A2A8, // "Karla's Coat"
	0x137CA788, // "Follower Armor"
	0x134EE0C8, // "Slave Knight Armor"
	0x139B2C08, // "Millwood Knight Armor"
	0x135E2308, // "Ordained Dress"
	0x11B2E408, // "Antiquated Plain Garb"
	0x11C22648, // "Shira's Armor"
	0x11E84BE8, // "Lapp's Armor"
	0x13C8F2C8, // "Ringed Knight Armor"
	0x13D83508, // "Harald Legion Armor"
	0x1405FBC8, // "Iron Dragonslayer Armor"
	0x14CC5908, // "Ruin Armor"
	0x14DB9B48, // "Desert Pyromancer Garb"
	0x14EADD88, // "Black Witch Garb"
	0x12625DE8, // "Deserter Armor"
	0x00000000
};

extern uint32_t pHandsList[]{
	0x149E9630, // "Conjurator Manchettes"
	0x1121F290, // "Fallen Knight Gauntlets"
	0x112993B0, // "Knight Gauntlets"
	0x113134D0, // "Vilhelm's Gauntlets"
	0x11407710, // "Firelink Gauntlets"
	0x11481830, // "Sellsword Gauntlet"
	0x114FB950, // "Herald Gloves"
	0x11575A70, // "Sunless Gauntlets"
	0x115EFB90, // "Assassin Gloves"
	0x11669CB0, // "Xanthous Gloves"
	0x116E3DD0, // "Northern Gloves"
	0x1175DEF0, // "Morne's Gauntlets"
	0x117D8010, // "Leonhard's Gauntlets"
	0x11852130, // "Pale Shade Gloves"
	0x118CC250, // "Sunset Gauntlets"
	0x11946370, // "Cornyx's Wrap"
	0x119C0490, // "Executioner Gauntlets"
	0x11A3A5B0, // "Black Gauntlets"
	0x11AB46D0, // "Pyromancer Wrap"
	0x11BA8910, // "Court Sorcerer Gloves"
	0x11C9CB50, // "Sorcerer Gloves"
	0x11D90D90, // "Cleric Gloves"
	0x11E84FD0, // "Lapp's Gauntlets"
	0x11F79210, // "Grotto Wrap" (unused)
	0x126261D0, // "Soldier's Gauntlets" (unused)
	0x129F6AD0, // "Jailer Gloves"
	0x12AEAD10, // "Footman's Bracelets" (unused)
	0x12BDEF50, // "Grave Warden Wrap"
	0x12CD3190, // "Worker Gloves"
	0x12DC73D0, // "Evangelist Gloves"
	0x12EBB610, // "Winged Knight Gauntlets"
	0x13029970, // "Cathedral Knight Gauntlets"
	0x13197CD0, // "Lothric Knight Gauntlets"
	0x1328BF10, // "Outrider Knight Gauntlets"
	0x13380150, // "Black Knight Gauntlets"
	0x133FA270, // "Dark Gauntlets"
	0x13474390, // "Exile Gauntlets"
	0x135685D0, // "Pontiff Knight Gauntlets"
	0x1365C810, // "Golden Bracelets"
	0x13750A50, // "Undead Legion Gauntlet"
	0x13938ED0, // "Fire Witch Gauntlets"
	0x13A2D110, // "Lorian's Gauntlets"
	0x13B21350, // "Giant's Gauntlets" (unused)
	0x13C15590, // "Dancer's Gauntlets"
	0x13D097D0, // "Gundyr's Gauntlets"
	0x140DA0D0, // "Fire Keeper Gloves"
	0x142C2550, // "Leather Gauntlets"
	0x143B6790, // "Nameless Knight Gauntlets"
	0x144AA9D0, // "Elite Knight Gauntlets"
	0x1459EC10, // "Faraam Gauntlets"
	0x14692E50, // "Catarina Gauntlets"
	0x1470CF70, // "Hard Leather Gauntlets"
	0x14787090, // "Havel's Gauntlets"
	0x148011B0, // "Brigand Gauntlets"
	0x1487B2D0, // "Leather Gloves"
	0x148F53F0, // "Master's Gloves"
	0x1496F510, // "Old Sorcerer Gauntlets"
	0x14A63750, // "Black Leather Gloves"
	0x14B57990, // "Mirrah Chain Gloves"
	0x14BD1AB0, // "Maiden Gloves"
	0x14C4BBD0, // "Alva Gauntlets"
	0x14D3FE10, // "Shadow Gauntlets"
	0x14E34050, // "Eastern Gauntlets"
	0x14F28290, // "Gauntlets of Favor"
	0x1501C4D0, // "Brass Gauntlets"
	0x15110710, // "Silver Knight Gauntlets"
	0x15204950, // "Mirrah Gloves"
	0x152F8B90, // "Iron Bracelets"
	0x153ECDD0, // "Drakeblood Gauntlets"
	0x154E1010, // "Drang Gauntlets"
	0x155D5250, // "Black Iron Gauntlets"
	0x156C9490, // "Painting Guardian Gloves"
	0x157BD6D0, // "Wolf Knight Gauntlets"
	0x158B1910, // "Dragonslayer Gauntlets"
	0x159A5B50, // "Smough's Gauntlets"
	0x15A99D90, // "Hexer's Gloves" (unused)
	0x15B8DFD0, // "Gauntlets of Thorns"
	0x15C82210, // "Varangian Cuffs" (unused)
	0x15D76450, // "Antiquated Gloves"
	0x15E6A690, // "Karla's Gloves"
	0x137CAB70, // "Follower Gloves"
	0x134EE4B0, // "Slave Knight Gauntlets"
	0x139B2FF0, // "Millwood Knight Gauntlets"
	0x11B2E7F0, // "Violet Wrappings"
	0x11C22A30, // "Shira's Gloves"
	0x13C8F6B0, // "Ringed Knight Gauntlets"
	0x13D838F0, // "Harald Legion Gauntlets"
	0x1405FFB0, // "Iron Dragonslayer Gauntlets"
	0x14CC5CF0, // "Ruin Gauntlets"
	0x14DB9F30, // "Desert Pyromancer Gloves"
	0x14EAE170, // "Black Witch Wrappings"
	0x00000000
};

extern uint32_t pLegsList[]{
	0x1121F678, // "Fallen Knight Trousers"
	0x11299798, // "Knight Leggings"
	0x113138B8, // "Vilhelm's Leggings"
	0x11407AF8, // "Firelink Leggings"
	0x11481C18, // "Sellsword Trousers"
	0x114FBD38, // "Herald Trousers"
	0x11575E58, // "Sunless Leggings"
	0x115EFF78, // "Assassin Trousers"
	0x1166A098, // "Xanthous Trousers"
	0x116E41B8, // "Northern Trousers"
	0x1175E2D8, // "Morne's Leggings"
	0x117D83F8, // "Leonhard's Trousers"
	0x11852518, // "Pale Shade Trousers"
	0x118CC638, // "Sunset Leggings"
	0x11946758, // "Cornyx's Skirt"
	0x119C0878, // "Executioner Leggings"
	0x11A3A998, // "Black Leggings"
	0x11AB4AB8, // "Pyromancer Trousers"
	0x11BA8CF8, // "Court Sorcerer Trousers"
	0x11C9CF38, // "Sorcerer Trousers"
	0x11D91178, // "Cleric Trousers"
	0x11E853B8, // "Lapp's Leggings"
	0x11F795F8, // "Grotto Trousers" (unused)
	0x126265B8, // "Deserter Trousers"
	0x129F6EB8, // "Jailer Trousers"
	0x12AEB0F8, // "Footman's Trousers" (unused)
	0x12BDF338, // "Grave Warden Skirt"
	0x12CD3578, // "Worker Trousers"
	0x12DC77B8, // "Evangelist Trousers"
	0x12EBB9F8, // "Winged Knight Leggings"
	0x13029D58, // "Cathedral Knight Leggings"
	0x131980B8, // "Lothric Knight Leggings"
	0x1328C2F8, // "Outrider Knight Leggings"
	0x13380538, // "Black Knight Leggings"
	0x133FA658, // "Dark Leggings"
	0x13474778, // "Exile Leggings"
	0x135689B8, // "Pontiff Knight Leggings"
	0x1365CBF8, // "Dragonscale Waistcloth"
	0x13750E38, // "Undead Legion Leggings"
	0x139392B8, // "Fire Witch Leggings"
	0x13A2D4F8, // "Lorian's Leggings"
	0x13AA7618, // "Skirt of Prayer"
	0x13B21738, // "Giant's Leggings" (unused)
	0x13C15978, // "Dancer's Leggings"
	0x13D09BB8, // "Gundyr's Leggings"
	0x13EF2038, // "Archdeacon Skirt"
	0x13F6C158, // "Deacon Skirt"
	0x140DA4B8, // "Fire Keeper Skirt"
	0x142C2938, // "Chain Leggings"
	0x143B6B78, // "Nameless Knight Leggings"
	0x144AADB8, // "Elite Knight Leggings"
	0x1459EFF8, // "Faraam Boots"
	0x14693238, // "Catarina Leggings"
	0x1470D358, // "Hard Leather Boots"
	0x14787478, // "Havel's Leggings"
	0x14801598, // "Brigand Trousers"
	0x1487B6B8, // "Leather Boots"
	0x148F57D8, // "Loincloth"
	0x1496F8F8, // "Old Sorcerer Boots"
	0x149E9A18, // "Conjurator Boots"
	0x14A63B38, // "Black Leather Boots"
	0x14B57D78, // "Mirrah Chain Leggings"
	0x14BD1E98, // "Maiden Skirt"
	0x14C4BFB8, // "Alva Leggings"
	0x14D401F8, // "Shadow Leggings"
	0x14E34438, // "Eastern Leggings"
	0x14F28678, // "Leggings of Favor"
	0x1501C8B8, // "Brass Leggings"
	0x15110AF8, // "Silver Knight Leggings"
	0x15204D38, // "Mirrah Trousers"
	0x152F8F78, // "Iron Leggings"
	0x153ED1B8, // "Drakeblood Leggings"
	0x154E13F8, // "Drang Shoes"
	0x155D5638, // "Black Iron Leggings"
	0x156C9878, // "Painting Guardian Waistcloth"
	0x157BDAB8, // "Wolf Knight Leggings"
	0x158B1CF8, // "Dragonslayer Leggings"
	0x159A5F38, // "Smough's Leggings"
	0x15A9A178, // "Hexer's Boots" (unused)
	0x15B8E3B8, // "Leggings of Thorns"
	0x15C825F8, // "Varangian Leggings" (unused)
	0x15D76838, // "Antiquated Skirt"
	0x15E6AA78, // "Karla's Trousers"
	0x137CAF58, // "Follower Boots"
	0x134EE898, // "Slave Knight Leggings"
	0x139B33D8, // "Millwood Knight Leggings"
	0x135E2AD8, // "Ordained Trousers"
	0x11B2EBD8, // "Loincloth 2"
	0x11C22E18, // "Shira's Trousers"
	0x13C8FA98, // "Ringed Knight Leggings"
	0x13D83CD8, // "Harald Legion Leggings"
	0x14060398, // "Iron Dragonslayer Leggings"
	0x14CC60D8, // "Ruin Leggings"
	0x14DBA318, // "Desert Pyromancer Skirt"
	0x14EAE558, // "Black Witch Trousers"
	0x00000000
};

// The rest of these aren't currently needed, but are correctly grouped for reference/future use:

//extern uint32_t pCovenantsList[]{
//    0x20002710, // "Blade of the Darkmoon"
//    0x20002724, // "Watchdogs of Farron"
//    0x2000272E, // "Aldrich Faithful"
//    0x20002738, // "Warrior of Sunlight"
//    0x20002742, // "Mound-makers"
//    0x2000274C, // "Way of Blue"
//    0x20002756, // "Blue Sentinels"
//    0x20002760, // "Rosaria's Fingers"
//    0x2000276A, // "Spears of the Church"
//};
//
//extern uint32_t pSpellList[]{
//    0x40124F80, // "Farron Dart"
//    0x40127690, // "Great Farron Dart"
//    0x4013D620, // "Soul Arrow"
//    0x4013DA08, // "Great Soul Arrow"
//    0x4013DDF0, // "Heavy Soul Arrow"
//    0x4013E1D8, // "Great Heavy Soul Arrow"
//    0x4013E5C0, // "Homing Soulmass"
//    0x4013E9A8, // "Homing Crystal Soulmass"
//    0x4013ED90, // "Soul Spear"
//    0x4013F178, // "Crystal Soul Spear"
//    0x4013F560, // "Deep Soul"
//    0x4013F948, // "Great Deep Soul"
//    0x4013FD30, // "Magic Weapon"
//    0x40140118, // "Great Magic Weapon"
//    0x40140500, // "Crystal Magic Weapon"
//    0x40144B50, // "Magic Shield"
//    0x40144F38, // "Great Magic Shield"
//    0x40147260, // "Hidden Weapon"
//    0x40147648, // "Hidden Body"
//    0x40149970, // "Cast Light"
//    0x4014A528, // "Repair"
//    0x4014A910, // "Spook"
//    0x4014ACF8, // "Chameleon"
//    0x4014B0E0, // "Aural Decoy"
//    0x4014E790, // "White Dragon Breath"
//    0x4014EF60, // "Farron Hail"
//    0x4014F348, // "Crystal Hail"
//    0x4014F730, // "Soul Greatsword"
//    0x4014FB18, // "Farron Flashsword"
//    0x401875B8, // "Affinity"
//    0x40189CC8, // "Dark Edge"
//    0x4018B820, // "Soul Stream"
//    0x40193138, // "Twisted Wall of Light"
//    0x401A8CE0, // "Pestilent Mist"
//    0x40249F00, // "Fireball"
//    0x4024A6D0, // "Fire Orb"
//    0x4024AAB8, // "Firestorm"
//    0x4024B288, // "Fire Surge"
//    0x4024BA58, // "Black Serpent"
//    0x4024C610, // "Combustion"
//    0x4024C9F8, // "Great Combustion"
//    0x4024ED20, // "Poison Mist"
//    0x4024F108, // "Toxic Mist"
//    0x4024F4F0, // "Acid Surge"
//    0x40251430, // "Iron Flesh"
//    0x40251818, // "Flash Sweat"
//    0x402527B8, // "Carthus Flame Arc"
//    0x40252BA0, // "Rapport"
//    0x40253B40, // "Power Within"
//    0x40256250, // "Great Chaos Fire Orb"
//    0x40256638, // "Chaos Storm"
//    0x40256A20, // "Fire Whip"
//    0x40256E08, // "Black Flame"
//    0x402575D8, // "Profaned Flame"
//    0x402579C0, // "Chaos Bed Vestiges"
//    0x4025B070, // "Warmth"
//    0x402717D0, // "Profuse Sweat"
//    0x4027D350, // "Black Fire Orb"
//    0x4027FA60, // "Bursting Fireball"
//    0x40282170, // "Boulder Heave"
//    0x40284880, // "Sacred Flame"
//    0x40286F90, // "Carthus Beacon"
//    0x403540D0, // "Heal Aid"
//    0x403567E0, // "Heal"
//    0x40356BC8, // "Med Heal"
//    0x40356FB0, // "Great Heal"
//    0x40357398, // "Soothing Sunlight"
//    0x40357780, // "Replenishment"
//    0x40357B68, // "Bountiful Sunlight"
//    0x40358338, // "Bountiful Light"
//    0x40358720, // "Caressing Tears"
//    0x4035B600, // "Tears of Denial"
//    0x4035B9E8, // "Homeward"
//    0x4035DD10, // "Force"
//    0x4035E0F8, // "Wrath of the Gods"
//    0x4035E4E0, // "Emit Force"
//    0x40360420, // "Seek Guidance"
//    0x40362B30, // "Lightning Spear"
//    0x40362F18, // "Great Lightning Spear"
//    0x40363300, // "Sunlight Spear"
//    0x403636E8, // "Lightning Storm"
//    0x40363AD0, // "Gnaw"
//    0x40363EB8, // "Dorhys' Gnawing"
//    0x40365240, // "Magic Barrier"
//    0x40365628, // "Great Magic Barrier"
//    0x40365DF8, // "Sacred Oath"
//    0x4036A448, // "Vow of Silence"
//    0x4036C770, // "Lightning Blade"
//    0x4036CB58, // "Darkmoon Blade"
//    0x40378AC0, // "Dark Blade"
//    0x40387520, // "Dead Again"
//    0x40389C30, // "Lightning Stake"
//    0x4038C340, // "Divine Pillars of Light"
//    0x4038EA50, // "Lifehunt Scythe"
//    0x40395F80, // "Blessed Weapon"
//    0x40398690, // "Deep Protection"
//    0x4039ADA0, // "Atonement"
//
//    // dlc
//    0x401408E8, // "Frozen Weapon"
//    0x4014FF00, // "Old Moonlight"
//    0x401879A0, // "Great Soul Dregs"
//    0x401A90C8, // "Snap Freeze"
//    0x40257DA8, // "Floating Chaos"
//    0x40258190, // "Flame Fan"
//    0x402896A0, // "Seething Chaos"
//    0x40358B08, // "Lightning Arrow"
//    0x403642A0, // "Way of White Corona"
//    0x40364688, // "Projected Heal"
//
//    // unused
//    0x4027AC40, // "Dark Orb" (unused)
//    0x40359AA8, // "Morbid Temptation" (unused)
//    0x40393870, // "Dorris Swarm" (unused)
//
//    0x00000000,
//};
//
//extern uint32_t pItemsList[]{
//    0x40000064, // "White Sign Soapstone"
//    0x40000066, // "Red Sign Soapstone"
//    0x40000066, // "Red Eye Orb"
//    0x4000006C, // "Roster of Knights"
//    0x4000006F, // "Cracked Red Eye Orb"
//    0x40000073, // "Black Eye Orb"
//    0x400000F0, // "Divine Blessing"
//    0x400000F1, // "Hidden Blessing"
//    0x40000104, // "Green Blossom"
//    0x40000106, // "Budding Green Blossom"
//    0x4000010E, // "Bloodred Moss Clump"
//    0x4000010F, // "Purple Moss Clump"
//    0x40000110, // "Blooming Purple Moss Clump"
//    0x40000112, // "Purging Stone"
//    0x40000114, // "Rime-blue Moss Clump"
//    0x40000118, // "Repair Powder"
//    0x40000122, // "Kukri"
//    0x40000124, // "Firebomb"
//    0x40000125, // "Dung Pie"
//    0x40000126, // "Alluring Skull"
//    0x40000128, // "Undead Hunter Charm"
//    0x40000129, // "Black Firebomb"
//    0x4000012B, // "Rope Firebomb"
//    0x4000012C, // "Lightning Urn"
//    0x4000012E, // "Rope Black Firebomb"
//    0x4000012F, // "Stalk Dung Pie"
//    0x40000130, // "Duel Charm"
//    0x40000136, // "Throwing Knife"
//    0x40000137, // "Poison Throwing Knife"
//    0x4000014A, // "Charcoal Pine Resin"
//    0x4000014B, // "Gold Pine Resin"
//    0x4000014E, // "Human Pine Resin"
//    0x4000014F, // "Carthus Rouge"
//    0x40000150, // "Pale Pine Resin"
//    0x40000154, // "Charcoal Pine Bundle"
//    0x40000155, // "Gold Pine Bundle"
//    0x40000157, // "Rotten Pine Resin"
//    0x4000015E, // "Homeward Bone"
//    0x4000015F, // "Coiled Sword Fragment"
//    0x4000016E, // "Wolf's Blood Swordgrass"
//    0x4000016F, // "Human Dregs"
//    0x40000170, // "Forked Pale Tongue"
//    0x40000171, // "Proof of a Concord Well Kept"
//    0x40000172, // "Prism Stone"
//    0x40000173, // "Binoculars"
//    0x40000174, // "Proof of a Concord Kept"
//    0x40000175, // "Pale Tongue"
//    0x40000176, // "Vertebra Shackle"
//    0x40000177, // "Sunlight Medal"
//    0x40000179, // "Dragon Head Stone"
//    0x4000017A, // "Dragon Torso Stone"
//    0x4000017C, // "Rubbish"
//    0x40000181, // "Dried Finger"
//    0x40000183, // "Twinkling Dragon Head Stone"
//    0x40000184, // "Twinkling Dragon Torso Stone"
//    0x40000186, // "Fire Keeper Soul"
//    0x40000190, // "Fading Soul"
//    0x40000191, // "Soul of a Deserted Corpse"
//    0x40000192, // "Large Soul of a Deserted Corpse"
//    0x40000193, // "Soul of an Unknown Traveler"
//    0x40000194, // "Large Soul of an Unknown Traveler"
//    0x40000195, // "Soul of a Nameless Soldier"
//    0x40000196, // "Large Soul of a Nameless Soldier"
//    0x40000197, // "Soul of a Weary Warrior"
//    0x40000198, // "Large Soul of a Weary Warrior"
//    0x40000199, // "Soul of a Crestfallen Knight"
//    0x4000019A, // "Large Soul of a Crestfallen Knight"
//    0x4000019B, // "Soul of a Proud Paladin"
//    0x4000019C, // "Large Soul of a Proud Paladin"
//    0x4000019D, // "Soul of an Intrepid Hero"
//    0x4000019E, // "Large Soul of an Intrepid Hero"
//    0x4000019F, // "Soul of a Seasoned Warrior"
//    0x400001A0, // "Large Soul of a Seasoned Warrior"
//    0x400001A1, // "Soul of an Old Hand"
//    0x400001A2, // "Soul of a Venerable Old Hand"
//    0x400001A3, // "Soul of a Champion"
//    0x400001A4, // "Soul of a Great Champion"
//    0x400001B8, // "Seed of a Giant Tree"
//    0x400001C4, // "Mossfruit"
//    0x400001C6, // "Young White Branch"
//    0x400001C7, // "Rusted Coin"
//    0x400001C8, // "Siegbräu"
//    0x400001C9, // "Rusted Gold Coin"
//    0x400001CA, // "Blue Bug Pellet"
//    0x400001CB, // "Red Bug Pellet"
//    0x400001CC, // "Yellow Bug Pellet"
//    0x400001CD, // "Black Bug Pellet"
//    0x400001CF, // "Young White Branch"
//    0x400001EA, // "Dark Sigil"
//    0x400001F4, // "Ember"
//    0x40000208, // "Hello Carving"
//    0x40000209, // "Thank you Carving"
//    0x4000020A, // "Very good! Carving"
//    0x4000020B, // "I'm sorry Carving"
//    0x4000020C, // "Help me! Carving"
//    0x400002C8, // "Soul of Champion Gundyr"
//    0x400002CA, // "Soul of the Dancer"
//    0x400002CB, // "Soul of a Crystal Sage"
//    0x400002CD, // "Soul of the Blood of the Wolf"
//    0x400002CE, // "Soul of Consumed Oceiros"
//    0x400002CF, // "Soul of Boreal Valley Vordt"
//    0x400002D0, // "Soul of the Old Demon King"
//    0x400002D1, // "Soul of Dragonslayer Armour"
//    0x400002D2, // "Soul of the Nameless King"
//    0x400002D4, // "Soul of Pontiff Sulyvahn"
//    0x400002D5, // "Soul of Aldrich"
//    0x400002D6, // "Soul of High Lord Wolnir"
//    0x400002D7, // "Soul of the Rotted Greatwood"
//    0x400002D8, // "Soul of Rosaria"
//    0x400002D9, // "Soul of the Deacons of the Deep"
//    0x400002DB, // "Soul of the Twin Princes"
//    0x400002DC, // "Soul of Yhorm the Giant"
//    0x400002DD, // "Soul of the Lords"
//    0x400002E3, // "Soul of a Demon"
//    0x400002E7, // "Soul of a Stray Demon"
//    0x400003E8, // "Titanite Shard"
//    0x400003E9, // "Large Titanite Shard"
//    0x400003EA, // "Titanite Chunk"
//    0x400003EB, // "Titanite Slab"
//    0x400003FC, // "Titanite Scale"
//    0x40000406, // "Twinkling Titanite"
//    0x4000044C, // "Heavy Gem"
//    0x40000456, // "Sharp Gem"
//    0x40000460, // "Refined Gem"
//    0x4000046A, // "Crystal Gem"
//    0x40000474, // "Simple Gem"
//    0x4000047E, // "Fire Gem"
//    0x40000488, // "Chaos Gem"
//    0x40000492, // "Lightning Gem"
//    0x4000049C, // "Deep Gem"
//    0x400004A6, // "Dark Gem"
//    0x400004B0, // "Poison Gem"
//    0x400004BA, // "Blood Gem"
//    0x400004C4, // "Raw Gem"
//    0x400004CE, // "Blessed Gem"
//    0x400004D8, // "Hollow Gem"
//    0x400004E2, // "Shriving Stone"
//    0x400007D1, // "Lift Chamber Key"
//    0x400007D5, // "Small Doll"
//    0x400007D7, // "Jailbreaker's Key"
//    0x400007D8, // "Jailer's Key Ring"
//    0x400007D9, // "Grave Key"
//    0x400007DA, // "Cell Key"
//    0x400007DB, // "Dungeon Ground Floor Key"
//    0x400007DC, // "Old Cell Key"
//    0x400007DE, // "Grand Archives Key"
//    0x400007DF, // "Tower Key"
//    0x40000836, // "Small Lothric Banner"
//    0x40000837, // "Farron Coal"
//    0x40000838, // "Sage's Coal"
//    0x40000839, // "Giant's Coal"
//    0x4000083A, // "Profaned Coal"
//    0x4000083B, // "Mortician's Ashes"
//    0x4000083C, // "Dreamchaser's Ashes"
//    0x4000083D, // "Paladin's Ashes"
//    0x4000083E, // "Grave Warden's Ashes"
//    0x4000083F, // "Greirat's Ashes"
//    0x40000840, // "Orbeck's Ashes"
//    0x40000841, // "Cornyx's Ashes"
//    0x40000842, // "Karla's Ashes"
//    0x40000843, // "Irina's Ashes"
//    0x40000844, // "Yuria's Ashes"
//    0x40000845, // "Basin of Vows"
//    0x40000846, // "Loretta's Bone"
//    0x40000847, // "Braille Divine Tome of Carim"
//    0x40000848, // "Braille Divine Tome of Lothric"
//    0x4000084B, // "Cinders of a Lord - Abyss Watcher"
//    0x4000084C, // "Cinders of a Lord - Aldrich"
//    0x4000084D, // "Cinders of a Lord - Yhorm the Giant"
//    0x4000084E, // "Cinders of a Lord - Lothric Prince"
//    0x4000084F, // "Great Swamp Pyromancy Tome"
//    0x40000850, // "Carthus Pyromancy Tome"
//    0x40000851, // "Izalith Pyromancy Tome"
//    0x40000852, // "Quelana Pyromancy Tome"
//    0x40000853, // "Grave Warden Pyromancy Tome"
//    0x40000854, // "Sage's Scroll"
//    0x40000855, // "Logan's Scroll"
//    0x40000856, // "Crystal Scroll"
//    0x40000857, // "Transposing Kiln"
//    0x40000859, // "Coiled Sword"
//    0x4000085A, // "Eyes of a Fire Keeper"
//    0x4000085B, // "Sword of Avowal"
//    0x4000085C, // "Golden Scroll"
//    0x4000085D, // "Estus Shard"
//    0x4000085E, // "Hawkwood's Swordgrass"
//    0x4000085F, // "Undead Bone Shard"
//    0x40000860, // "Deep Braille Divine Tome"
//    0x40000861, // "Londor Braille Divine Tome"
//    0x40000862, // "Excrement-covered Ashes"
//    0x40000863, // "Prisoner Chief's Ashes"
//    0x40000864, // "Xanthous Ashes"
//    0x40000865, // "Hollow's Ashes"
//    0x40000866, // "Patches' Ashes"
//    0x40000867, // "Dragon Chaser's Ashes"
//    0x40000868, // "Easterner's Ashes"
//
//    // dlc
//    0x4000013B, // "Church Guardian Shiv"
//    0x4000017B, // "Filianore's Spear Ornament"
//    0x4000028A, // "Ritual Spear Fragment"
//    0x4000028B, // "Divine Spear Fragment"
//    0x400002E8, // "Soul of Sister Friede"
//    0x400002E9, // "Soul of Slave Knight Gael"
//    0x400002EA, // "Soul of the Demon Prince"
//    0x400002EB, // "Soul of Darkeater Midir"
//    0x40000869, // "Champion's Bones"
//    0x4000086A, // "Captain's Ashes"
//    0x4000086B, // "Contraption Key"
//    0x4000086C, // "Small Envoy Banner"
//    0x4000086D, // "Old Woman's Ashes"
//    0x4000086E, // "Blood of the Dark Soul"
//
//    // unused
//    0x400002C9, // "Soul of a Wicked Spirit" (unused)
//
//    0x00000000
//};
//
//extern uint32_t pRingsList[]{
//    0x20004E20, // "Life Ring"
//    0x20004E21, // "Life Ring+1"
//    0x20004E22, // "Life Ring+2"
//    0x20004E23, // "Life Ring+3"
//    0x20004E2A, // "Chloranthy Ring"
//    0x20004E2B, // "Chloranthy Ring+1"
//    0x20004E2C, // "Chloranthy Ring+2"
//    0x20004E34, // "Havel's Ring"
//    0x20004E35, // "Havel's Ring+1"
//    0x20004E36, // "Havel's Ring+2"
//    0x20004E3E, // "Ring of Favor"
//    0x20004E3F, // "Ring of Favor+1"
//    0x20004E40, // "Ring of Favor+2"
//    0x20004E48, // "Ring of Steel Protection"
//    0x20004E49, // "Ring of Steel Protection+1"
//    0x20004E4A, // "Ring of Steel Protection+2"
//    0x20004E52, // "Flame Stoneplate Ring"
//    0x20004E53, // "Flame Stoneplate Ring+1"
//    0x20004E54, // "Flame Stoneplate Ring+2"
//    0x20004E5C, // "Thunder Stoneplate Ring"
//    0x20004E5D, // "Thunder Stoneplate Ring+1"
//    0x20004E5E, // "Thunder Stoneplate Ring+2"
//    0x20004E66, // "Magic Stoneplate Ring"
//    0x20004E67, // "Magic Stoneplate Ring+1"
//    0x20004E68, // "Magic Stoneplate Ring+2"
//    0x20004E70, // "Dark Stoneplate Ring"
//    0x20004E71, // "Dark Stoneplate Ring+1"
//    0x20004E72, // "Dark Stoneplate Ring+2"
//    0x20004E7A, // "Speckled Stoneplate Ring"
//    0x20004E7B, // "Speckled Stoneplate Ring+1"
//    0x20004E84, // "Bloodbite Ring"
//    0x20004E85, // "Bloodbite Ring+1"
//    0x20004E8E, // "Poisonbite Ring"
//    0x20004E8F, // "Poisonbite Ring+1"
//    0x20004E98, // "Cursebite Ring"
//    0x20004EA2, // "Fleshbite Ring"
//    0x20004EA3, // "Fleshbite Ring+1"
//    0x20004EAC, // "Wood Grain Ring"
//    0x20004EAD, // "Wood Grain Ring+1"
//    0x20004EAE, // "Wood Grain Ring+2"
//    0x20004EB6, // "Scholar Ring"
//    0x20004EC0, // "Priestess Ring"
//    0x20004ECA, // "Red Tearstone Ring"
//    0x20004ED4, // "Blue Tearstone Ring"
//    0x20004EDE, // "Wolf Ring"
//    0x20004EDF, // "Wolf Ring+1"
//    0x20004EE0, // "Wolf Ring+2"
//    0x20004EE8, // "Leo Ring"
//    0x20004EF2, // "Ring of Sacrifice"
//    0x20004F06, // "Young Dragon Ring"
//    0x20004F07, // "Bellowing Dragoncrest Ring"
//    0x20004F10, // "Great Swamp Ring"
//    0x20004F11, // "Witch's Ring"
//    0x20004F1A, // "Morne's Ring"
//    0x20004F1B, // "Ring of the Sun's First Born"
//    0x20004F2E, // "Lingering Dragoncrest Ring"
//    0x20004F2F, // "Lingering Dragoncrest Ring+1"
//    0x20004F30, // "Lingering Dragoncrest Ring+2"
//    0x20004F38, // "Sage Ring"
//    0x20004F39, // "Sage Ring+1"
//    0x20004F3A, // "Sage Ring+2"
//    0x20004F42, // "Slumbering Dragoncrest Ring"
//    0x20004F4C, // "Dusk Crown Ring"
//    0x20004F56, // "Saint's Ring"
//    0x20004F60, // "Deep Ring"
//    0x20004F6A, // "Darkmoon Ring"
//    0x20004F92, // "Hawk Ring"
//    0x20004F9C, // "Hornet Ring"
//    0x20004FA6, // "Covetous Gold Serpent Ring"
//    0x20004FA7, // "Covetous Gold Serpent Ring+1"
//    0x20004FA8, // "Covetous Gold Serpent Ring+2"
//    0x20004FB0, // "Covetous Silver Serpent Ring"
//    0x20004FB1, // "Covetous Silver Serpent Ring+1"
//    0x20004FB2, // "Covetous Silver Serpent Ring+2"
//    0x20004FBA, // "Sun Princess Ring"
//    0x20004FC4, // "Silvercat Ring"
//    0x20004FCE, // "Skull Ring"
//    0x20004FD8, // "Untrue White Ring"
//    0x20004FE2, // "Carthus Milkring"
//    0x20004FEC, // "Knight's Ring"
//    0x20004FF6, // "Hunter's Ring"
//    0x20005000, // "Knight Slayer's Ring"
//    0x2000500A, // "Magic Clutch Ring"
//    0x20005014, // "Lightning Clutch Ring"
//    0x2000501E, // "Fire Clutch Ring"
//    0x20005028, // "Dark Clutch Ring"
//    0x2000503C, // "Flynn's Ring"
//    0x20005046, // "Prisoner's Chain"
//    0x20005050, // "Untrue Dark Ring"
//    0x20005064, // "Obscuring Ring"
//    0x2000506E, // "Ring of the Evil Eye"
//    0x2000506F, // "Ring of the Evil Eye+1"
//    0x20005070, // "Ring of the Evil Eye+2"
//    0x20005078, // "Calamity Ring"
//    0x20005082, // "Farron Ring"
//    0x2000508C, // "Aldrich's Ruby"
//    0x20005096, // "Aldrich's Sapphire"
//    0x200050B4, // "Lloyd's Sword Ring"
//    0x200050BE, // "Lloyd's Shield Ring"
//    0x200050DC, // "Estus Ring"
//    0x200050E6, // "Ashen Estus Ring"
//    0x200050F0, // "Horsehoof Ring"
//    0x200050FA, // "Carthus Bloodring"
//    0x20005104, // "Reversal Ring"
//    0x2000510E, // "Pontiff's Right Eye"
//    0x20005136, // "Pontiff's Left Eye"
//    0x2000515E, // "Dragonscale Ring"
//
//    // dlc
//    0x20004E2D, // "Chloranthy Ring+3"
//    0x20004E37, // "Havel's Ring+3"
//    0x20004E41, // "Ring of Favor+3"
//    0x20004E4B, // "Ring of Steel Protection+3"
//    0x20004EE1, // "Wolf Ring+3"
//    0x20004FA9, // "Covetous Gold Serpent Ring+3"
//    0x20004FB3, // "Covetous Silver Serpent Ring+3"
//    0x20005071, // "Ring of the Evil Eye+3"
//    0x20005208, // "Chillbite Ring"
//
//    // unused
//    0x20004EFC, // "Rare Ring of Sacrifice" (unused)
//    0x20005032, // "Baneful Bird Ring" (unused)
//    0x20004F7E, // "Darkmoon Blade Covenant Ring" (unused)
//    0x2000505A, // "Yorgh's Ring" (unused)
//    0x200050D2, // "Ring of Hiding" (unused)
//    0x20005118, // "Ring of Sustained Toughness" (unused)
//    0x20005122, // "Ring of Sustained Energy" (unused)
//    0x2000512C, // "Ring of Sustained Magic" (unused)
//    0x20005140, // "Ring of Sustained Essence" (unused)
//    0x2000514A, // "Ring of Sustained Might" (unused)
//    0x20005154, // "Ring of Sustained Fortune" (unused)
//
//    0x00000000
//};
//
//extern uint32_t pAmmoList[]{
//    0x00061A80, // "Standard Arrow" DS3ItemCategory.MISC
//    0x00061AE4, // "Fire Arrow" DS3ItemCategory.MISC
//    0x00061B48, // "Poison Arrow" DS3ItemCategory.MISC
//    0x00061BAC, // "Large Arrow" DS3ItemCategory.MISC
//    0x00061C10, // "Feather Arrow" DS3ItemCategory.MISC
//    0x00061C74, // "Moonlight Arrow" DS3ItemCategory.MISC
//    0x00061CD8, // "Wood Arrow" DS3ItemCategory.MISC
//    0x00061D3C, // "Dark Arrow" DS3ItemCategory.MISC
//    0x00062250, // "Dragonslayer Greatarrow" DS3ItemCategory.MISC
//    0x00062318, // "Dragonslayer Lightning Arrow" DS3ItemCategory.MISC
//    0x0006237C, // "Onislayer Greatarrow" DS3ItemCategory.MISC
//    0x000623E0, // "Millwood Greatarrow" DS3ItemCategory.MISC
//    0x00062A20, // "Standard Bolt" DS3ItemCategory.MISC
//    0x00062A84, // "Heavy Bolt" DS3ItemCategory.MISC
//    0x00062AE8, // "Sniper Bolt" DS3ItemCategory.MISC
//    0x00062B4C, // "Wood Bolt" DS3ItemCategory.MISC
//    0x00062BB0, // "Lightning Bolt" DS3ItemCategory.MISC
//    0x00062BB0, // "Lightning Bolt" DS3ItemCategory.MISC
//    0x00062C14, // "Splintering Bolt" DS3ItemCategory.MISC
//    0x00062C78, // "Exploding Bolt" DS3ItemCategory.MISC
//    0x00000000
//};

// finally, some unused weapons. not sure if they would be twinkling/scale/regular, and/or infusible
//0x00100590, // "Blood-stained Short Sword"
//0x006C2F50, // "Missionary's Axe"
//0x006D40C0, // "Dragon King Greataxe"
//0x007D4650, // "Four Knights Hammer"
//0x007D9470, // "Hammer of the Great Tree"
//0x008C8890, // "Channeler's Trident"
//0x009A4430, // "Lothric's Scythe"
//0x009A6B40, // "Ancient Dragon Halberd"
//0x009A9250, // "Scythe of Want"
//0x00C8A730, // "Sacred Beast Catalyst"
//0x00CC9ED0, // "Deep Pyromancy Flame"
//0x00CD3B10, // "Flickering Pyromancy Flame"
//0x00CD6220, // "Strong Pyromancy Flame"
//0x00CDFE60, // "Deep Pyromancy Flame"
//0x00CE2570, // "Pitch-Dark Pyromancy Flame"
//0x00D77440, // "Dancer's Short Bow"
//0x00D81080, // "Shield Crossbow"
//0x00F55C80, // "Golden Dual Swords"
//0x013524A0, // "Cleric's Parma"
//0x01421CF0, // "Prince's Shield"
