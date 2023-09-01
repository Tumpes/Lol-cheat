#pragma once

#include <Windows.h>
#include "Offsets.h"
#include "Vector.h"
#include <string>
#include "Globals.h"
#include "Struct.h"

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

	float GetMaxHealth() {
		return *(float*)((uint64_t)this + Offsets::MaxHealth);
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

	int GetTeam() {
		return *(int*)((uint64_t)this + Offsets::ObjTeam);
	}

	bool IsEnemy()
	{
		return this->GetTeam() != Globals::localPlayer->GetTeam();
	}

	bool IsTargetable()
	{
		return *(bool*)((uint64_t)this + Offsets::ObjTargetable);
	}

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
	} // Järjestys: q w e r passive d f

	float DistanceToObject(Object* obj) {
		return sqrt(pow((this->GetPos().x - obj->GetPos().x), 2) + pow((this->GetPos().y - obj->GetPos().y), 2) + pow((this->GetPos().z - obj->GetPos().z), 2));
	}

	bool IsVisible() {
		return *(bool*)((uint64_t)this + Offsets::ObjVisible);
	}

	bool IsValidTarget()
	{
		return this->IsVisible() && this->IsAlive() && this->IsEnemy() && this->IsTargetable();
	}

	float GetAttackDelay() {
		typedef float(__fastcall* fnGetAttackDelay)(Object*);
		fnGetAttackDelay ingame_GetAttackDelay = (fnGetAttackDelay)(Globals::BaseAddress + Offsets::oGetAttackDelay);

		return ingame_GetAttackDelay(this);
	}

	float GetAttackWindUp() {
		typedef float(__fastcall* fnGetWindUp)(Object*, int flags);
		fnGetWindUp ingame_GetAttackDelay = (fnGetWindUp)(Globals::BaseAddress + Offsets::oGetAttackWindup);

		return ingame_GetAttackDelay(this,0x40);
	}

	//uint64_t GetAttackDelay() {
	//	typedef char(__fastcall* fnGetAttackDelay)(Object*);
	//	fnGetAttackDelay ingame_GetAttackDelay = (fnGetAttackDelay)(Globals::BaseAddress + Offsets::oGetAttackDelay);

	//	return ingame_GetAttackDelay(this);
	//}

	unsigned short GetActionState()
	{
		return *(unsigned short*)((uint64_t)this + Offsets::oActionState);
	}

	bool CanAttack()
	{
		return this->GetActionState() & CharacterState::CanAttack;
	}
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