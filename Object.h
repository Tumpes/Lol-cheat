#pragma once

#include <Windows.h>
#include "Offsets.h"
#include "Vector.h"
#include <string>

class Object {
public:
	//bool IsTurret();
	//bool IsMinion();
	//bool IsAlive();
	//bool IsHero();
	//bool IsMissile();
	//bool IsNexus();

	//bool IsInhibitor();
	//bool IsTroyEnt();
	//bool IsTargetable();

	//short GetIndex() {
	//	return *(short*)((DWORD)this + oObjIndex);
	//}

	//short GetTargetIndex() {
	//	return *(short*)((DWORD)this + oObjTargetID);
	//}

	//short GetSourceIndex() {
	//	return *(short*)((DWORD)this + oObjSourceIndex);
	//}

	//DWORD GetNetworkID() {
	//	return *(DWORD*)((DWORD)this + oObjNetworkID);
	//}

	Vector3 GetPos() {
		return *(Vector3*)((uint64_t)this + Offsets::Position);
	}

	//int GetLevel() {
	//	return *(int*)((DWORD)this + oObjLevel);
	//}

	float GetHealth() {
		return *(float*)((uint64_t)this + Offsets::Health);
	}

	//float GetBaseAttackDamage() {
	//	return *(float*)((DWORD)this + oObjBaseAtk);
	//}

	//float GetBonusAttackDamage() {
	//	return *(float*)((DWORD)this + oObjBonusAtk);
	//}

	//float GetTotalAttackDamage() {
	//	return this->GetBonusAttackDamage() + this->GetBaseAttackDamage();
	//}

	//float GetArmor() {
	//	return *(float*)((DWORD)this + oObjArmor);
	//}

	//float GetMaxHealth() {
	//	return *(float*)((DWORD)this + oObjHealth + 0x10);
	//}

	//float GetAttackRange() {
	//	return *(float*)((DWORD)this + oObjAtkRange);
	//}

	//bool IsVisible() {
	//	return *(bool*)((DWORD)this + oObjVisibility);
	//}

	bool IsAlive() {
		return !(*(int*)((uint64_t)this + Offsets::IsAlive) % 2);
	}

	//float GetBoundingRadius() {
	//	typedef float(__thiscall* OriginalFn)(PVOID);
	//	return CallVirtual<OriginalFn>(this, 36)(this);
	//}

	//bool IsEnemyTo(CObject* Obj) {
	//	if (Obj->GetTeam() == 100 && this->GetTeam() == 200)
	//		return true;

	//	else if (Obj->GetTeam() == 200 && this->GetTeam() == 100)
	//		return true;

	//	return false;
	//}

	char* GetName() { //scuffed :D
		return *reinterpret_cast<char**>((uint64_t)this + Offsets::Name);
	}

	int* GetNameLengthptr() {
		return reinterpret_cast<int*>((uint64_t)this + (Offsets::Name + 0x10));
		// älä käytä: undefined
	}

	//char* GetChampionName() {
	//	return GetStr((DWORD)this + oObjChampionName);
	//}

	//int GetTeam() {
	//	return *(int*)((DWORD)this + oObjTeam);
	//}
};

class SpellInfo {
public:
	std::string GetSpellName() {
		if (this->GetSpellNameLength() < 16) {
			char* s = (char*)(this + 0x28);
			return std::string(s);
		}
		else if (this->GetSpellNameLength() >= 16) {
			char* s = *(char**)(this + 0x28);
			return std::string(s);
		}
	}

	int GetSpellNameLength() {
		return *(int*)(this + 0x38);
	}
};

class Spell {
public:
	SpellInfo* GetSpellInfo() {
		return *reinterpret_cast<SpellInfo**>(this + Offsets::SpellInfo);
	}

	float* GetSpellDamagePtr() {
		return (float*)(this + 0x90);
	}
};

