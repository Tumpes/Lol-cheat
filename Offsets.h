#pragma once
#include <Windows.h>
#include <cstdint>

class Offsets {
public:
	static const uint64_t GameTime = (uint64_t)0x21a1f48; //64 a
	static const uint64_t MinionList = (uint64_t)0x2195d08; //64 
	static const uint64_t HeroList = (uint64_t)0x2192F68; //64 a
	static const uint64_t TurretList = (uint64_t)0x219c340; //64 a
	static const uint64_t LocalPlayer = (uint64_t)0x21ad080; //64 a
	static const uint64_t BuffManager = (uint64_t)0x27B0;        //    [[[[<league of Legends.exe> +0x21B7BC0]+ 0x27C8] + 0x00] + 0x10] + 0x8
	static const uint64_t Renderer = (uint64_t)0x21fea90; //64 
	static const uint64_t ViewProjMatrices = (uint64_t)0x21f6110; //64
	static const uint64_t RendererWidth = (uint64_t)0xC; //64
	static const uint64_t RendererHeight = (uint64_t)0x10; //64 
	static const uint64_t oChatClient = (uint64_t)0x21ade68; //64 a
	static const uint64_t HudInstance = (uint64_t)0x2192e18; // a
	static const uint64_t HudInstanceSpellInfo = (uint64_t)0x68;
	static const uint64_t PingNet = (uint64_t)0x2192e00;     // GetPingNet:   E8 ? ? ? ? 0F 10 4D 97 

	static const uint64_t fPrintChat = (uint64_t)0x860740; //64     E8 ? ? ? ? 4C 8B C3 B2 01
	//uint64_t fCastSpellWrapper = (uint64_t)0x88E996;    //64    E8 ? ? ? ? 48 8B 53 08 48 8B 42 60
	static const uint64_t fSendChat = (uint64_t)0x4bed90;   //    E9 ? ? ? ? CC CC CC CC CC 48 8B 0D ? ? ? ?     string: game_chat_known_commands
	static const uint64_t fAttackMove = (uint64_t)0x8A4910; // 48 83 EC 48 8B 42 48 45 33 C9 C6 44 24 ? ? 41 B0 01
	static const uint64_t fMove = (uint64_t)0x8A4AC0; // 48 89 5C 24 ? 57 48 83 EC 50 48 8B D9 0F 29 74 24 ? 48 8B 0D ? ? ? ? 
	static const uint64_t DerefPointer = (uint64_t)0x1033100; // E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 80 3B 00 
	// Missilemap  = 0x5195E58
	//MissileInfo = 0x02E8

	static const uint64_t IsAlive = (uint64_t)0x328;
	static const uint64_t Position = (uint64_t)0x220;
	static const uint64_t Health = (uint64_t)0x1058;
	static const uint64_t MaxHealth = (uint64_t)0x1070;
	static const uint64_t Name = (uint64_t)0x35D8;
	static const uint64_t ObjAtkRange = (uint64_t)0x16B4;
	static const uint64_t ObjVisible = (uint64_t)0x310;
	static const uint64_t ObjTeam = (uint64_t)0x3C;
	static const uint64_t ObjTargetable = (uint64_t)0xEB0;
	static const uint64_t oActionState = (uint64_t)0x13C0;
	//oGetBoundingRadius 0x1F99B0
	static const uint64_t oGetAttackDelay = (uint64_t)0x3b5b80; // F3 0F 10 89 ? ? ? ? E9 ? ? ? ? 
	static const uint64_t oGetAttackWindup = (uint64_t)0x3b5a80; // E8 ? ? ? ? 48 8B CE F3 0F 11 83 ? ? ? ?
	static const uint64_t fnGetBoundingRadius = (uint64_t)0x1f7b90; // E8 ? ? ? ? 0F 28 F8 48 8B D6
	//oObjAttackRange 0x16B4


	//Spells
	static const uint64_t SpellInfo = (uint64_t)0x130; //64 a
	static const uint64_t ObjSpellBook = (uint64_t)0x29E8; //64   spellbook => instance
	static const uint64_t SpellInstance = (uint64_t)0x6D0; //64   spellslot => instance tai spellbookspellslot
	static const uint64_t SpellSlotTime = (uint64_t)0x30; // spell + 30

	static const uint64_t BuffManagerStart = (uint64_t)0x18;
	static const uint64_t BuffManagerEnd = (uint64_t)0x18;
};