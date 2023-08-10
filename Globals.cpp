#include "Globals.h"

namespace Globals {

	uint64_t BaseAddress;
	Object* localPlayer;
	Object** MinionList;
	int* pMinionListLength;
	bool autosmite;
	uint64_t HUDInput;

	Vector2 GetWindowDimensions() {
		uint64_t RendererAddress = *reinterpret_cast<uint64_t*>(Globals::BaseAddress + Offsets::Renderer);

		int width = 0;
		int height = 0;

		char buff[128];
		memcpy(buff, (void*)RendererAddress, 128);
		memcpy(&width, &buff[Offsets::RendererWidth], sizeof(int));
		memcpy(&height, &buff[Offsets::RendererHeight], sizeof(int));

		Vector2 ret = { width, height };
		return ret;
	}

	//static void PrintChat_s(const char* message) {
	//	std::string str(message);
	//	message = std::regex_replace(message, std::regex("ä"), "");
	//	PrintChat(BaseAddress + Offsets::oChatClient, message, 0x2);
	//}

};

namespace Funcs {
	void PrintChat(std::string message) {
		typedef void(__fastcall* fnPrintChat)(uint64_t, const char*, int);
		fnPrintChat ingame_PrintChat = (fnPrintChat)(Globals::BaseAddress + Offsets::fPrintChat);

		ingame_PrintChat(Globals::BaseAddress + Offsets::oChatClient, message.c_str(), 0x2);
	} 

	void PrintChat(int message) {
		std::string strmessage = std::to_string(message);
		PrintChat(strmessage);
	}

	void PrintChat(uint64_t message) {
		std::string strmessage = std::to_string(message);
		PrintChat(strmessage);
	}

	void PrintChat(float message) {
		std::string strmessage = std::to_string(message);
		PrintChat(strmessage);
	}

	void SendChat(std::string message) {
		typedef char(__fastcall* fnSendChat)(uint64_t, const char*, int);
		fnSendChat ingame_SendChat = (fnSendChat)(Globals::BaseAddress + Offsets::fSendChat);

		ingame_SendChat(*(uint64_t*)(Globals::BaseAddress + Offsets::PingNet), message.c_str(), 0x1);  //Pingnet, message, ChatType - 1 = all,  2 = team,  3 = party
	}
	//fnCastSpellWrapper CastSpellWrapper = (fnCastSpellWrapper)(Globals::BaseAddress + Offsets::fCastSpellWrapper);

	float GetGameTime() {
		return *(float*)(Globals::BaseAddress + Offsets::GameTime);
	}

	char AttackMoveOnPos(Vector2 coordinates)
	{
		typedef char(__fastcall* fnAttackMove)(uint64_t HUDInput, unsigned int* params);
		fnAttackMove ingame_AttackMove = (fnAttackMove)(Globals::BaseAddress + 0x88B0F0);

		unsigned int params[20];

		params[17] = coordinates.x;
		params[18] = coordinates.y;
		params[19] = 0;

		ingame_AttackMove(Globals::HUDInput, (unsigned int*)&params); // hundinput offsetteihin ja testi

		return 1;
	}
}