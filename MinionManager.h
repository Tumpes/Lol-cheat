#pragma once

#include "Offsets.h"
#include "Vector.h"
#include "Utils.h"
#include <regex>
#include <string>
#include "Globals.h"

class CMinionManager {
public:

	Object* getMinionByIndex(int index) {
		return reinterpret_cast<Object*>(Globals::MinionList[index]);
	}

	inline uint64_t GetDragonIndex() {

	uint64_t DragonIndex = 0xDEADBEEFF00D;
	const std::vector<std::string> Dragons{ "SRU_Dragon_Air", "SRU_Dragon_Earth", "SRU_Dragon_Water", "SRU_Dragon_Fire", "SRU_Dragon_Hextech", "SRU_Dragon_Chemtech", "SRU_Baron", "SRU_RiftHerald", "SRU_Dragon_Elder" };
	for (uint64_t i = 0; i < *Globals::pMinionListLength; i++) {


		Object* Minion = this->getMinionByIndex((int)i);
		if (Minion == nullptr) break;
		char* pMinionName = Minion->GetName();
		if (Minion == nullptr) break;
		std::string str(pMinionName);
		if (Minion == nullptr) break;
		Vector3 MinionPos = Minion->GetPos();


		Object* me = Globals::localPlayer;


		float DistanceToDragon = (float)sqrt(pow((MinionPos.x - me->GetPos().x), 2) + pow((MinionPos.z - me->GetPos().z), 2));

		auto it = std::find(Dragons.begin(), Dragons.end(), pMinionName);

		if (it != Dragons.end() && DistanceToDragon < 500.0f) {

			DragonIndex = i;
		}
	}

	return DragonIndex;
}

};

class Spells {
public:
	static Spell* getSpellByIndex(int index) {
		return (Spell*)*reinterpret_cast<uint64_t*>(Globals::localPlayer + Offsets::ObjSpellBook + Offsets::SpellInstance + (0x8 * index));
	}
};