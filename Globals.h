#pragma once

#include <cstdint>
#include "Offsets.h"
#include "Vector.h"
#include <string>

extern class Object;
extern class CMinionManager;
class Spell;

namespace Globals {

	extern uint64_t BaseAddress;
	extern Object* localPlayer;
	extern CMinionManager* MinionList;
	extern CMinionManager* HeroList;
	extern int* pMinionListLength;
	extern bool autosmite;
	extern uint64_t HUDInput;
	extern void** Bufflist;

	extern Vector2 GetWindowDimensions();

	//static void PrintChat_s(const char* message) {
	//	std::string str(message);
	//	message = std::regex_replace(message, std::regex("ä"), "");
	//	PrintChat(BaseAddress + Offsets::oChatClient, message, 0x2);
	//}

};

namespace Funcs {
	void PrintChat(std::string);
	void PrintChat(int);
	void PrintChat(uint64_t);
	void PrintChat(float);


	void SendChat(std::string);

	float GetGameTime();

	//typedef bool(__fastcall* fnCastSpellWrapper)(uint64_t* hudSpellInfo, uint64_t* spellInfo);
	//extern fnCastSpellWrapper CastSpellWrapper;

	char AttackMoveOnPos(Vector2 coordinates);

	char MoveOnPos(Vector2 pos);
}

