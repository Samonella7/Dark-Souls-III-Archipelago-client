#include "ItemInfo.h"
#include "AutoEquip.h"
#include "GameHook.h"

extern CCore* Core;
extern CAutoEquip* AutoEquip;
extern CGameHook* GameHook;
extern CItemInfo* ItemInfo;

uint32_t pHelmetList[110];
uint32_t pBodyList[105];
uint32_t pHandsList[100];
uint32_t pLegsList[105];

DetailedItemType CItemInfo::GetDetailedItemType(uint32_t dItemID) {

	auto baseItemType = (ItemType)(dItemID >> 0x1C);
	switch (baseItemType) {
	case ItemType::weapon: {
		if ((dItemID >> 16) == 6) return DetailedItemType::ammo;
		if ((dItemID & 0xFF000000) >> 48 == 1) return DetailedItemType::shield;
		else return DetailedItemType::meleeWeapon; 
	};
	case ItemType::protector: {
		if (IsItemInList(dItemID, &pHelmetList[0])) return DetailedItemType::headArmor;
		else if (IsItemInList(dItemID, &pBodyList[0])) return DetailedItemType::bodyArmor;
		else if (IsItemInList(dItemID, &pHandsList[0])) return DetailedItemType::armsArmor;
		else if (IsItemInList(dItemID, &pLegsList[0])) return DetailedItemType::legsArmor;
		else {
			spdlog::trace("Unrecognized protector item: {}", dItemID);
			return DetailedItemType::unrecognizedArmor;
		}
	};
	case ItemType::accessory: {
		if ((dItemID & 0xFFFFFF00) == 0x20002700) return DetailedItemType::covenantItem;
		else return DetailedItemType::ring;
	};
	case ItemType::goods: return DetailedItemType::goods;
	default: {
		std::ostringstream stream;
		stream << "Invalid item type: " << ((uint32_t)baseItemType) << " (" << std::hex << dItemID << ")";
		Core->Panic(stream.str().c_str(), "...\\Source\\AutoEquip\\AutoEquip.cpp", HE_InvalidItemType, 0);
		return DetailedItemType::goods;
	};
	};
};

bool CItemInfo::IsItemInList(uint32_t dItem, uint32_t* pArray) {
	if (!pArray) {
		Core->Panic("Null array pointer!", "...\\Source\\AutoEquip\\AutoEquip.cpp", FE_NullArray, 1);
		int3
	};

	while (*pArray) {
		if (dItem == *pArray) return true;
		pArray++;
	};

	return false;
};

// All in-game headwear
extern uint32_t pHelmetList[110] {
	0x14ADD0A0,
	0x14153A20,
	0x1121EAC0,
	0x11298BE0,
	0x11312D00,
	0x11406F40,
	0x11481060,
	0x114FB180,
	0x115752A0,
	0x115EF3C0,
	0x11607A60,
	0x116694E0,
	0x116E3600,
	0x1175D720,
	0x117D7840,
	0x11851960,
	0x118CBA80,
	0x11945BA0,
	0x119BFCC0,
	0x11A39DE0,
	0x11AB3F00,
	0x11BA8140,
	0x11C9C380,
	0x11D905C0,
	0x11E84800,
	0x11F78A40,
	0x12625A00,
	0x1263E0A0,
	0x12656740,
	0x129020C0,
	0x129F6300,
	0x12A70420,
	0x12AEA540,
	0x12BDE780,
	0x12CD29C0,
	0x12D4CAE0,
	0x12DC6C00,
	0x12EBAE40,
	0x130291A0,
	0x13197500,
	0x1328B740,
	0x1337F980,
	0x133F9AA0,
	0x13473BC0,
	0x13567E00,
	0x1365C040,
	0x136D6160,
	0x13750280,
	0x138BE5E0,
	0x13938700,
	0x13A2C940,
	0x13AA6A60,
	0x13B20B80,
	0x13C14DC0,
	0x13D09000,
	0x13DFD240,
	0x13EF1480,
	0x13FE56C0,
	0x140D9900,
	0x142C1D80,
	0x143B5FC0,
	0x144AA200,
	0x1459E440,
	0x14692680,
	0x1470C7A0,
	0x147868C0,
	0x148009E0,
	0x1487AB00,
	0x148F4C20,
	0x1496ED40,
	0x149E8E60,
	0x12656740,
	0x14B571C0,
	0x14BD12E0,
	0x14C4B400,
	0x14D3F640,
	0x14E33880,
	0x14F27AC0,
	0x1501BD00,
	0x1510FF40,
	0x15204180,
	0x152F83C0,
	0x153EC600,
	0x155D4A80,
	0x156C8CC0,
	0x157BCF00,
	0x158B1140,
	0x159A5380,
	0x15A995C0,
	0x15B8D800,
	0x15C81A40,
	0x15D75C80,
	0x15E69EC0,
	0x137CA3A0,
	0x134EDCE0,
	0x11312D00,
	0x139B2820,
	0x135E1F20,
	0x11C22260,
	0x11E84800,
	0x13C8EEE0,
	0x1405F7E0,
	0x14CC5520,
	0x14DB9760,
	0x14FA1BE0,
	0x14EAD9A0,
	0x15095E20,
	0x00000000,
};

// All in-game chestpieces
extern uint32_t pBodyList[105] {
	0x14B575A8,
	0x15204568,
	0x156C90A8,
	0x148F5008,
	0x1121EEA8,
	0x11298FC8,
	0x113130E8,
	0x11407328,
	0x11481448,
	0x114FB568,
	0x11575688,
	0x115EF7A8,
	0x11607E48,
	0x116698C8,
	0x116E39E8,
	0x1175DB08,
	0x117D7C28,
	0x11851D48,
	0x118CBE68,
	0x11945F88,
	0x119C00A8,
	0x11A3A1C8,
	0x11AB42E8,
	0x11BA8528,
	0x11C9C768,
	0x11CB4E08,
	0x11D909A8,
	0x11DA9048,
	0x11F78E28,
	0x129024A8,
	0x129F66E8,
	0x12A70808,
	0x12AEA928,
	0x12BDEB68,
	0x12CD2DA8,
	0x12DC6FE8,
	0x12E41108,
	0x12EBB228,
	0x13029588,
	0x131978E8,
	0x1328BB28,
	0x1337FD68,
	0x133F9E88,
	0x13473FA8,
	0x135681E8,
	0x1365C428,
	0x13750668,
	0x138BE9C8,
	0x13938AE8,
	0x13A2CD28,
	0x13AA6E48,
	0x13B20F68,
	0x13C151A8,
	0x13D093E8,
	0x13DFD628,
	0x13EF1868,
	0x13F6B988,
	0x140D9CE8,
	0x142C2168,
	0x143B63A8,
	0x144AA5E8,
	0x1459E828,
	0x14692A68,
	0x1470CB88,
	0x14786CA8,
	0x14800DC8,
	0x1487AEE8,
	0x1496F128,
	0x149E9248,
	0x14A63368,
	0x14BD16C8,
	0x14C4B7E8,
	0x14D3FA28,
	0x14E33C68,
	0x14F27EA8,
	0x1501C0E8,
	0x15110328,
	0x152F87A8,
	0x153EC9E8,
	0x154E0C28,
	0x155D4E68,
	0x157BD2E8,
	0x158B1528,
	0x159A5768,
	0x15A999A8,
	0x15B8DBE8,
	0x15C81E28,
	0x15D76068,
	0x15E6A2A8,
	0x137CA788,
	0x134EE0C8,
	0x139B2C08,
	0x135E2308,
	0x11B2E408,
	0x11C22648,
	0x11E84BE8,
	0x13C8F2C8,
	0x13D83508,
	0x1405FBC8,
	0x14CC5908,
	0x14DB9B48,
	0x14EADD88,
	0x12625de8,
	0x00000000,
};

extern uint32_t pHandsList[100] {
	0x149E9630,
	0x1121F290,
	0x112993B0,
	0x113134D0,
	0x11407710,
	0x11481830,
	0x114FB950,
	0x11575A70,
	0x115EFB90,
	0x11669CB0,
	0x116E3DD0,
	0x1175DEF0,
	0x117D8010,
	0x11852130,
	0x118CC250,
	0x11946370,
	0x119C0490,
	0x11A3A5B0,
	0x11AB46D0,
	0x11BA8910,
	0x11C9CB50,
	0x11D90D90,
	0x11E84FD0,
	0x11F79210,
	0x126261D0,
	0x129F6AD0,
	0x12AEAD10,
	0x12BDEF50,
	0x12CD3190,
	0x12DC73D0,
	0x12EBB610,
	0x13029970,
	0x13197CD0,
	0x1328BF10,
	0x13380150,
	0x133FA270,
	0x13474390,
	0x135685D0,
	0x1365C810,
	0x13750A50,
	0x13938ED0,
	0x13A2D110,
	0x13B21350,
	0x13C15590,
	0x13D097D0,
	0x140DA0D0,
	0x142C2550,
	0x143B6790,
	0x144AA9D0,
	0x1459EC10,
	0x14692E50,
	0x1470CF70,
	0x14787090,
	0x148011B0,
	0x1487B2D0,
	0x148F53F0,
	0x1496F510,
	0x14A63750,
	0x14B57990,
	0x14BD1AB0,
	0x14C4BBD0,
	0x14D3FE10,
	0x14E34050,
	0x14F28290,
	0x1501C4D0,
	0x15110710,
	0x15204950,
	0x152F8B90,
	0x153ECDD0,
	0x154E1010,
	0x155D5250,
	0x156C9490,
	0x157BD6D0,
	0x158B1910,
	0x159A5B50,
	0x15A99D90,
	0x15B8DFD0,
	0x15D76450,
	0x15E6A690,
	0x137CAB70,
	0x134EE4B0,
	0x139B2FF0,
	0x11B2E7F0,
	0x11C22A30,
	0x11E84FD0,
	0x13C8F6B0,
	0x13D838F0,
	0x1405FFB0,
	0x14CC5CF0,
	0x14DB9F30,
	0x14EAE170,
	0x00000000,
};

extern uint32_t pLegsList[105] {
	0x1121F678,
	0x11299798,
	0x113138B8,
	0x11407AF8,
	0x11481C18,
	0x114FBD38,
	0x11575E58,
	0x115EFF78,
	0x1166A098,
	0x116E41B8,
	0x1175E2D8,
	0x117D83F8,
	0x11852518,
	0x118CC638,
	0x11946758,
	0x119C0878,
	0x11A3A998,
	0x11AB4AB8,
	0x11BA8CF8,
	0x11C9CF38,
	0x11D91178,
	0x11E853B8,
	0x11F795F8,
	0x126265B8,
	0x129F6EB8,
	0x12AEB0F8,
	0x12BDF338,
	0x12CD3578,
	0x12DC77B8,
	0x12EBB9F8,
	0x13029D58,
	0x131980B8,
	0x1328C2F8,
	0x13380538,
	0x133FA658,
	0x13474778,
	0x135689B8,
	0x1365CBF8,
	0x13750E38,
	0x139392B8,
	0x13A2D4F8,
	0x13AA7618,
	0x13B21738,
	0x13C15978,
	0x13D09BB8,
	0x13EF2038,
	0x13F6C158,
	0x140DA4B8,
	0x142C2938,
	0x143B6B78,
	0x144AADB8,
	0x1459EFF8,
	0x14693238,
	0x1470D358,
	0x14787478,
	0x14801598,
	0x1487B6B8,
	0x148F57D8,
	0x1496F8F8,
	0x149E9A18,
	0x14A63B38,
	0x14B57D78,
	0x14BD1E98,
	0x14C4BFB8,
	0x14D401F8,
	0x14E34438,
	0x14F28678,
	0x1501C8B8,
	0x15110AF8,
	0x15204D38,
	0x152F8F78,
	0x153ED1B8,
	0x154E13F8,
	0x155D5638,
	0x156C9878,
	0x157BDAB8,
	0x158B1CF8,
	0x159A5F38,
	0x15A9A178,
	0x15B8E3B8,
	0x15C825F8,
	0x15D76838,
	0x15E6AA78,
	0x137CAF58,
	0x134EE898,
	0x139B33D8,
	0x135E2AD8,
	0x11B2EBD8,
	0x11C22E18,
	0x11E853B8,
	0x13C8FA98,
	0x13D83CD8,
	0x14060398,
	0x14CC60D8,
	0x14DBA318,
	0x14EAE558,
	0x00000000,
};





_vanilla_items = [
    # Ammunition
    0x00061A80, // "Standard Arrow" DS3ItemCategory.MISC
    0x00061A80, // "Standard Arrow x8" DS3ItemCategory.MISC
    0x00061AE4, // "Fire Arrow" DS3ItemCategory.MISC
    0x00061AE4, // "Fire Arrow x8" DS3ItemCategory.MISC
    0x00061B48, // "Poison Arrow" DS3ItemCategory.MISC
    0x00061B48, // "Poison Arrow x8" DS3ItemCategory.MISC
    0x00061BAC, // "Large Arrow" DS3ItemCategory.MISC
    0x00061C10, // "Feather Arrow" DS3ItemCategory.MISC
    0x00061C74, // "Moonlight Arrow" DS3ItemCategory.MISC
    0x00061CD8, // "Wood Arrow" DS3ItemCategory.MISC
    0x00061D3C, // "Dark Arrow" DS3ItemCategory.MISC
    0x00062250, // "Dragonslayer Greatarrow" DS3ItemCategory.MISC
    0x00062318, // "Dragonslayer Lightning Arrow" DS3ItemCategory.MISC
    0x0006237C, // "Onislayer Greatarrow" DS3ItemCategory.MISC
    0x00062A20, // "Standard Bolt" DS3ItemCategory.MISC
    0x00062A84, // "Heavy Bolt" DS3ItemCategory.MISC
    0x00062AE8, // "Sniper Bolt" DS3ItemCategory.MISC
    0x00062B4C, // "Wood Bolt" DS3ItemCategory.MISC
    0x00062BB0, // "Lightning Bolt" DS3ItemCategory.MISC
    0x00062BB0, // "Lightning Bolt" DS3ItemCategory.MISC
    0x00062C14, // "Splintering Bolt" DS3ItemCategory.MISC
    0x00062C78, // "Exploding Bolt" DS3ItemCategory.MISC

        # Weapons
    0x000F4240, // "Dagger" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x000F6950, // "Bandit's Knife" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x000F9060, // "Parrying Dagger" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x000FDE80, // "Rotten Ghru Dagger" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00102CA0, // "Harpe" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x001053B0, // "Scholar's Candlestick" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00107AC0, // "Tailbone Short Sword" DS3ItemCategory.WEAPON_UPGRADE_10
    0x0010A1D0, // "Corvian Greatknife" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00111700, // "Handmaid's Dagger" DS3ItemCategory.WEAPON_UPGRADE_10
    0x001E8480, // "Shortsword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x001EAB90, // "Longsword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x001ED2A0, // "Broadsword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x001EF9B0, // "Broken Straight Sword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x001F6EE0, // "Lothric Knight Sword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00203230, // "Sunlight Straight Sword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00205940, // "Rotten Ghru Curved Sword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x0020A760, // "Irithyll Straight Sword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x0020F580, // "Cleric's Candlestick" DS3ItemCategory.WEAPON_UPGRADE_5
    0x002143A0, // "Morion Blade" DS3ItemCategory.WEAPON_UPGRADE_5
    0x002191C0, // "Astora Straight Sword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x0021B8D0, // "Barbed Straight Sword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x0021DFE0, // "Executioner's Greatsword" DS3ItemCategory.WEAPON_UPGRADE_10
    0x002206F0, // "Anri's Straight Sword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x002DC6C0, // "Estoc" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x002DEDD0, // "Mail Breaker" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x002E14E0, // "Rapier" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x002E3BF0, // "Ricard's Rapier" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x002E6300, // "Crystal Sage's Rapier" DS3ItemCategory.WEAPON_UPGRADE_5
    0x002E8A10, // "Irithyll Rapier" DS3ItemCategory.WEAPON_UPGRADE_5
    0x003D3010, // "Shotel" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x003D7E30, // "Scimitar" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x003DA540, // "Falchion" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x003DCC50, // "Carthus Curved Sword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x003DF360, // "Carthus Curved Greatsword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x003E1A70, // "Pontiff Knight Curved Sword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x003E4180, // "Storm Curved Sword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x003E6890, // "Painting Guardian's Curved Sword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x003E8FA0, // "Crescent Moon Sword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x003EB6B0, // "Carthus Shotel" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x004C4B40, // "Uchigatana" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x004C7250, // "Washing Pole" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x004C9960, // "Chaos Blade" DS3ItemCategory.WEAPON_UPGRADE_5
    0x004CC070, // "Black Blade" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x004CE780, // "Bloodlust" DS3ItemCategory.WEAPON_UPGRADE_5
    0x004D0E90, // "Darkdrift" DS3ItemCategory.WEAPON_UPGRADE_5
    0x005B8D80, // "Bastard Sword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x005BDBA0, // "Claymore" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x005C29C0, // "Zweihander" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x005C50D0, // "Greatsword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x005C9EF0, // "Astora Greatsword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x005CC600, // "Murakumo" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x005D1420, // "Lothric Knight Greatsword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x005DB060, // "Flamberge" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x005DD770, // "Exile Greatsword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x005E2590, // "Greatsword of Judgment" DS3ItemCategory.WEAPON_UPGRADE_5
    0x005E4CA0, // "Profaned Greatsword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x005E73B0, // "Cathedral Knight Greatsword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x005E9AC0, // "Farron Greatsword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x005F0FF0, // "Yhorm's Great Machete" DS3ItemCategory.WEAPON_UPGRADE_5
    0x005F3700, // "Dark Sword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x005F5E10, // "Black Knight Sword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x005F8520, // "Lorian's Greatsword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x005FAC30, // "Twin Princes' Greatsword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x005FD340, // "Lothric's Holy Sword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x005FFA50, // "Wolnir's Holy Sword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00602160, // "Wolf Knight's Greatsword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x0060216A, // "Greatsword of Artorias" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00604870, // "Hollowslayer Greatsword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00606F80, // "Moonlight Greatsword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00609690, // "Drakeblood Greatsword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x0060BDA0, // "Firelink Greatsword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x0060E4B0, // "Fume Ultra Greatsword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00610BC0, // "Old Wolf Curved Sword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x006132D0, // "Storm Ruler" DS3ItemCategory.WEAPON_UPGRADE_5
    0x006ACFC0, // "Hand Axe" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x006AF6D0, // "Battle Axe" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x006AFA54, // "Deep Battle Axe" DS3ItemCategory.WEAPON_UPGRADE_10
    0x006B1DE0, // "Brigand Axe" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x006B6C00, // "Crescent Axe" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x006B9310, // "Greataxe" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x006BE130, // "Butcher Knife" DS3ItemCategory.WEAPON_UPGRADE_10
    0x006C0840, // "Dragonslayer's Axe" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x006C5660, // "Thrall Axe" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x006C7D70, // "Dragonslayer Greataxe" DS3ItemCategory.WEAPON_UPGRADE_5
    0x006CA480, // "Demon's Greataxe" DS3ItemCategory.WEAPON_UPGRADE_5
    0x006CCB90, // "Eleonora" DS3ItemCategory.WEAPON_UPGRADE_5
    0x006D19B0, // "Man Serpent Hatchet" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x007A1200, // "Club" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x007A3910, // "Mace" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x007A6020, // "Morning Star" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x007A8730, // "Reinforced Club" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x007AFC60, // "Large Club" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x007B4A80, // "Great Club" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x007BBFB0, // "Great Mace" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x007C8300, // "Great Wooden Hammer" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x007CAA10, // "Gargoyle Flame Hammer" DS3ItemCategory.WEAPON_UPGRADE_5
    0x007CD120, // "Vordt's Great Hammer" DS3ItemCategory.WEAPON_UPGRADE_5
    0x007CF830, // "Old King's Great Hammer" DS3ItemCategory.WEAPON_UPGRADE_5
    0x007D6D60, // "Heysel Pick" DS3ItemCategory.WEAPON_UPGRADE_5
    0x007DBB80, // "Warpick" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x007DE290, // "Pickaxe" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x007E09A0, // "Pickaxe" DS3ItemCategory.WEAPON_UPGRADE_5
    0x007E30B0, // "Smough's Great Hammer" DS3ItemCategory.WEAPON_UPGRADE_5
    0x007E57C0, // "Blacksmith Hammer" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x007E7ED0, // "Morne's Great Hammer" DS3ItemCategory.WEAPON_UPGRADE_5
    0x007EA5E0, // "Spiked Mace" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00895440, // "Spear" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00897B50, // "Winged Spear" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x0089C970, //  DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x008A8CC0, // "Greatlance" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x008AB3D0, // "Lothric Knight Long Spear" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x008B01F0, // "Gargoyle Flame Spear" DS3ItemCategory.WEAPON_UPGRADE_5
    0x008B2900, // "Rotten Ghru Spear" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x008B5010, // "Tailbone Spear" DS3ItemCategory.WEAPON_UPGRADE_5
    0x008B7720, // "Soldering Iron" DS3ItemCategory.WEAPON_UPGRADE_10
    0x008BC540, // "Dragonslayer Swordspear" DS3ItemCategory.WEAPON_UPGRADE_5
    0x008BEC50, // "Arstor's Spear" DS3ItemCategory.WEAPON_UPGRADE_5
    0x008C1360, // "Saint Bident" DS3ItemCategory.WEAPON_UPGRADE_10
    0x008C3A70, // "Yorshka's Spear" DS3ItemCategory.WEAPON_UPGRADE_5
    0x008C6180, // "Pike" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x008ADAE0, // "Heavy Four-pronged Plow" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x008CAFA0, // "Dragonslayer Spear" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00989680, // "Great Scythe" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x0098BD90, // "Lucerne" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x0098E4A0, // "Glaive" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00990BB0, // "Halberd" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x009959D0, // "Black Knight Greataxe" DS3ItemCategory.WEAPON_UPGRADE_5
    0x0099A7F0, // "Pontiff Knight Great Scythe" DS3ItemCategory.WEAPON_UPGRADE_5
    0x0099CF00, // "Great Corvian Scythe" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x0099F610, // "Winged Knight Halberd" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x009A1D20, // "Gundyr's Halberd" DS3ItemCategory.WEAPON_UPGRADE_5
    0x009AB960, // "Red Hilted Halberd" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x009AE070, // "Black Knight Glaive" DS3ItemCategory.WEAPON_UPGRADE_5
    0x009B0780, // "Immolation Tinder" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00A7D8C0, // "Claw" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00A7FFD0, // "Caestus" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00A826E0, // "Manikin Claws" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00A84DF0, // "Demon's Fist" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00A87500, // "Dark Hand" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00B71B00, // "Whip" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00B7B740, // "Witch's Locks" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00B7DE50, // "Notched Whip" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00B80560, // "Spotted Whip" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00C72090, // "Talisman" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00C747A0, // "Sorcerer's Staff" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00C76EB0, // "Storyteller's Staff" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00C795C0, // "Mendicant's Staff" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00C7E3E0, // "Man-grub's Staff" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00C80AF0, // "Archdeacon's Great Staff" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00C83200, // "Golden Ritual Spear" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00C88020, // "Yorshka's Chime" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00C8CE40, // "Sage's Crystal Staff" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00C8F550, // "Heretic's Staff" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00C91C60, // "Court Sorcerer's Staff" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00C94370, // "Witchtree Branch" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00C96A80, // "Izalith Staff" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00C99190, // "Cleric's Sacred Chime" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00C9B8A0, // "Priest's Chime" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00C9DFB0, // "Saint-tree Bellvine" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00CA06C0, // "Caitha's Chime" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00CA2DD0, // "Crystal Chime" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00CA54E0, // "Sunlight Talisman" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00CA7BF0, // "Canvas Talisman" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00CAA300, // "Sunless Talisman" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00CACA10, // "Saint's Talisman" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00CAF120, // "White Hair Talisman" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00CC77C0, // "Pyromancy Flame" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00CF8500, // "Dragonslayer Greatbow" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00D5C690, // "Short Bow" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00D5EDA0, // "Composite Bow" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00D63BC0, // "Light Crossbow" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00D662D0, // "Arbalest" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00D689E0, // "Longbow" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00D6B0F0, // "Dragonrider Bow" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00D6FF10, // "Avelyn" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00D72620, // "Knight's Crossbow" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00D74D30, // "Heavy Crossbow" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00D79B50, // "Darkmoon Longbow" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00D7C260, // "Onislayer Greatbow" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00D7E970, // "Black Bow of Pharis" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00D83790, // "Sniper Crossbow" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00F42400, // "Sellsword Twinblades" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00F47220, // "Warden Twinblades" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00F49930, // "Winged Knight Twinaxes" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00F4C040, // "Dancer's Enchanted Swords" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00F4E750, // "Great Machete" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00F50E60, // "Brigand Twindaggers" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00F53570, // "Gotthard Twinswords" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00F58390, // "Onikiri and Ubadachi" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00F5AAA0, // "Drang Twinspears" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00F61FD0, // "Drang Hammers" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE

        # Shields
    0x01312D00, // "Buckler" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01315410, // "Small Leather Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0131A230, // "Round Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0131C940, // "Large Leather Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01323E70, // "Hawkwood's Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01326580, // "Iron Round Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0132DAB0, // "Wooden Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x013301C0, // "Kite Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x013328D0, // "Ghru Rotshield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x013376F0, // "Havel's Greatshield" DS3ItemCategory.SHIELD
    0x01339E00, // "Target Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0133C510, // "Elkhorn Round Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0133EC20, // "Warrior's Round Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01341330, // "Caduceus Round Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01343A40, // "Red and White Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01343FB9, // "Blessed Red and White Shield+1" DS3ItemCategory.SHIELD
    0x01346150, // "Plank Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01348860, // "Leather Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0134AF70, // "Crimson Parma" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0134D680, // "Eastern Iron Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0134FD90, // "Llewellyn Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01354BB0, // "Golden Falcon Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x013572C0, // "Sacred Bloom Shield" DS3ItemCategory.SHIELD
    0x013599D0, // "Ancient Dragon Greatshield" DS3ItemCategory.SHIELD
    0x01409650, // "Lothric Knight Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01410B80, // "Knight Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x014159A0, // "Pontiff Knight Shield" DS3ItemCategory.SHIELD
    0x014180B0, // "Carthus Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0141F5E0, // "Black Knight Shield" DS3ItemCategory.SHIELD
    0x01424400, // "Silver Knight Shield" DS3ItemCategory.SHIELD
    0x01426B10, // "Spiked Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01429220, // "Pierce Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0142B930, // "East-West Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0142E040, // "Sunlight Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01430750, // "Crest Shield" DS3ItemCategory.SHIELD
    0x01432E60, // "Dragon Crest Shield" DS3ItemCategory.SHIELD
    0x01435570, // "Spider Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01437C80, // "Grass Crest Shield" DS3ItemCategory.SHIELD
    0x0143A390, // "Sunset Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0143CAA0, // "Golden Wing Crest Shield" DS3ItemCategory.SHIELD
    0x0143F1B0, // "Blue Wooden Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x014418C0, // "Silver Eagle Kite Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01443FD0, // "Stone Parma" DS3ItemCategory.SHIELD_INFUSIBLE
    0x014466E0, // "Spirit Tree Crest Shield" DS3ItemCategory.SHIELD
    0x01448DF0, // "Porcine Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0144B500, // "Shield of Want" DS3ItemCategory.SHIELD
    0x0144DC10, // "Wargod Wooden Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x014FD890, // "Lothric Knight Greatshield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x014FFFA0, // "Cathedral Knight Greatshield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01504DC0, // "Dragonslayer Greatshield" DS3ItemCategory.SHIELD
    0x015074D0, // "Moaning Shield" DS3ItemCategory.SHIELD
    0x0150C2F0, // "Yhorm's Greatshield" DS3ItemCategory.SHIELD
    0x0150EA00, // "Black Iron Greatshield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01511110, // "Wolf Knight's Greatshield" DS3ItemCategory.SHIELD
    0x01513820, // "Twin Dragon Greatshield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x01515F30, // "Greatshield of Glory" DS3ItemCategory.SHIELD
    0x01518640, // "Curse Ward Greatshield" DS3ItemCategory.SHIELD
    0x0151AD50, // "Bonewheel Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0151D460, // "Stone Greatshield" DS3ItemCategory.SHIELD_INFUSIBLE

        # Armor
    0x1121EAC0, // "Fallen Knight Helm"
    0x1121EEA8, // "Fallen Knight Armor"
    0x1121F290, // "Fallen Knight Gauntlets"
    0x1121F678, // "Fallen Knight Trousers"
    0x11298BE0, // "Knight Helm"
    0x11298FC8, // "Knight Armor"
    0x112993B0, // "Knight Gauntlets"
    0x11299798, // "Knight Leggings"
    0x11406F40, // "Firelink Helm"
    0x11407328, // "Firelink Armor"
    0x11407710, // "Firelink Gauntlets"
    0x11407AF8, // "Firelink Leggings"
    0x11481060, // "Sellsword Helm"
    0x11481448, // "Sellsword Armor"
    0x11481830, // "Sellsword Gauntlet"
    0x11481C18, // "Sellsword Trousers"
    0x114FB180, // "Herald Helm"
    0x114FB568, // "Herald Armor"
    0x114FB950, // "Herald Gloves"
    0x114FBD38, // "Herald Trousers"
    0x115752A0, // "Sunless Veil"
    0x11575688, // "Sunless Armor"
    0x11575A70, // "Sunless Gauntlets"
    0x11575E58, // "Sunless Leggings"
    0x115EF3C0, // "Black Hand Hat"
    0x115EF7A8, // "Black Hand Armor"
    0x115EFB90, // "Assassin Gloves"
    0x115EFF78, // "Assassin Trousers"
    0x11607A60, // "Assassin Hood"
    0x11607E48, // "Assassin Armor"
    0x116694E0, // "Xanthous Crown"
    0x116698C8, // "Xanthous Overcoat"
    0x11669CB0, // "Xanthous Gloves"
    0x1166A098, // "Xanthous Trousers"
    0x116E3600, // "Northern Helm"
    0x116E39E8, // "Northern Armor"
    0x116E3DD0, // "Northern Gloves"
    0x116E41B8, // "Northern Trousers"
    0x1175D720, // "Morne's Helm"
    0x1175DB08, // "Morne's Armor"
    0x1175DEF0, // "Morne's Gauntlets"
    0x1175E2D8, // "Morne's Leggings"
    0x117D7840, // "Silver Mask"
    0x117D7C28, // "Leonhard's Garb"
    0x117D8010, // "Leonhard's Gauntlets"
    0x117D83F8, // "Leonhard's Trousers"
    0x11851960, // "Sneering Mask"
    0x11851D48, // "Pale Shade Robe"
    0x11852130, // "Pale Shade Gloves"
    0x11852518, // "Pale Shade Trousers"
    0x118CBA80, // "Sunset Helm"
    0x118CBE68, // "Sunset Armor"
    0x118CC250, // "Sunset Gauntlets"
    0x118CC638, // "Sunset Leggings"
    0x11945BA0, // "Old Sage's Blindfold"
    0x11945F88, // "Cornyx's Garb"
    0x11946370, // "Cornyx's Wrap"
    0x11946758, // "Cornyx's Skirt"
    0x119BFCC0, // "Executioner Helm"
    0x119C00A8, // "Executioner Armor"
    0x119C0490, // "Executioner Gauntlets"
    0x119C0878, // "Executioner Leggings"
    0x11A39DE0, // "Billed Mask"
    0x11A3A1C8, // "Black Dress"
    0x11A3A5B0, // "Black Gauntlets"
    0x11A3A998, // "Black Leggings"
    0x11AB3F00, // "Pyromancer Crown"
    0x11AB42E8, // "Pyromancer Garb"
    0x11AB46D0, // "Pyromancer Wrap"
    0x11AB4AB8, // "Pyromancer Trousers"
    0x11BA8140, // "Court Sorcerer Hood"
    0x11BA8528, // "Court Sorcerer Robe"
    0x11BA8910, // "Court Sorcerer Gloves"
    0x11BA8CF8, // "Court Sorcerer Trousers"
    0x11C9C380, // "Sorcerer Hood"
    0x11C9C768, // "Sorcerer Robe"
    0x11C9CB50, // "Sorcerer Gloves"
    0x11C9CF38, // "Sorcerer Trousers"
    0x11CB4E08, // "Clandestine Coat"
    0x11D905C0, // "Cleric Hat"
    0x11D909A8, // "Cleric Blue Robe"
    0x11D90D90, // "Cleric Gloves"
    0x11D91178, // "Cleric Trousers"
    0x12625A00, // "Steel Soldier Helm"
    0x12625DE8, // "Deserter Armor"
    0x126265B8, // "Deserter Trousers"
    0x12656740, // "Thief Mask"
    0x129020C0, // "Sage's Big Hat"
    0x129F6300, // "Aristocrat's Mask"
    0x129F66E8, // "Jailer Robe"
    0x129F6AD0, // "Jailer Gloves"
    0x129F6EB8, // "Jailer Trousers"
    0x12BDE780, // "Grave Warden Hood"
    0x12BDEB68, // "Grave Warden Robe"
    0x12BDEF50, // "Grave Warden Wrap"
    0x12BDF338, // "Grave Warden Skirt"
    0x12CD29C0, // "Worker Hat"
    0x12CD2DA8, // "Worker Garb"
    0x12CD3190, // "Worker Gloves"
    0x12CD3578, // "Worker Trousers"
    0x12D4CAE0, // "Thrall Hood"
    0x12DC6C00, // "Evangelist Hat"
    0x12DC6FE8, // "Evangelist Robe"
    0x12DC73D0, // "Evangelist Gloves"
    0x12DC77B8, // "Evangelist Trousers"
    0x12E41108, // "Scholar's Robe"
    0x12EBAE40, // "Winged Knight Helm"
    0x12EBB228, // "Winged Knight Armor"
    0x12EBB610, // "Winged Knight Gauntlets"
    0x12EBB9F8, // "Winged Knight Leggings"
    0x130291A0, // "Cathedral Knight Helm"
    0x13029588, // "Cathedral Knight Armor"
    0x13029970, // "Cathedral Knight Gauntlets"
    0x13029D58, // "Cathedral Knight Leggings"
    0x13197500, // "Lothric Knight Helm"
    0x131978E8, // "Lothric Knight Armor"
    0x13197CD0, // "Lothric Knight Gauntlets"
    0x131980B8, // "Lothric Knight Leggings"
    0x1328B740, // "Outrider Knight Helm"
    0x1328BB28, // "Outrider Knight Armor"
    0x1328BF10, // "Outrider Knight Gauntlets"
    0x1328C2F8, // "Outrider Knight Leggings"
    0x1337F980, // "Black Knight Helm"
    0x1337FD68, // "Black Knight Armor"
    0x13380150, // "Black Knight Gauntlets"
    0x13380538, // "Black Knight Leggings"
    0x133F9AA0, // "Dark Mask"
    0x133F9E88, // "Dark Armor"
    0x133FA270, // "Dark Gauntlets"
    0x133FA658, // "Dark Leggings"
    0x13473BC0, // "Exile Mask"
    0x13473FA8, // "Exile Armor"
    0x13474390, // "Exile Gauntlets"
    0x13474778, // "Exile Leggings"
    0x13567E00, // "Pontiff Knight Crown"
    0x135681E8, // "Pontiff Knight Armor"
    0x135685D0, // "Pontiff Knight Gauntlets"
    0x135689B8, // "Pontiff Knight Leggings"
    0x1365C040, // "Golden Crown"
    0x1365C428, // "Dragonscale Armor"
    0x1365C810, // "Golden Bracelets"
    0x1365CBF8, // "Dragonscale Waistcloth"
    0x136D6160, // "Wolnir's Crown"
    0x13750280, // "Undead Legion Helm"
    0x13750668, // "Undead Legion Armor"
    0x13750A50, // "Undead Legion Gauntlet"
    0x13750E38, // "Undead Legion Leggings"
    0x13938700, // "Fire Witch Helm"
    0x13938AE8, // "Fire Witch Armor"
    0x13938ED0, // "Fire Witch Gauntlets"
    0x139392B8, // "Fire Witch Leggings"
    0x13A2C940, // "Lorian's Helm"
    0x13A2CD28, // "Lorian's Armor"
    0x13A2D110, // "Lorian's Gauntlets"
    0x13A2D4F8, // "Lorian's Leggings"
    0x13AA6A60, // "Hood of Prayer"
    0x13AA6E48, // "Robe of Prayer"
    0x13AA7618, // "Skirt of Prayer"
    0x13C14DC0, // "Dancer's Crown"
    0x13C151A8, // "Dancer's Armor"
    0x13C15590, // "Dancer's Gauntlets"
    0x13C15978, // "Dancer's Leggings"
    0x13D09000, // "Gundyr's Helm"
    0x13D093E8, // "Gundyr's Armor"
    0x13D097D0, // "Gundyr's Gauntlets"
    0x13D09BB8, // "Gundyr's Leggings"
    0x13EF1480, // "Archdeacon White Crown"
    0x13EF1868, // "Archdeacon Holy Garb"
    0x13EF2038, // "Archdeacon Skirt"
    0x13F6B988, // "Deacon Robe"
    0x13F6C158, // "Deacon Skirt"
    0x140D9CE8, // "Fire Keeper Robe"
    0x140DA0D0, // "Fire Keeper Gloves"
    0x140DA4B8, // "Fire Keeper Skirt"
    0x142C1D80, // "Chain Helm"
    0x142C2168, // "Chain Armor"
    0x142C2550, // "Leather Gauntlets"
    0x142C2938, // "Chain Leggings"
    0x143B5FC0, // "Nameless Knight Helm"
    0x143B63A8, // "Nameless Knight Armor"
    0x143B6790, // "Nameless Knight Gauntlets"
    0x143B6B78, // "Nameless Knight Leggings"
    0x144AA200, // "Elite Knight Helm"
    0x144AA5E8, // "Elite Knight Armor"
    0x144AA9D0, // "Elite Knight Gauntlets"
    0x144AADB8, // "Elite Knight Leggings"
    0x1459E440, // "Faraam Helm"
    0x1459E828, // "Faraam Armor"
    0x1459EC10, // "Faraam Gauntlets"
    0x1459EFF8, // "Faraam Boots"
    0x14692680, // "Catarina Helm"
    0x14692A68, // "Catarina Armor"
    0x14692E50, // "Catarina Gauntlets"
    0x14693238, // "Catarina Leggings"
    0x1470C7A0, // "Standard Helm"
    0x1470CB88, // "Hard Leather Armor"
    0x1470CF70, // "Hard Leather Gauntlets"
    0x1470D358, // "Hard Leather Boots"
    0x147868C0, // "Havel's Helm"
    0x14786CA8, // "Havel's Armor"
    0x14787090, // "Havel's Gauntlets"
    0x14787478, // "Havel's Leggings"
    0x148009E0, // "Brigand Hood"
    0x14800DC8, // "Brigand Armor"
    0x148011B0, // "Brigand Gauntlets"
    0x14801598, // "Brigand Trousers"
    0x1487AB00, // "Pharis's Hat"
    0x1487AEE8, // "Leather Armor"
    0x1487B2D0, // "Leather Gloves"
    0x1487B6B8, // "Leather Boots"
    0x148F4C20, // "Ragged Mask"
    0x148F5008, // "Master's Attire"
    0x148F53F0, // "Master's Gloves"
    0x148F57D8, // "Loincloth"
    0x1496ED40, // "Old Sorcerer Hat"
    0x1496F128, // "Old Sorcerer Coat"
    0x1496F510, // "Old Sorcerer Gauntlets"
    0x1496F8F8, // "Old Sorcerer Boots"
    0x149E8E60, // "Conjurator Hood"
    0x149E9248, // "Conjurator Robe"
    0x149E9630, // "Conjurator Manchettes"
    0x149E9A18, // "Conjurator Boots"
    0x14A63368, // "Black Leather Armor"
    0x14A63750, // "Black Leather Gloves"
    0x14A63B38, // "Black Leather Boots"
    0x14ADD0A0, // "Symbol of Avarice"
    0x14B571C0, // "Creighton's Steel Mask"
    0x14B575A8, // "Mirrah Chain Mail"
    0x14B57990, // "Mirrah Chain Gloves"
    0x14B57D78, // "Mirrah Chain Leggings"
    0x14BD12E0, // "Maiden Hood"
    0x14BD16C8, // "Maiden Robe"
    0x14BD1AB0, // "Maiden Gloves"
    0x14BD1E98, // "Maiden Skirt"
    0x14C4B400, // "Alva Helm"
    0x14C4B7E8, // "Alva Armor"
    0x14C4BBD0, // "Alva Gauntlets"
    0x14C4BFB8, // "Alva Leggings"
    0x14D3F640, // "Shadow Mask"
    0x14D3FA28, // "Shadow Garb"
    0x14D3FE10, // "Shadow Gauntlets"
    0x14D401F8, // "Shadow Leggings"
    0x14E33880, // "Eastern Helm"
    0x14E33C68, // "Eastern Armor"
    0x14E34050, // "Eastern Gauntlets"
    0x14E34438, // "Eastern Leggings"
    0x14F27AC0, // "Helm of Favor"
    0x14F27EA8, // "Embraced Armor of Favor"
    0x14F28290, // "Gauntlets of Favor"
    0x14F28678, // "Leggings of Favor"
    0x1501BD00, // "Brass Helm"
    0x1501C0E8, // "Brass Armor"
    0x1501C4D0, // "Brass Gauntlets"
    0x1501C8B8, // "Brass Leggings"
    0x1510FF40, // "Silver Knight Helm"
    0x15110328, // "Silver Knight Armor"
    0x15110710, // "Silver Knight Gauntlets"
    0x15110AF8, // "Silver Knight Leggings"
    0x15204180, // "Lucatiel's Mask"
    0x15204568, // "Mirrah Vest"
    0x15204950, // "Mirrah Gloves"
    0x15204D38, // "Mirrah Trousers"
    0x152F83C0, // "Iron Helm"
    0x152F87A8, // "Armor of the Sun"
    0x152F8B90, // "Iron Bracelets"
    0x152F8F78, // "Iron Leggings"
    0x153EC600, // "Drakeblood Helm"
    0x153EC9E8, // "Drakeblood Armor"
    0x153ECDD0, // "Drakeblood Gauntlets"
    0x153ED1B8, // "Drakeblood Leggings"
    0x154E0C28, // "Drang Armor"
    0x154E1010, // "Drang Gauntlets"
    0x154E13F8, // "Drang Shoes"
    0x155D4A80, // "Black Iron Helm"
    0x155D4E68, // "Black Iron Armor"
    0x155D5250, // "Black Iron Gauntlets"
    0x155D5638, // "Black Iron Leggings"
    0x156C8CC0, // "Painting Guardian Hood"
    0x156C90A8, // "Painting Guardian Gown"
    0x156C9490, // "Painting Guardian Gloves"
    0x156C9878, // "Painting Guardian Waistcloth"
    0x157BCF00, // "Wolf Knight Helm"
    0x157BD2E8, // "Wolf Knight Armor"
    0x157BD6D0, // "Wolf Knight Gauntlets"
    0x157BDAB8, // "Wolf Knight Leggings"
    0x158B1140, // "Dragonslayer Helm"
    0x158B1528, // "Dragonslayer Armor"
    0x158B1910, // "Dragonslayer Gauntlets"
    0x158B1CF8, // "Dragonslayer Leggings"
    0x159A5380, // "Smough's Helm"
    0x159A5768, // "Smough's Armor"
    0x159A5B50, // "Smough's Gauntlets"
    0x159A5F38, // "Smough's Leggings"
    0x15B8D800, // "Helm of Thorns"
    0x15B8DBE8, // "Armor of Thorns"
    0x15B8DFD0, // "Gauntlets of Thorns"
    0x15B8E3B8, // "Leggings of Thorns"
    0x15D75C80, // "Crown of Dusk"
    0x15D76068, // "Antiquated Dress"
    0x15D76450, // "Antiquated Gloves"
    0x15D76838, // "Antiquated Skirt"
    0x15E69EC0, // "Karla's Pointed Hat"
    0x15E6A2A8, // "Karla's Coat"
    0x15E6A690, // "Karla's Gloves"
    0x15E6AA78, // "Karla's Trousers"

        # Covenants
    0x20002710, // "Blade of the Darkmoon" DS3ItemCategory.UNIQUE
    0x20002724, // "Watchdogs of Farron" DS3ItemCategory.UNIQUE
    0x2000272E, // "Aldrich Faithful" DS3ItemCategory.UNIQUE
    0x20002738, // "Warrior of Sunlight" DS3ItemCategory.UNIQUE
    0x20002742, // "Mound-makers" DS3ItemCategory.UNIQUE
    0x2000274C, // "Way of Blue" DS3ItemCategory.UNIQUE
    0x20002756, // "Blue Sentinels" DS3ItemCategory.UNIQUE
    0x20002760, // "Rosaria's Fingers" DS3ItemCategory.UNIQUE
    0x2000276A, // "Spears of the Church" DS3ItemCategory.UNIQUE

        # Rings
    0x20004E20, // "Life Ring" DS3ItemCategory.RING
    0x20004E21, // "Life Ring+1" DS3ItemCategory.RING
    0x20004E22, // "Life Ring+2" DS3ItemCategory.RING
    0x20004E23, // "Life Ring+3" DS3ItemCategory.RING
    0x20004E2A, // "Chloranthy Ring" DS3ItemCategory.RING
    0x20004E2B, // "Chloranthy Ring+1" DS3ItemCategory.RING
    0x20004E2C, // "Chloranthy Ring+2" DS3ItemCategory.RING
    0x20004E34, // "Havel's Ring" DS3ItemCategory.RING
    0x20004E35, // "Havel's Ring+1" DS3ItemCategory.RING
    0x20004E36, // "Havel's Ring+2" DS3ItemCategory.RING
    0x20004E3E, // "Ring of Favor" DS3ItemCategory.RING
    0x20004E3F, // "Ring of Favor+1" DS3ItemCategory.RING
    0x20004E40, // "Ring of Favor+2" DS3ItemCategory.RING
    0x20004E48, // "Ring of Steel Protection" DS3ItemCategory.RING
    0x20004E49, // "Ring of Steel Protection+1" DS3ItemCategory.RING
    0x20004E4A, // "Ring of Steel Protection+2" DS3ItemCategory.RING
    0x20004E52, // "Flame Stoneplate Ring" DS3ItemCategory.RING
    0x20004E53, // "Flame Stoneplate Ring+1" DS3ItemCategory.RING
    0x20004E54, // "Flame Stoneplate Ring+2" DS3ItemCategory.RING
    0x20004E5C, // "Thunder Stoneplate Ring" DS3ItemCategory.RING
    0x20004E5D, // "Thunder Stoneplate Ring+1" DS3ItemCategory.RING
    0x20004E5E, // "Thunder Stoneplate Ring+2" DS3ItemCategory.RING
    0x20004E66, // "Magic Stoneplate Ring" DS3ItemCategory.RING
    0x20004E67, // "Magic Stoneplate Ring+1" DS3ItemCategory.RING
    0x20004E68, // "Magic Stoneplate Ring+2" DS3ItemCategory.RING
    0x20004E70, // "Dark Stoneplate Ring" DS3ItemCategory.RING
    0x20004E71, // "Dark Stoneplate Ring+1" DS3ItemCategory.RING
    0x20004E72, // "Dark Stoneplate Ring+2" DS3ItemCategory.RING
    0x20004E7A, // "Speckled Stoneplate Ring" DS3ItemCategory.RING
    0x20004E7B, // "Speckled Stoneplate Ring+1" DS3ItemCategory.RING
    0x20004E84, // "Bloodbite Ring" DS3ItemCategory.RING
    0x20004E85, // "Bloodbite Ring+1" DS3ItemCategory.RING
    0x20004E8E, // "Poisonbite Ring" DS3ItemCategory.RING
    0x20004E8F, // "Poisonbite Ring+1" DS3ItemCategory.RING
    0x20004E98, // "Cursebite Ring" DS3ItemCategory.RING
    0x20004EA2, // "Fleshbite Ring" DS3ItemCategory.RING
    0x20004EA3, // "Fleshbite Ring+1" DS3ItemCategory.RING
    0x20004EAC, // "Wood Grain Ring" DS3ItemCategory.RING
    0x20004EAD, // "Wood Grain Ring+1" DS3ItemCategory.RING
    0x20004EAE, // "Wood Grain Ring+2" DS3ItemCategory.RING
    0x20004EB6, // "Scholar Ring" DS3ItemCategory.RING
    0x20004EC0, // "Priestess Ring" DS3ItemCategory.RING
    0x20004ECA, // "Red Tearstone Ring" DS3ItemCategory.RING
    0x20004ED4, // "Blue Tearstone Ring" DS3ItemCategory.RING
    0x20004EDE, // "Wolf Ring" DS3ItemCategory.RING
    0x20004EDF, // "Wolf Ring+1" DS3ItemCategory.RING
    0x20004EE0, // "Wolf Ring+2" DS3ItemCategory.RING
    0x20004EE8, // "Leo Ring" DS3ItemCategory.RING
    0x20004EF2, // "Ring of Sacrifice" DS3ItemCategory.RING
    0x20004F06, // "Young Dragon Ring" DS3ItemCategory.RING
    0x20004F07, // "Bellowing Dragoncrest Ring" DS3ItemCategory.RING
    0x20004F10, // "Great Swamp Ring" DS3ItemCategory.RING
    0x20004F11, // "Witch's Ring" DS3ItemCategory.RING
    0x20004F1A, // "Morne's Ring" DS3ItemCategory.RING
    0x20004F1B, // "Ring of the Sun's First Born" DS3ItemCategory.RING
    0x20004F2E, // "Lingering Dragoncrest Ring" DS3ItemCategory.RING
    0x20004F2F, // "Lingering Dragoncrest Ring+1" DS3ItemCategory.RING
    0x20004F30, // "Lingering Dragoncrest Ring+2" DS3ItemCategory.RING
    0x20004F38, // "Sage Ring" DS3ItemCategory.RING
    0x20004F39, // "Sage Ring+1" DS3ItemCategory.RING
    0x20004F3A, // "Sage Ring+2" DS3ItemCategory.RING
    0x20004F42, // "Slumbering Dragoncrest Ring" DS3ItemCategory.RING
    0x20004F4C, // "Dusk Crown Ring" DS3ItemCategory.RING
    0x20004F56, // "Saint's Ring" DS3ItemCategory.RING
    0x20004F60, // "Deep Ring" DS3ItemCategory.RING
    0x20004F6A, // "Darkmoon Ring" DS3ItemCategory.RING
    0x20004F92, // "Hawk Ring" DS3ItemCategory.RING
    0x20004F9C, // "Hornet Ring" DS3ItemCategory.RING
    0x20004FA6, // "Covetous Gold Serpent Ring" DS3ItemCategory.RING
    0x20004FA7, // "Covetous Gold Serpent Ring+1" DS3ItemCategory.RING
    0x20004FA8, // "Covetous Gold Serpent Ring+2" DS3ItemCategory.RING
    0x20004FB0, // "Covetous Silver Serpent Ring" DS3ItemCategory.RING
    0x20004FB1, // "Covetous Silver Serpent Ring+1" DS3ItemCategory.RING
    0x20004FB2, // "Covetous Silver Serpent Ring+2" DS3ItemCategory.RING
    0x20004FBA, // "Sun Princess Ring" DS3ItemCategory.RING
    0x20004FC4, // "Silvercat Ring" DS3ItemCategory.RING
    0x20004FCE, // "Skull Ring" DS3ItemCategory.RING
    0x20004FD8, // "Untrue White Ring" DS3ItemCategory.RING
    0x20004FE2, // "Carthus Milkring" DS3ItemCategory.RING
    0x20004FEC, // "Knight's Ring" DS3ItemCategory.RING
    0x20004FF6, // "Hunter's Ring" DS3ItemCategory.RING
    0x20005000, // "Knight Slayer's Ring" DS3ItemCategory.RING
    0x2000500A, // "Magic Clutch Ring" DS3ItemCategory.RING
    0x20005014, // "Lightning Clutch Ring" DS3ItemCategory.RING
    0x2000501E, // "Fire Clutch Ring" DS3ItemCategory.RING
    0x20005028, // "Dark Clutch Ring" DS3ItemCategory.RING
    0x2000503C, // "Flynn's Ring" DS3ItemCategory.RING
    0x20005046, // "Prisoner's Chain" DS3ItemCategory.RING
    0x20005050, // "Untrue Dark Ring" DS3ItemCategory.RING
    0x20005064, // "Obscuring Ring" DS3ItemCategory.RING
    0x2000506E, // "Ring of the Evil Eye" DS3ItemCategory.RING
    0x2000506F, // "Ring of the Evil Eye+1" DS3ItemCategory.RING
    0x20005070, // "Ring of the Evil Eye+2" DS3ItemCategory.RING
    0x20005078, // "Calamity Ring" DS3ItemCategory.RING
    0x20005082, // "Farron Ring" DS3ItemCategory.RING
    0x2000508C, // "Aldrich's Ruby" DS3ItemCategory.RING
    0x20005096, // "Aldrich's Sapphire" DS3ItemCategory.RING
    0x200050B4, // "Lloyd's Sword Ring" DS3ItemCategory.RING
    0x200050BE, // "Lloyd's Shield Ring" DS3ItemCategory.RING
    0x200050DC, // "Estus Ring" DS3ItemCategory.RING
    0x200050E6, // "Ashen Estus Ring" DS3ItemCategory.RING
    0x200050F0, // "Horsehoof Ring" DS3ItemCategory.RING
    0x200050FA, // "Carthus Bloodring" DS3ItemCategory.RING
    0x20005104, // "Reversal Ring" DS3ItemCategory.RING
    0x2000510E, // "Pontiff's Right Eye" DS3ItemCategory.RING
    0x20005136, // "Pontiff's Left Eye" DS3ItemCategory.RING
    0x2000515E, // "Dragonscale Ring" DS3ItemCategory.RING

        # Items
    0x40000064, // "White Sign Soapstone" DS3ItemCategory.UNIQUE
    0x40000066, // "Red Sign Soapstone" DS3ItemCategory.UNIQUE
    0x40000066, // "Red Eye Orb" DS3ItemCategory.UNIQUE
    0x4000006C, // "Roster of Knights" DS3ItemCategory.UNIQUE
    0x4000006F, // "Cracked Red Eye Orb" DS3ItemCategory.MISC
    0x40000073, // "Black Eye Orb" DS3ItemCategory.UNIQUE
    0x400000F0, // "Divine Blessing" DS3ItemCategory.MISC
    0x400000F1, // "Hidden Blessing" DS3ItemCategory.MISC
    0x40000104, // "Green Blossom" DS3ItemCategory.MISC
    0x40000106, // "Budding Green Blossom" DS3ItemCategory.MISC
    0x4000010E, // "Bloodred Moss Clump" DS3ItemCategory.MISC
    0x4000010F, // "Purple Moss Clump" DS3ItemCategory.MISC
    0x40000110, // "Blooming Purple Moss Clump" DS3ItemCategory.MISC
    0x40000112, // "Purging Stone" DS3ItemCategory.MISC
    0x40000114, // "Rime-blue Moss Clump" DS3ItemCategory.MISC
    0x40000118, // "Repair Powder" DS3ItemCategory.MISC
    0x40000122, // "Kukri" DS3ItemCategory.MISC
    0x40000122, // "Kukri x5" DS3ItemCategory.MISC
    0x40000124, // "Firebomb" DS3ItemCategory.MISC
    0x40000124, // "Firebomb x2" DS3ItemCategory.MISC
    0x40000125, // "Dung Pie" DS3ItemCategory.MISC
    0x40000125, // "Dung Pie x3" DS3ItemCategory.MISC
    0x40000126, // "Alluring Skull" DS3ItemCategory.MISC
    0x40000128, // "Undead Hunter Charm" DS3ItemCategory.MISC
    0x40000129, // "Black Firebomb" DS3ItemCategory.MISC
    0x4000012B, // "Rope Firebomb" DS3ItemCategory.MISC
    0x4000012C, // "Lightning Urn" DS3ItemCategory.MISC
    0x4000012E, // "Rope Black Firebomb" DS3ItemCategory.MISC
    0x4000012F, // "Stalk Dung Pie" DS3ItemCategory.MISC
    0x40000130, // "Duel Charm" DS3ItemCategory.MISC
    0x40000136, // "Throwing Knife" DS3ItemCategory.MISC
    0x40000136, // "Throwing Knife x5" DS3ItemCategory.MISC
    0x40000137, // "Poison Throwing Knife" DS3ItemCategory.MISC
    0x4000014A, // "Charcoal Pine Resin" DS3ItemCategory.MISC
    0x4000014B, // "Gold Pine Resin" DS3ItemCategory.MISC
    0x4000014E, // "Human Pine Resin" DS3ItemCategory.MISC
    0x4000014F, // "Carthus Rouge" DS3ItemCategory.MISC
    0x40000150, // "Pale Pine Resin" DS3ItemCategory.MISC
    0x40000154, // "Charcoal Pine Bundle" DS3ItemCategory.MISC
    0x40000155, // "Gold Pine Bundle" DS3ItemCategory.MISC
    0x40000157, // "Rotten Pine Resin" DS3ItemCategory.MISC
    0x4000015E, // "Homeward Bone" DS3ItemCategory.MISC
    0x4000015F, // "Coiled Sword Fragment" DS3ItemCategory.UNIQUE
    0x4000016E, // "Wolf's Blood Swordgrass" DS3ItemCategory.MISC
    0x4000016F, // "Human Dregs" DS3ItemCategory.MISC
    0x40000170, // "Forked Pale Tongue" DS3ItemCategory.MISC
    0x40000171, // "Proof of a Concord Well Kept" DS3ItemCategory.MISC
    0x40000172, // "Prism Stone" DS3ItemCategory.MISC
    0x40000173, // "Binoculars" DS3ItemCategory.MISC
    0x40000174, // "Proof of a Concord Kept" DS3ItemCategory.MISC
    0x40000175, // "Pale Tongue" DS3ItemCategory.MISC
    0x40000176, // "Vertebra Shackle" DS3ItemCategory.MISC
    0x40000177, // "Sunlight Medal" DS3ItemCategory.MISC
    0x40000179, // "Dragon Head Stone" DS3ItemCategory.UNIQUE
    0x4000017A, // "Dragon Torso Stone" DS3ItemCategory.UNIQUE
    0x4000017C, // "Rubbish" DS3ItemCategory.MISC
    0x40000181, // "Dried Finger" DS3ItemCategory.UNIQUE
    0x40000183, // "Twinkling Dragon Head Stone" DS3ItemCategory.UNIQUE
    0x40000184, // "Twinkling Dragon Torso Stone" DS3ItemCategory.UNIQUE
    0x40000186, // "Fire Keeper Soul" DS3ItemCategory.UNIQUE
    0x40000190, // "Fading Soul" DS3ItemCategory.SOUL
    0x40000191, // "Soul of a Deserted Corpse" DS3ItemCategory.SOUL
    0x40000192, // "Large Soul of a Deserted Corpse" DS3ItemCategory.SOUL
    0x40000193, // "Soul of an Unknown Traveler" DS3ItemCategory.SOUL
    0x40000194, // "Large Soul of an Unknown Traveler" DS3ItemCategory.SOUL
    0x40000195, // "Soul of a Nameless Soldier" DS3ItemCategory.SOUL
    0x40000196, // "Large Soul of a Nameless Soldier" DS3ItemCategory.SOUL
    0x40000197, // "Soul of a Weary Warrior" DS3ItemCategory.SOUL
    0x40000198, // "Large Soul of a Weary Warrior" DS3ItemCategory.SOUL
    0x40000199, // "Soul of a Crestfallen Knight" DS3ItemCategory.SOUL
    0x4000019A, // "Large Soul of a Crestfallen Knight" DS3ItemCategory.SOUL
    0x4000019B, // "Soul of a Proud Paladin" DS3ItemCategory.SOUL
    0x4000019C, // "Large Soul of a Proud Paladin" DS3ItemCategory.SOUL
    0x4000019D, // "Soul of an Intrepid Hero" DS3ItemCategory.SOUL
    0x4000019E, // "Large Soul of an Intrepid Hero" DS3ItemCategory.SOUL
    0x4000019F, // "Soul of a Seasoned Warrior" DS3ItemCategory.SOUL
    0x400001A0, // "Large Soul of a Seasoned Warrior" DS3ItemCategory.SOUL
    0x400001A1, // "Soul of an Old Hand" DS3ItemCategory.SOUL
    0x400001A2, // "Soul of a Venerable Old Hand" DS3ItemCategory.SOUL
    0x400001A3, // "Soul of a Champion" DS3ItemCategory.SOUL
    0x400001A4, // "Soul of a Great Champion" DS3ItemCategory.SOUL
    0x400001B8, // "Seed of a Giant Tree" DS3ItemCategory.UNIQUE
    0x400001C4, // S3ItemData("Mossfruit" DS3ItemCategory.MISC
    0x400001C6, // "Young White Branch" DS3ItemCategory.MISC
    0x400001C7, // "Rusted Coin" DS3ItemCategory.MISC
    0x400001C8, // "Siegbräu" DS3ItemCategory.MISC
    0x400001C9, // S3ItemData("Rusted Gold Coin" DS3ItemCategory.MISC
    0x400001CA, // "Blue Bug Pellet" DS3ItemCategory.MISC
    0x400001CB, // "Red Bug Pellet" DS3ItemCategory.MISC
    0x400001CC, // "Yellow Bug Pellet" DS3ItemCategory.MISC
    0x400001CD, // "Black Bug Pellet" DS3ItemCategory.MISC
    0x400001CF, // "Young White Branch" DS3ItemCategory.MISC
    0x400001EA, // "Dark Sigil" DS3ItemCategory.MISC
    0x400001F4, // "Ember" DS3ItemCategory.MISC
    0x40000208, // "Hello Carving" DS3ItemCategory.UNIQUE
    0x40000209, // "Thank you Carving" DS3ItemCategory.UNIQUE
    0x4000020A, // "Very good! Carving" DS3ItemCategory.UNIQUE
    0x4000020B, // "I'm sorry Carving" DS3ItemCategory.UNIQUE
    0x4000020C, // "Help me! Carving" DS3ItemCategory.UNIQUE
    0x400002C8, // "Soul of Champion Gundyr" DS3ItemCategory.BOSS
    0x400002CA, // "Soul of the Dancer" DS3ItemCategory.BOSS
    0x400002CB, // "Soul of a Crystal Sage" DS3ItemCategory.BOSS
    0x400002CD, // "Soul of the Blood of the Wolf" DS3ItemCategory.BOSS
    0x400002CE, // "Soul of Consumed Oceiros" DS3ItemCategory.BOSS
    0x400002CF, // "Soul of Boreal Valley Vordt" DS3ItemCategory.BOSS
    0x400002D0, // "Soul of the Old Demon King" DS3ItemCategory.BOSS
    0x400002D1, // "Soul of Dragonslayer Armour" DS3ItemCategory.BOSS
    0x400002D2, // "Soul of the Nameless King" DS3ItemCategory.BOSS
    0x400002D4, // "Soul of Pontiff Sulyvahn" DS3ItemCategory.BOSS
    0x400002D5, // "Soul of Aldrich" DS3ItemCategory.BOSS
    0x400002D6, // "Soul of High Lord Wolnir" DS3ItemCategory.BOSS
    0x400002D7, // "Soul of the Rotted Greatwood" DS3ItemCategory.BOSS
    0x400002D8, // "Soul of Rosaria" DS3ItemCategory.BOSS
    0x400002D9, // "Soul of the Deacons of the Deep" DS3ItemCategory.BOSS
    0x400002DB, // "Soul of the Twin Princes" DS3ItemCategory.BOSS
    0x400002DC, // "Soul of Yhorm the Giant" DS3ItemCategory.BOSS
    0x400002DD, // "Soul of the Lords" DS3ItemCategory.BOSS
    0x400002E3, // "Soul of a Demon" DS3ItemCategory.BOSS
    0x400002E7, // "Soul of a Stray Demon" DS3ItemCategory.BOSS
    0x400003E8, // "Titanite Shard" DS3ItemCategory.UPGRADE
    0x400003E9, // "Large Titanite Shard" DS3ItemCategory.UPGRADE
    0x400003EA, // "Titanite Chunk" DS3ItemCategory.UPGRADE
    0x400003EB, // "Titanite Slab" DS3ItemCategory.UPGRADE
    0x400003FC, // "Titanite Scale" DS3ItemCategory.UPGRADE
    0x40000406, // "Twinkling Titanite" DS3ItemCategory.UPGRADE
    0x4000044C, // "Heavy Gem" DS3ItemCategory.UPGRADE
    0x40000456, // "Sharp Gem" DS3ItemCategory.UPGRADE
    0x40000460, // "Refined Gem" DS3ItemCategory.UPGRADE
    0x4000046A, // "Crystal Gem" DS3ItemCategory.UPGRADE
    0x40000474, // "Simple Gem" DS3ItemCategory.UPGRADE
    0x4000047E, // "Fire Gem" DS3ItemCategory.UPGRADE
    0x40000488, // "Chaos Gem" DS3ItemCategory.UPGRADE
    0x40000492, // "Lightning Gem" DS3ItemCategory.UPGRADE
    0x4000049C, // "Deep Gem" DS3ItemCategory.UPGRADE
    0x400004A6, // "Dark Gem" DS3ItemCategory.UPGRADE
    0x400004B0, // "Poison Gem" DS3ItemCategory.UPGRADE
    0x400004BA, // "Blood Gem" DS3ItemCategory.UPGRADE
    0x400004C4, // "Raw Gem" DS3ItemCategory.UPGRADE
    0x400004CE, // "Blessed Gem" DS3ItemCategory.UPGRADE
    0x400004D8, // "Hollow Gem" DS3ItemCategory.UPGRADE
    0x400004E2, // "Shriving Stone" DS3ItemCategory.UPGRADE
    0x400007D1, // "Lift Chamber Key" DS3ItemCategory.UNIQUE
    0x400007D5, // "Small Doll" DS3ItemCategory.UNIQUE
    0x400007D7, // "Jailbreaker's Key" DS3ItemCategory.UNIQUE
    0x400007D8, // "Jailer's Key Ring" DS3ItemCategory.UNIQUE
    0x400007D9, // "Grave Key" DS3ItemCategory.UNIQUE
    0x400007DA, // "Cell Key" DS3ItemCategory.UNIQUE
    0x400007DB, // "Dungeon Ground Floor Key" DS3ItemCategory.UNIQUE
    0x400007DC, // "Old Cell Key" DS3ItemCategory.UNIQUE
    0x400007DE, // "Grand Archives Key" DS3ItemCategory.UNIQUE
    0x400007DF, // "Tower Key" DS3ItemCategory.UNIQUE
    0x40000836, // "Small Lothric Banner" DS3ItemCategory.UNIQUE
    0x40000837, // "Farron Coal" DS3ItemCategory.UNIQUE
    0x40000838, // "Sage's Coal" DS3ItemCategory.UNIQUE
    0x40000839, // "Giant's Coal" DS3ItemCategory.UNIQUE
    0x4000083A, // "Profaned Coal" DS3ItemCategory.UNIQUE
    0x4000083B, // "Mortician's Ashes" DS3ItemCategory.UNIQUE
    0x4000083C, // "Dreamchaser's Ashes" DS3ItemCategory.UNIQUE
    0x4000083D, // "Paladin's Ashes" DS3ItemCategory.UNIQUE
    0x4000083E, // "Grave Warden's Ashes" DS3ItemCategory.UNIQUE
    0x4000083F, // "Greirat's Ashes" DS3ItemCategory.UNIQUE
    0x40000840, // "Orbeck's Ashes" DS3ItemCategory.UNIQUE
    0x40000841, // "Cornyx's Ashes" DS3ItemCategory.UNIQUE
    0x40000842, // "Karla's Ashes" DS3ItemCategory.UNIQUE
    0x40000843, // "Irina's Ashes" DS3ItemCategory.UNIQUE
    0x40000844, // "Yuria's Ashes" DS3ItemCategory.UNIQUE
    0x40000845, // "Basin of Vows" DS3ItemCategory.UNIQUE
    0x40000846, // "Loretta's Bone" DS3ItemCategory.UNIQUE
    0x40000847, // "Braille Divine Tome of Carim" DS3ItemCategory.UNIQUE
    0x40000848, // "Braille Divine Tome of Lothric" DS3ItemCategory.UNIQUE
    0x4000084B, // "Cinders of a Lord - Abyss Watcher" DS3ItemCategory.UNIQUE
    0x4000084C, // "Cinders of a Lord - Aldrich" DS3ItemCategory.UNIQUE
    0x4000084D, // "Cinders of a Lord - Yhorm the Giant" DS3ItemCategory.UNIQUE
    0x4000084E, // "Cinders of a Lord - Lothric Prince" DS3ItemCategory.UNIQUE
    0x4000084F, // "Great Swamp Pyromancy Tome" DS3ItemCategory.UNIQUE
    0x40000850, // "Carthus Pyromancy Tome" DS3ItemCategory.UNIQUE
    0x40000851, // "Izalith Pyromancy Tome" DS3ItemCategory.UNIQUE
    0x40000852, // "Quelana Pyromancy Tome" DS3ItemCategory.UNIQUE
    0x40000853, // "Grave Warden Pyromancy Tome" DS3ItemCategory.UNIQUE
    0x40000854, // "Sage's Scroll" DS3ItemCategory.UNIQUE
    0x40000855, // "Logan's Scroll" DS3ItemCategory.UNIQUE
    0x40000856, // "Crystal Scroll" DS3ItemCategory.UNIQUE
    0x40000857, // "Transposing Kiln" DS3ItemCategory.UNIQUE
    0x40000859, // "Coiled Sword" DS3ItemCategory.UNIQUE
    0x4000085A, // "Eyes of a Fire Keeper" DS3ItemCategory.UNIQUE
    0x4000085B, // "Sword of Avowal" DS3ItemCategory.UNIQUE
    0x4000085C, // "Golden Scroll" DS3ItemCategory.UNIQUE
    0x4000085D, // "Estus Shard" DS3ItemCategory.HEALING
    0x4000085E, // "Hawkwood's Swordgrass" DS3ItemCategory.UNIQUE
    0x4000085F, // "Undead Bone Shard" DS3ItemCategory.HEALING
    0x40000860, // "Deep Braille Divine Tome" DS3ItemCategory.UNIQUE
    0x40000861, // "Londor Braille Divine Tome" DS3ItemCategory.UNIQUE
    0x40000862, // "Excrement-covered Ashes" DS3ItemCategory.UNIQUE
    0x40000863, // "Prisoner Chief's Ashes" DS3ItemCategory.UNIQUE
    0x40000864, // "Xanthous Ashes" DS3ItemCategory.UNIQUE
    0x40000865, // "Hollow's Ashes" DS3ItemCategory.UNIQUE
    0x40000866, // "Patches' Ashes" DS3ItemCategory.UNIQUE
    0x40000867, // "Dragon Chaser's Ashes" DS3ItemCategory.UNIQUE
    0x40000868, // "Easterner's Ashes" DS3ItemCategory.UNIQUE

        # Spells
    0x40124F80, // "Farron Dart" DS3ItemCategory.SPELL
    0x40127690, // "Great Farron Dart" DS3ItemCategory.SPELL
    0x4013D620, // "Soul Arrow" DS3ItemCategory.SPELL
    0x4013DA08, // "Great Soul Arrow" DS3ItemCategory.SPELL
    0x4013DDF0, // "Heavy Soul Arrow" DS3ItemCategory.SPELL
    0x4013E1D8, // "Great Heavy Soul Arrow" DS3ItemCategory.SPELL
    0x4013E5C0, // "Homing Soulmass" DS3ItemCategory.SPELL
    0x4013E9A8, // "Homing Crystal Soulmass" DS3ItemCategory.SPELL
    0x4013ED90, // "Soul Spear" DS3ItemCategory.SPELL
    0x4013F178, // "Crystal Soul Spear" DS3ItemCategory.SPELL
    0x4013F560, // "Deep Soul" DS3ItemCategory.SPELL
    0x4013F948, // "Great Deep Soul" DS3ItemCategory.SPELL
    0x4013FD30, // "Magic Weapon" DS3ItemCategory.SPELL
    0x40140118, // "Great Magic Weapon" DS3ItemCategory.SPELL
    0x40140500, // "Crystal Magic Weapon" DS3ItemCategory.SPELL
    0x40144B50, // "Magic Shield" DS3ItemCategory.SPELL
    0x40144F38, // "Great Magic Shield" DS3ItemCategory.SPELL
    0x40147260, // "Hidden Weapon" DS3ItemCategory.SPELL
    0x40147648, // "Hidden Body" DS3ItemCategory.SPELL
    0x40149970, // "Cast Light" DS3ItemCategory.SPELL
    0x4014A528, // "Repair" DS3ItemCategory.SPELL
    0x4014A910, // "Spook" DS3ItemCategory.SPELL
    0x4014ACF8, // "Chameleon" DS3ItemCategory.SPELL
    0x4014B0E0, // "Aural Decoy" DS3ItemCategory.SPELL
    0x4014E790, // "White Dragon Breath" DS3ItemCategory.SPELL
    0x4014EF60, // "Farron Hail" DS3ItemCategory.SPELL
    0x4014F348, // "Crystal Hail" DS3ItemCategory.SPELL
    0x4014F730, // "Soul Greatsword" DS3ItemCategory.SPELL
    0x4014FB18, // "Farron Flashsword" DS3ItemCategory.SPELL
    0x401875B8, // "Affinity" DS3ItemCategory.SPELL
    0x40189CC8, // "Dark Edge" DS3ItemCategory.SPELL
    0x4018B820, // "Soul Stream" DS3ItemCategory.SPELL
    0x40193138, // "Twisted Wall of Light" DS3ItemCategory.SPELL
    0x401A8CE0, // "Pestilent Mist" DS3ItemCategory.SPELL
    0x40249F00, // "Fireball" DS3ItemCategory.SPELL
    0x4024A6D0, // "Fire Orb" DS3ItemCategory.SPELL
    0x4024AAB8, // "Firestorm" DS3ItemCategory.SPELL
    0x4024B288, // "Fire Surge" DS3ItemCategory.SPELL
    0x4024BA58, // "Black Serpent" DS3ItemCategory.SPELL
    0x4024C610, // "Combustion" DS3ItemCategory.SPELL
    0x4024C9F8, // "Great Combustion" DS3ItemCategory.SPELL
    0x4024ED20, // "Poison Mist" DS3ItemCategory.SPELL
    0x4024F108, // "Toxic Mist" DS3ItemCategory.SPELL
    0x4024F4F0, // "Acid Surge" DS3ItemCategory.SPELL
    0x40251430, // "Iron Flesh" DS3ItemCategory.SPELL
    0x40251818, // "Flash Sweat" DS3ItemCategory.SPELL
    0x402527B8, // "Carthus Flame Arc" DS3ItemCategory.SPELL
    0x40252BA0, // "Rapport" DS3ItemCategory.SPELL
    0x40253B40, // "Power Within" DS3ItemCategory.SPELL
    0x40256250, // "Great Chaos Fire Orb" DS3ItemCategory.SPELL
    0x40256638, // "Chaos Storm" DS3ItemCategory.SPELL
    0x40256A20, // "Fire Whip" DS3ItemCategory.SPELL
    0x40256E08, // "Black Flame" DS3ItemCategory.SPELL
    0x402575D8, // "Profaned Flame" DS3ItemCategory.SPELL
    0x402579C0, // "Chaos Bed Vestiges" DS3ItemCategory.SPELL
    0x4025B070, // "Warmth" DS3ItemCategory.SPELL
    0x402717D0, // "Profuse Sweat" DS3ItemCategory.SPELL
    0x4027D350, // "Black Fire Orb" DS3ItemCategory.SPELL
    0x4027FA60, // "Bursting Fireball" DS3ItemCategory.SPELL
    0x40282170, // "Boulder Heave" DS3ItemCategory.SPELL
    0x40284880, // "Sacred Flame" DS3ItemCategory.SPELL
    0x40286F90, // "Carthus Beacon" DS3ItemCategory.SPELL
    0x403540D0, // "Heal Aid" DS3ItemCategory.SPELL
    0x403567E0, // "Heal" DS3ItemCategory.SPELL
    0x40356BC8, // "Med Heal" DS3ItemCategory.SPELL
    0x40356FB0, // "Great Heal" DS3ItemCategory.SPELL
    0x40357398, // "Soothing Sunlight" DS3ItemCategory.SPELL
    0x40357780, // "Replenishment" DS3ItemCategory.SPELL
    0x40357B68, // "Bountiful Sunlight" DS3ItemCategory.SPELL
    0x40358338, // "Bountiful Light" DS3ItemCategory.SPELL
    0x40358720, // "Caressing Tears" DS3ItemCategory.SPELL
    0x4035B600, // "Tears of Denial" DS3ItemCategory.SPELL
    0x4035B9E8, // "Homeward" DS3ItemCategory.SPELL
    0x4035DD10, // "Force" DS3ItemCategory.SPELL
    0x4035E0F8, // "Wrath of the Gods" DS3ItemCategory.SPELL
    0x4035E4E0, // "Emit Force" DS3ItemCategory.SPELL
    0x40360420, // "Seek Guidance" DS3ItemCategory.SPELL
    0x40362B30, // "Lightning Spear" DS3ItemCategory.SPELL
    0x40362F18, // "Great Lightning Spear" DS3ItemCategory.SPELL
    0x40363300, // "Sunlight Spear" DS3ItemCategory.SPELL
    0x403636E8, // "Lightning Storm" DS3ItemCategory.SPELL
    0x40363AD0, // "Gnaw" DS3ItemCategory.SPELL
    0x40363EB8, // "Dorhys' Gnawing" DS3ItemCategory.SPELL
    0x40365240, // "Magic Barrier" DS3ItemCategory.SPELL
    0x40365628, // "Great Magic Barrier" DS3ItemCategory.SPELL
    0x40365DF8, // "Sacred Oath" DS3ItemCategory.SPELL
    0x4036A448, // "Vow of Silence" DS3ItemCategory.SPELL
    0x4036C770, // "Lightning Blade" DS3ItemCategory.SPELL
    0x4036CB58, // "Darkmoon Blade" DS3ItemCategory.SPELL
    0x40378AC0, // "Dark Blade" DS3ItemCategory.SPELL
    0x40387520, // "Dead Again" DS3ItemCategory.SPELL
    0x40389C30, // "Lightning Stake" DS3ItemCategory.SPELL
    0x4038C340, // "Divine Pillars of Light" DS3ItemCategory.SPELL
    0x4038EA50, // "Lifehunt Scythe" DS3ItemCategory.SPELL
    0x40395F80, // "Blessed Weapon" DS3ItemCategory.SPELL
    0x40398690, // "Deep Protection" DS3ItemCategory.SPELL
    0x4039ADA0, // "Atonement" DS3ItemCategory.SPELL
]

_dlc_items = [
    # Ammunition
    0x000623E0, // "Millwood Greatarrow" DS3ItemCategory.MISC

        # Weapons
    0x00116520, // "Aquamarine Dagger" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00118C30, // "Murky Hand Scythe" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00222E00, // "Onyx Blade" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00225510, // "Ringed Knight Straight Sword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00227C20, // "Gael's Greatsword" DS3ItemCategory.WEAPON_UPGRADE_5
    0x003EDDC0, // "Follower Sabre" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x003F04D0, // "Demon's Scar" DS3ItemCategory.WEAPON_UPGRADE_5
    0x004D35A0, // "Frayed Blade" DS3ItemCategory.WEAPON_UPGRADE_5
    0x006159E0, // "Harald Curved Greatsword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x006D67D0, // "Millwood Battle Axe" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x006D8EE0, // "Earth Seeker" DS3ItemCategory.WEAPON_UPGRADE_5
    0x007ECCF0, // "Quakestone Hammer" DS3ItemCategory.WEAPON_UPGRADE_5
    0x007EF400, // "Ledo's Great Hammer" DS3ItemCategory.WEAPON_UPGRADE_5
    0x008CD6B0, // "Follower Javelin" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x008CFDC0, // "Ringed Knight Spear" DS3ItemCategory.WEAPON_UPGRADE_5
    0x008D24D0, // "Lothric War Banner" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x008D4BE0, // "Crucifix of the Mad King" DS3ItemCategory.WEAPON_UPGRADE_5
    0x009B2E90, // "Splitleaf Greatsword" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x009B55A0, // "Friede's Great Scythe" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00A89C10, // "Crow Talons" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00B82C70, // "Rose of Ariandel" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00CC9ED0, // "Pyromancer's Parting Flame" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00CCC5E0, // "Murky Longstaff" DS3ItemCategory.WEAPON_UPGRADE_10
    0x00CCECF0, // "Sacred Chime of Filianore" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00CD1400, // "Preacher's Right Arm" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00D77440, // "White Birch Bow" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00D85EA0, // "Millwood Greatbow" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00D885B0, // "Repeating Crossbow" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00F5F8C0, // "Giant Door Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x00F646E0, // "Valorheart" DS3ItemCategory.WEAPON_UPGRADE_5
    0x00F66DF0, // "Crow Quills" DS3ItemCategory.WEAPON_UPGRADE_10_INFUSIBLE
    0x00F69500, // "Ringed Knight Paired Greatswords" DS3ItemCategory.WEAPON_UPGRADE_5

        # Shields
    0x0135C0E0, // "Follower Shield" DS3ItemCategory.SHIELD_INFUSIBLE
    0x0135E7F0, // "Dragonhead Shield" DS3ItemCategory.SHIELD
    0x01450320, // "Ethereal Oak Shield" DS3ItemCategory.SHIELD
    0x01452A30, // "Dragonhead Greatshield" DS3ItemCategory.SHIELD
    0x015F1AD0, // "Follower Torch" DS3ItemCategory.SHIELD

        # Armor
    0x11312D00, // "Vilhelm's Helm"
    0x113130E8, // "Vilhelm's Armor"
    0x113134D0, // "Vilhelm's Gauntlets"
    0x113138B8, // "Vilhelm's Leggings"
    0x11B2E408, // "Antiquated Plain Garb"
    0x11B2E7F0, // "Violet Wrappings"
    0x11B2EBD8, // "Loincloth 2"
    0x11C22260, // "Shira's Crown"
    0x11C22648, // "Shira's Armor"
    0x11C22A30, // "Shira's Gloves"
    0x11C22E18, // "Shira's Trousers"
    0x11E84800, // "Lapp's Helm"
    0x11E84BE8, // "Lapp's Armor"
    0x11E84FD0, // "Lapp's Gauntlets"
    0x11E853B8, // "Lapp's Leggings"
    0x134EDCE0, // "Slave Knight Hood"
    0x134EE0C8, // "Slave Knight Armor"
    0x134EE4B0, // "Slave Knight Gauntlets"
    0x134EE898, // "Slave Knight Leggings"
    0x135E1F20, // "Ordained Hood"
    0x135E2308, // "Ordained Dress"
    0x135E2AD8, // "Ordained Trousers"
    0x137CA3A0, // "Follower Helm"
    0x137CA788, // "Follower Armor"
    0x137CAB70, // "Follower Gloves"
    0x137CAF58, // "Follower Boots"
    0x139B2820, // "Millwood Knight Helm"
    0x139B2C08, // "Millwood Knight Armor"
    0x139B2FF0, // "Millwood Knight Gauntlets"
    0x139B33D8, // "Millwood Knight Leggings"
    0x13C8EEE0, // "Ringed Knight Hood"
    0x13C8F2C8, // "Ringed Knight Armor"
    0x13C8F6B0, // "Ringed Knight Gauntlets"
    0x13C8FA98, // "Ringed Knight Leggings"
    0x13D83508, // "Harald Legion Armor"
    0x13D838F0, // "Harald Legion Gauntlets"
    0x13D83CD8, // "Harald Legion Leggings"
    0x1405F7E0, // "Iron Dragonslayer Helm"
    0x1405FBC8, // "Iron Dragonslayer Armor"
    0x1405FFB0, // "Iron Dragonslayer Gauntlets"
    0x14060398, // "Iron Dragonslayer Leggings"
    0x14153A20, // "White Preacher Head"
    0x14CC5520, // "Ruin Helm"
    0x14CC5908, // "Ruin Armor"
    0x14CC5CF0, // "Ruin Gauntlets"
    0x14CC60D8, // "Ruin Leggings"
    0x14DB9760, // "Desert Pyromancer Hood"
    0x14DB9B48, // "Desert Pyromancer Garb"
    0x14DB9F30, // "Desert Pyromancer Gloves"
    0x14DBA318, // "Desert Pyromancer Skirt"
    0x14EAD9A0, // "Black Witch Hat"
    0x14EADD88, // "Black Witch Garb"
    0x14EAE170, // "Black Witch Wrappings"
    0x14EAE558, // "Black Witch Trousers"
    0x14FA1BE0, // "Black Witch Veil"
    0x15095E20, // "Blindfold Mask"

        # Covenants
    0x2000276A, // "Spear of the Church" DS3ItemCategory.UNIQUE

        # Rings
    0x20004E2D, // "Chloranthy Ring+3" DS3ItemCategory.RING
    0x20004E37, // "Havel's Ring+3" DS3ItemCategory.RING
    0x20004E41, // "Ring of Favor+3" DS3ItemCategory.RING
    0x20004E4B, // "Ring of Steel Protection+3" DS3ItemCategory.RING
    0x20004EE1, // "Wolf Ring+3" DS3ItemCategory.RING
    0x20004FA9, // "Covetous Gold Serpent Ring+3" DS3ItemCategory.RING
    0x20004FB3, // "Covetous Silver Serpent Ring+3" DS3ItemCategory.RING
    0x20005071, // "Ring of the Evil Eye+3" DS3ItemCategory.RING
    0x20005208, // "Chillbite Ring" DS3ItemCategory.RING

        # Items
    0x4000013B, // "Church Guardian Shiv" DS3ItemCategory.MISC
    0x4000017B, // "Filianore's Spear Ornament" DS3ItemCategory.UNIQUE
    0x4000028A, // "Ritual Spear Fragment" DS3ItemCategory.UNIQUE
    0x4000028B, // "Divine Spear Fragment" DS3ItemCategory.UNIQUE
    0x400002E8, // "Soul of Sister Friede" DS3ItemCategory.BOSS
    0x400002E9, // "Soul of Slave Knight Gael" DS3ItemCategory.BOSS
    0x400002EA, // "Soul of the Demon Prince" DS3ItemCategory.BOSS
    0x400002EB, // "Soul of Darkeater Midir" DS3ItemCategory.BOSS
    0x40000869, // "Champion's Bones" DS3ItemCategory.UNIQUE
    0x4000086A, // "Captain's Ashes" DS3ItemCategory.MISC
    0x4000086B, // "Contraption Key" DS3ItemCategory.UNIQUE
    0x4000086C, // "Small Envoy Banner" DS3ItemCategory.UNIQUE
    0x4000086D, // "Old Woman's Ashes" DS3ItemCategory.UNIQUE
    0x4000086E, // "Blood of the Dark Soul" DS3ItemCategory.UNIQUE

        # Spells
    0x401408E8, // "Frozen Weapon" DS3ItemCategory.SPELL
    0x4014FF00, // "Old Moonlight" DS3ItemCategory.SPELL
    0x401879A0, // "Great Soul Dregs" DS3ItemCategory.SPELL
    0x401A90C8, // "Snap Freeze" DS3ItemCategory.SPELL
    0x40257DA8, // "Floating Chaos" DS3ItemCategory.SPELL
    0x40258190, // "Flame Fan" DS3ItemCategory.SPELL
    0x402896A0, // "Seething Chaos" DS3ItemCategory.SPELL
    0x40358B08, // "Lightning Arrow" DS3ItemCategory.SPELL
    0x403642A0, // "Way of White Corona" DS3ItemCategory.SPELL
    0x40364688, // "Projected Heal" DS3ItemCategory.SPELL
]

// Unused list for future reference
// These items exist to some degree in the code, but aren't accessible
// in - game and can't be picked up without modifications
_cut_content_items = [
    # Weapons
    0x00100590, // "Blood-stained Short Sword" DS3ItemCategory.UNIQUE
    0x006C2F50, // "Missionary's Axe" DS3ItemCategory.UNIQUE
    0x006D40C0, // "Dragon King Greataxe" DS3ItemCategory.UNIQUE
    0x007D4650, // "Four Knights Hammer" DS3ItemCategory.UNIQUE
    0x007D9470, // "Hammer of the Great Tree" DS3ItemCategory.UNIQUE
    0x009A4430, // "Lothric's Scythe" DS3ItemCategory.UNIQUE
    0x009A6B40, // "Ancient Dragon Halberd" DS3ItemCategory.UNIQUE
    0x009A9250, // "Scythe of Want" DS3ItemCategory.UNIQUE
    0x00C8A730, // "Sacred Beast Catalyst" DS3ItemCategory.UNIQUE
    0x00CC9ED0, // "Deep Pyromancy Flame" DS3ItemCategory.UNIQUE
    0x00CD3B10, // "Flickering Pyromancy Flame" DS3ItemCategory.UNIQUE
    0x00CD6220, // "Strong Pyromancy Flame" DS3ItemCategory.UNIQUE
    0x00CDFE60, // "Deep Pyromancy Flame" DS3ItemCategory.UNIQUE
    0x00CE2570, // "Pitch-Dark Pyromancy Flame" DS3ItemCategory.UNIQUE
    0x00D77440, // "Dancer's Short Bow" DS3ItemCategory.UNIQUE
    0x00D81080, // "Shield Crossbow" DS3ItemCategory.UNIQUE
    0x00F55C80, // "Golden Dual Swords" DS3ItemCategory.UNIQUE
    0x008C8890, // "Channeler's Trident" DS3ItemCategory.UNIQUE

        # Shields
    0x013524A0, // "Cleric's Parma" DS3ItemCategory.UNIQUE
    0x01421CF0, // "Prince's Shield" DS3ItemCategory.UNIQUE

        # Armor
    0x11DA9048, // "Dingy Maiden's Overcoat" DS3ItemCategory.UNIQUE
    0x11F78A40, // "Grotto Hat" DS3ItemCategory.UNIQUE
    0x11F78E28, // "Grotto Robe" DS3ItemCategory.UNIQUE
    0x11F79210, // "Grotto Wrap" DS3ItemCategory.UNIQUE
    0x11F795F8, // "Grotto Trousers" DS3ItemCategory.UNIQUE
    0x126261D0, // "Soldier's Gauntlets" DS3ItemCategory.UNIQUE
    0x1263E0A0, // "Soldier's Hood" DS3ItemCategory.UNIQUE
    0x129024A8, // "Elder's Robe" DS3ItemCategory.UNIQUE
    0x12A70420, // "Saint's Veil" DS3ItemCategory.UNIQUE
    0x12A70808, // "Saint's Dress" DS3ItemCategory.UNIQUE
    0x12AEA540, // "Footman's Hood" DS3ItemCategory.UNIQUE
    0x12AEA928, // "Footman's Overcoat" DS3ItemCategory.UNIQUE
    0x12AEAD10, // "Footman's Bracelets" DS3ItemCategory.UNIQUE
    0x12AEB0F8, // "Footman's Trousers" DS3ItemCategory.UNIQUE
    0x12E40D20, // "Scholar's Shed Skin" DS3ItemCategory.UNIQUE
    0x138BE5E0, // "Man Serpent's Mask" DS3ItemCategory.UNIQUE
    0x138BE9C8, // "Man Serpent's Robe" DS3ItemCategory.UNIQUE
    0x13DFD240, // "Old Monarch's Crown" DS3ItemCategory.UNIQUE
    0x13DFD628, // "Old Monarch's Robe" DS3ItemCategory.UNIQUE
    0x13FE56C0, // "Frigid Valley Mask" DS3ItemCategory.UNIQUE
    0x140D9900, // "Dingy Hood" DS3ItemCategory.UNIQUE
    0x15A995C0, // "Hexer's Hood" DS3ItemCategory.UNIQUE
    0x15A999A8, // "Hexer's Robes" DS3ItemCategory.UNIQUE
    0x15A99D90, // "Hexer's Gloves" DS3ItemCategory.UNIQUE
    0x15A9A178, // "Hexer's Boots" DS3ItemCategory.UNIQUE
    0x15C81A40, // "Varangian Helm" DS3ItemCategory.UNIQUE
    0x15C81E28, // "Varangian Armor" DS3ItemCategory.UNIQUE
    0x15C82210, // "Varangian Cuffs" DS3ItemCategory.UNIQUE
    0x15C825F8, // "Varangian Leggings" DS3ItemCategory.UNIQUE

        # Rings
    0x20004EFC, // "Rare Ring of Sacrifice" DS3ItemCategory.UNIQUE
    0x20005032, // "Baneful Bird Ring" DS3ItemCategory.UNIQUE
    0x20004F7E, // "Darkmoon Blade Covenant Ring" DS3ItemCategory.UNIQUE
    0x2000505A, // "Yorgh's Ring" DS3ItemCategory.UNIQUE
    0x200050D2, // "Ring of Hiding" DS3ItemCategory.UNIQUE
    0x20005118, // "Ring of Sustained Toughness" DS3ItemCategory.UNIQUE
    0x20005122, // "Ring of Sustained Energy" DS3ItemCategory.UNIQUE
    0x2000512C, // "Ring of Sustained Magic" DS3ItemCategory.UNIQUE
    0x20005140, // "Ring of Sustained Essence" DS3ItemCategory.UNIQUE
    0x2000514A, // "Ring of Sustained Might" DS3ItemCategory.UNIQUE
    0x20005154, // "Ring of Sustained Fortune" DS3ItemCategory.UNIQUE

        # Items
    0x400002C9, // "Soul of a Wicked Spirit" DS3ItemCategory.UNIQUE

        # Spells
    0x4027AC40, // "Dark Orb" DS3ItemCategory.UNIQUE
    0x40359AA8, // "Morbid Temptation" DS3ItemCategory.UNIQUE
    0x40393870, // "Dorris Swarm" DS3ItemCategory.UNIQUE
]
