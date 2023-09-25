#pragma once

#include "Offsets.h"
#include "Vector.h"
#include "Utils.h"
#include <regex>
#include <string>
#include "Globals.h"



class CObjectManager {
public:

	Object* getMinionByIndex(int index) {
		index = min(index, this->GetListSize());
		return *(Object**)(*(uint64_t*)((uint64_t)this + 0x8) + (sizeof(uint64_t) * index));
	}

	inline uint64_t GetDragonIndex() {

	uint64_t DragonIndex = 0xDEADBEEF;
	const std::vector<std::string> Dragons{ "SRU_Dragon_Air", "SRU_Dragon_Earth", "SRU_Dragon_Water", "SRU_Dragon_Fire", "SRU_Dragon_Hextech", "SRU_Dragon_Chemtech", "SRU_Baron", "SRU_RiftHerald", "SRU_Dragon_Elder" };
	for (uint64_t i = 0; i < *Globals::pMinionListLength; i++) {


		Object* Minion = this->getMinionByIndex((int)i);
		char* pMinionName = Minion->GetName();
		std::string str(pMinionName);
		Vector3 MinionPos = Minion->GetPos();


		Object* me = Globals::localPlayer;


		float DistanceToDragon = Globals::localPlayer->DistanceToObject(Minion);

		auto it = std::find(Dragons.begin(), Dragons.end(), pMinionName);

		if (it != Dragons.end() && DistanceToDragon < 500.0f) {

			DragonIndex = i;
		}
	}

	return DragonIndex;
}

	int GetListSize()
	{
		return *(int*)((uint64_t)this + 0x10);
	}

};
