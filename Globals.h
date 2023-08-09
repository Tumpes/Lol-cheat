#pragma once

#include <cstdint>
#include "Offsets.h"
#include "Vector.h"
#include "Object.h"
#include <string>

namespace Globals {

	extern uint64_t BaseAddress;
	extern Object* localPlayer;
	extern Object** MinionList;
	extern int* pMinionListLength;
	extern bool autosmite;


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
}

