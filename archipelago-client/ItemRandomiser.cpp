#include <functional>

#include "AutoEquip.h"
#include "Core.h"
#include "GameHook.h"
#include "ItemRandomiser.h"

extern CCore* Core;
extern CItemRandomiser* ItemRandomiser;
extern CGameHook* GameHook;
extern CAutoEquip* AutoEquip;

void CItemRandomiser::HookedItemGib(void* mapItemMan, SItemBuffer* pItemBuffer, int32_t* pItemData) {

	// TODO: This check excludes pickle pee items but also dropped items, which may be desirable
	// for auto-equip mode. Figure out whether to remove it.
	if (*pItemData >= 0) ItemRandomiser->RandomiseItem(pItemBuffer);

	ItemRandomiser->ItemGibOriginal(mapItemMan, pItemBuffer, pItemData);

	if (*pItemData >= 0 && ItemRandomiser->dIsAutoEquip) AutoEquip->AutoEquipItem(pItemBuffer);
}


VOID CItemRandomiser::RandomiseItem(SItemBuffer* pItemBuffer) {

	if (pItemBuffer->length > 6) {
		Core->Panic("Too many items!", "...\\Source\\ItemRandomiser\\ItemRandomiser.cpp", FE_AmountTooHigh, 1);
		int3
	};

	int indexToRemove = -1;
	for (int i = 0; i < pItemBuffer->length; i++) {

		SItemBufferEntry* dItem = &pItemBuffer->items[i];

		spdlog::trace("IN itemID: {}", dItem->id);

		if (dItem->id > (0x40000000 + 3780000)) {
			// If we receive a synthetic item generated by the offline randomizer, it may be a
			// placeholder. If so, we need to replace it with its real equivalent.
			EquipParamGoodsRow* row = GetGoodsParam(dItem->id & 0xfffffffU);
			if (row->iconId == 7039)
			{
				// Notify the server that this location was checked.
				OnGetSyntheticItem(row);
				// If this is a Path of the Dragon replacement, remove it from the item list and grant the
				// gesture manually.
				GameHook->grantPathOfTheDragon();
				indexToRemove = i;
			} else if (row != NULL && row->basicPrice != 0) {
				// Since the function this hooks into only gets called after HookedItemGib, we
				// have to manually make sure it sees the original synthetic item so it can notify
				// the server that the location was checked.
				OnGetSyntheticItem(row);
				dItem->id = row->basicPrice;
				dItem->quantity = row->sellValue;
				dItem->durability = -1;
			}
		}
		else {
			//Nothing to do, this is a vanilla item so we will let it go to the player's inventory	
		}

		ItemRandomiser->ControlWeaponLevel(dItem);

		spdlog::trace("OUT itemID: {}", dItem->id);
	};

	if (indexToRemove != -1)
	{
		std::memcpy(&pItemBuffer[indexToRemove], &pItemBuffer[indexToRemove + 1],
			(pItemBuffer->length - 1) * sizeof(SItemBufferEntry));
		pItemBuffer->length--;
	}

	return;
}

VOID CItemRandomiser::ControlWeaponLevel(SItemBufferEntry* dItem) {

	auto dItemType = (ItemType)(dItem->id >> 0x1C);
	if (dItemType != ItemType::weapon) return;
	if ((dItem->id >> 0x10) == 6) return; // ammo

	spdlog::log(spdlog::level::info, "Controlling weapon level of {}", dItem->id);

	// find titanite count
	DWORD titaniteId = 0x400003E8;
	auto itemList = GameDataMan::instance()->localPlayerData->equipGameData1.equipInventoryData.list;
	uint32_t titaniteCount = 0;
	for (uint32_t i = 0; i < itemList.slotIdCap; i++) {
		auto item = itemList.itemsAboveCap[i];
		if (item.itemId == titaniteId) {
			titaniteCount = item.itemCount;
			break;
		}
	}

	auto baseId = dItem->id - (dItem->id % 100);
	dItem->id = baseId + titaniteCount;
}

// This function is called once each time the player receives an item with an ID they don't already
// have in their inventory. It's called _after_ HookedItemGib, so it'll only see the items that
// that has replaced.
uint64_t CItemRandomiser::HookedOnGetItem(void* pEquipInventoryData, uint32_t qItemCategory,
		uint32_t qItemID, uint32_t qCount, void* qUnknown2) {
	// This function is frequently called with very high item IDs while the game is loading
	// for unclear reasons. We want to ignore those calls.
	bool removeItem = false;
	if (qItemID < 0xA0000000 && Core->connected) {
		if (qItemCategory == 0 && qItemID > 23010000) {
			EquipParamWeaponRow* row = GetWeaponParam(qItemID & 0xfffffffU - qItemID % 100);
			if (row != NULL) {
				ItemRandomiser->OnGetSyntheticItem(
					row->vagrantItemLotId, row->vagrantBonuseneDropItemLotId);
			}
		} else if (qItemCategory == 0x10000000 && qItemID > 99003000) {
			EquipParamProtectorRow* row = GetProtectorParam(qItemID & 0xfffffffU);
			if (row != NULL) {
				ItemRandomiser->OnGetSyntheticItem(
					row->vagrantItemLotId, row->vagrantBonuseneDropItemLotId);
			}
		}
		else if (qItemCategory == 0x20000000 && qItemID > 3780000) {
			EquipParamAccessoryRow* row = GetAccessoryParam(qItemID & 0xfffffffU);
			if (row != NULL) {
				ItemRandomiser->OnGetSyntheticItem(
					row->vagrantItemLotId, row->vagrantBonusEneDropItemLotId);
			}
		} else if (qItemCategory == 0x40000000 && qItemID > 3780000) {
			EquipParamGoodsRow* row = GetGoodsParam(qItemID & 0xfffffffU);
			if (row != NULL) {
				ItemRandomiser->OnGetSyntheticItem(row);
				removeItem = row->disableUseAtColiseum;
			}
		}
	}

	auto result = ItemRandomiser->OnGetItemOriginal(pEquipInventoryData, qItemCategory, qItemID, qCount, qUnknown2);
	// If the player isn't connected to Archipelago, hold onto foreign items so that we can send
	// them out once they reconnect
	if (removeItem && Core->connected) GameHook->removeFromInventory(qItemCategory, qItemID);
	return result;
}

VOID CItemRandomiser::OnGetSyntheticItem(EquipParamGoodsRow* row) {
	// TODO: We shouldn't call this with non-AP items, but we do sometimes.
	if (row->vagrantItemLotId < 0) return;
	ItemRandomiser->OnGetSyntheticItem(row->vagrantItemLotId, row->vagrantBonusEneDropItemLotId);
}

// Tells the Archipelago server that a synthetic item was aquired (meaning that a location was
// visited and possibly that another world's item was received). The itemID should contain only the
// base ID, not the category flag.
//
// Returns the parameter data about the aquired item.
VOID CItemRandomiser::OnGetSyntheticItem(uint32_t archipelagoId1, uint32_t archipelagoId2) {
	int64_t archipelagoLocationId = archipelagoId1 + ((int64_t)(archipelagoId2) << 32);
	checkedLocationsList.push_front(archipelagoLocationId);
}

VOID CItemRandomiser::sendMissedItems() {
	auto itemList = GameDataMan::instance()->localPlayerData->equipGameData1.equipInventoryData.list;
	for (uint32_t i = 0; i < itemList.slotIdCap; i++) {
		// Key items are always in itemList.itemsBelowCap
		auto item = itemList.itemsBelowCap[i];
		if (item.handle == 0) continue;
		if (item.itemCount == 0) continue;
		auto itemCategory = item.itemId & 0xf0000000;
		auto itemId = item.itemId & 0xfffffff;

		if (itemCategory == 0x40000000 && itemId > 3780000 && itemId < 0xffffffU) {
			EquipParamGoodsRow* row = GetGoodsParam(item.itemId & 0xfffffffU);
			if (row != NULL) ItemRandomiser->OnGetSyntheticItem(row);
			GameHook->removeFromInventory(itemCategory, itemId, 1);
		}
	}
}

