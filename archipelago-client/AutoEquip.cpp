#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>

#include "AutoEquip.h"
#include "GameHook.h"
#include "ItemInfo.h"

extern CCore* Core;
extern CAutoEquip* AutoEquip;
extern CGameHook* GameHook;
extern CItemInfo* ItemInfo;

EquipSlot dRingSlotSelect = EquipSlot::ring1;

VOID CAutoEquip::AutoEquipItem(SItemBuffer* pItemBuffer) {

	if (!pItemBuffer) {
		Core->Panic("Null buffer!", "...\\Source\\AutoEquip\\AutoEquip.cpp", FE_NullPtr, 1);
		int3
	};

	if (pItemBuffer->length > 6) {
		Core->Panic("Too many items!", "...\\Source\\AutoEquip\\AutoEquip.cpp", FE_AmountTooHigh, 1);
		int3
	};

	spdlog::trace("Auto-equipping {} items", pItemBuffer->length);
	for (int i = 0; i < pItemBuffer->length; i++) {

		SItemBufferEntry* dItem = &pItemBuffer->items[i];
		auto equipSlot = SortItem(dItem->id);
		if (!equipSlot.has_value()) {
			spdlog::trace("Item {} is not equipment", dItem->id);
			return;
		}

		spdlog::trace("Item {}'s equip slot: {}", dItem->id, fmt::underlying(equipSlot.value()));
		auto inventorySlot = GetInventorySlotID(dItem->id);
		spdlog::trace("Item {}'s inventory slot: {}", dItem->id, inventorySlot);
		if (inventorySlot < 0) {
			std::ostringstream stream;
			stream << "Unable to find item: " << std::hex << dItem->id;
			Core->Panic(stream.str().c_str(), "...\\Source\\AutoEquip\\AutoEquip.cpp", HE_InvalidInventoryEquipID, 0);
			return;
		};

		LockUnlockEquipSlots(1);
		spdlog::trace("Unlocked equip slots");
		GameHook->equipItem(equipSlot.value(), inventorySlot);
		spdlog::trace("Equipped item");
	}

	return;
};

std::optional<EquipSlot> CAutoEquip::SortItem(uint32_t dItemID) {

	auto detailedItemType = ItemInfo->GetDetailedItemType(dItemID);
	switch (detailedItemType) {
		case DetailedItemType::meleeWeapon:
		case DetailedItemType::catalyst:
		case DetailedItemType::bow: {
			return EquipSlot::rightHand1;
		};
		case DetailedItemType::shield: {
			return EquipSlot::leftHand1;
		};
		case DetailedItemType::headArmor: {
			return EquipSlot::head;
		};
		case DetailedItemType::bodyArmor: {
			return EquipSlot::body;
		};
		case DetailedItemType::armsArmor: {
			return EquipSlot::arms;
		};
		case DetailedItemType::legsArmor: {
			return EquipSlot::legs;
		};
		case DetailedItemType::ring: {
			if (dRingSlotSelect > EquipSlot::ring4) dRingSlotSelect = EquipSlot::ring1;
			EquipSlot result = dRingSlotSelect;
			dRingSlotSelect = static_cast<EquipSlot>(static_cast<uint32_t>(dRingSlotSelect) + 1);
			return result;
		};
		default: {
			return std::nullopt;
		};
	};
};

uint32_t CAutoEquip::GetInventorySlotID(uint32_t dItemID) {

	uint32_t dInventoryID = 0;
	UINT_PTR qInventoryScanPtr = 0;

	auto qInventoryPtr = (UINT_PTR)GameDataMan::instance()->localPlayerData;
	qInventoryPtr = *(UINT_PTR*)(qInventoryPtr + 0x470);
	qInventoryPtr = *(UINT_PTR*)(qInventoryPtr + 0x10);
	qInventoryPtr += 0x1B8;

	while (dInventoryID < *(uint32_t*)(qInventoryPtr + 0x04)) {
	
		qInventoryScanPtr = (dInventoryID << 0x04);
		qInventoryScanPtr += *(UINT_PTR*)(qInventoryPtr + 0x38);

		if (*(uint32_t*)(qInventoryScanPtr + 0x04) == dItemID) {
			return (dInventoryID + *(uint32_t*)(qInventoryPtr + 0x14));
		};
	
		dInventoryID++;
	};

	return -1;
};

VOID CAutoEquip::LockUnlockEquipSlots(int iIsUnlock) {

	auto actionModule = WorldChrMan::instance()->mainCharacter->container->actionModule;
	if (iIsUnlock) actionModule->chrEquipAnimFlags |= 1;
	else actionModule->chrEquipAnimFlags &= 0xFFFFFFFE;

};