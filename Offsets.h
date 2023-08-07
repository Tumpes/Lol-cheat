#pragma once
#include <Windows.h>
#include <cstdint>

class Offsets {
public:
	static uint64_t GameTime;
	static uint64_t MinionList;
	static uint64_t HeroList;
	static uint64_t LocalPlayer;
	static uint64_t Renderer;
	static uint64_t ViewProjMatrices;
	static uint64_t RendererWidth;
	static uint64_t RendererHeight;
	static uint64_t fPrintChat;
	static uint64_t fSendChat;
	static uint64_t fCastSpellWrapper;
	static uint64_t oChatClient;


	static uint64_t Position;
	static uint64_t Health;
	static uint64_t Name;
	static uint64_t IsAlive;
	static uint64_t ObjAtkRange;
	static uint64_t fnGetBoundingRadius;

	static uint64_t SpellInfo; 
	static uint64_t ObjSpellBook;
	static uint64_t SpellInstance;
	static uint64_t HudInstance;
	static uint64_t HudInstanceSpellInfo;
	static uint64_t PingNet;
	static uint64_t SpellSlotTime;
};
