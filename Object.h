#pragma once

#include <Windows.h>
#include "Offsets.h"
#include "Vector.h"
#include <string>

class Spell;

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

	float GetAttackRange() {
		return *(float*)((uint64_t)this + Offsets::ObjAtkRange);
	}

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
		// �l� k�yt�: undefined
	}

	//char* GetChampionName() {
	//	return GetStr((DWORD)this + oObjChampionName);
	//}

	//int GetTeam() {
	//	return *(int*)((DWORD)this + oObjTeam);
	//}

	float GetBoundingRadius()
	{
		typedef float(__fastcall* fnGetBoundingRadius)(Object* obj);
		fnGetBoundingRadius _fnGetBoundingRadius = (fnGetBoundingRadius)((uint64_t)GetModuleHandleA("League of Legends.exe") + Offsets::fnGetBoundingRadius);
		return _fnGetBoundingRadius(this);
	}

	float GetRealAttackRange() {
		return this->GetAttackRange() + this->GetBoundingRadius();
	}

	Spell* getSpellByIndex(int index) {
		return (Spell*)*reinterpret_cast<uint64_t*>(this + Offsets::ObjSpellBook + Offsets::SpellInstance + (0x8 * index));
	} // J�rjestys: q w e r passive d f
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

class Spell {  //In c++ you have to declare(not necessarily define) a class before it is mentioned in another class.
public:
	SpellInfo* GetSpellInfo() {
		return *reinterpret_cast<SpellInfo**>(this + Offsets::SpellInfo);
	}

	float* GetSpellDamagePtr() {
		return (float*)(this + 0x90);
	}

	float GetSpellCooldown() {
		float readytime = *(float*)(this + Offsets::SpellSlotTime);
		float gametime = *(float*)((uint64_t)GetModuleHandleA("League of Legends.exe") + Offsets::GameTime);

		if (readytime > gametime) {
			return readytime - gametime;
		}

		return 0.0f;
	}
};

