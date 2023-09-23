#include "Globals.h"

namespace Globals {

	uint64_t BaseAddress;
	Object* localPlayer;
	CObjectManager* MinionList;
	CObjectManager* HeroList;
	void** Bufflist;
	int* pMinionListLength;
	bool autosmite;
	uint64_t HUDInput;

	Vector2 GetWindowDimensions() {
		uint64_t RendererAddress = *reinterpret_cast<uint64_t*>(Globals::BaseAddress + oRenderer);

		int width = 0;
		int height = 0;

		char buff[128];
		memcpy(buff, (void*)RendererAddress, 128);
		memcpy(&width, &buff[oRendererWidth], sizeof(int));
		memcpy(&height, &buff[oRendererHeight], sizeof(int));

		Vector2 ret = { width, height };
		return ret;
	}
};

namespace Funcs {
	void PrintChat(std::string message) {
		typedef void(__fastcall* fnPrintChat)(uint64_t, const char*, int);
		fnPrintChat ingame_PrintChat = (fnPrintChat)(Globals::BaseAddress + oPrintChat);

		ingame_PrintChat(Globals::BaseAddress + oChatClient, message.c_str(), 0x2);
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
		fnSendChat ingame_SendChat = (fnSendChat)(Globals::BaseAddress + oSendChat);

		ingame_SendChat(*(uint64_t*)(Globals::BaseAddress + oPingNet), message.c_str(), 0x1);  //Pingnet, message, ChatType - 1 = all,  2 = team,  3 = party
	}
	//fnCastSpellWrapper CastSpellWrapper = (fnCastSpellWrapper)(Globals::BaseAddress + fCastSpellWrapper);

	float GetGameTime() {
		return *(float*)(Globals::BaseAddress + oGameTime);
	}

	char AttackMoveOnPos(Vector2 pos)
	{
		typedef char(__fastcall* fnAttackMove)(uint64_t HUDInput, unsigned int* params);
		fnAttackMove ingame_AttackMove = (fnAttackMove)(Globals::BaseAddress + oAttackMove);

		unsigned int* params = new unsigned int[20];
		params[17] = (int)pos.x;
		params[18] = (int)pos.y;
		params[19] = 0;

		uint64_t HUDInput = *(uint64_t*)(*(uint64_t*)(Globals::BaseAddress + oHudInstance) + 0x48);

		ingame_AttackMove(HUDInput, params); // hudinput offsetteihin ja testi

		unsigned int* params2 = new unsigned int[20];
		params2[17] = (int)pos.x;
		params2[18] = (int)pos.y;
		params2[19] = 1;

		ingame_AttackMove(HUDInput, params2);

		return 1;
	}

	char MoveOnPos(Vector2 pos)
	{
		typedef char(__fastcall* fnAttackMove)(uint64_t HUDInput, unsigned int* params);
		fnAttackMove ingame_AttackMove = (fnAttackMove)(Globals::BaseAddress + oTryRightClick);

		unsigned int* params = new unsigned int[20];
		params[17] = (int)pos.x;
		params[18] = (int)pos.y;
		params[19] = 0;

		uint64_t HUDInput = *(uint64_t*)(*(uint64_t*)(Globals::BaseAddress + oHudInstance) + 0x48);

		ingame_AttackMove(HUDInput, params); // hudinput offsetteihin ja testi

		unsigned int* params2 = new unsigned int[20];
		params2[17] = (int)pos.x;
		params2[18] = (int)pos.y;
		params2[19] = 1;
		
		ingame_AttackMove(HUDInput, params2);

		return 1;
	}
}