#pragma once
#include <Windows.h>
#include <cstdint>

class Offsets {
public:
	static const uint64_t GameTime = (uint64_t)0x21ABFFC; //64 a
	static const uint64_t MinionList = (uint64_t)0x219FE58; //64 
	static const uint64_t HeroList = (uint64_t)0x219D000; //64 a
	static const uint64_t TurretList = (uint64_t)0x21A6530; //64 a
	static const uint64_t LocalPlayer = (uint64_t)0x21B7BC0; //64 a
	static const uint64_t BuffManager = (uint64_t)0x27B0;        //    [[[[<league of Legends.exe> +0x21B7BC0]+ 0x27C8] + 0x00] + 0x10] + 0x8
	static const uint64_t Renderer = (uint64_t)0x22078F0; //64 
	static const uint64_t ViewProjMatrices = (uint64_t)0x21FEE30; //64
	static const uint64_t RendererWidth = (uint64_t)0xC; //64
	static const uint64_t RendererHeight = (uint64_t)0x10; //64 
	static const uint64_t oChatClient = (uint64_t)0x21B7D78; //64 a
	static const uint64_t HudInstance = (uint64_t)0x219CEF0; // a
	static const uint64_t HudInstanceSpellInfo = (uint64_t)0x68;
	static const uint64_t PingNet = (uint64_t)0x21C0858;     // GetPingNet:   E8 ? ? ? ? 0F 10 4D 97 

	static const uint64_t fPrintChat = (uint64_t)0x85A830; //64     E8 ? ? ? ? 4C 8B C3 B2 01
	//uint64_t fCastSpellWrapper = (uint64_t)0x88E996;    //64    E8 ? ? ? ? 48 8B 53 08 48 8B 42 60
	static const uint64_t fSendChat = (uint64_t)0x4C4840;   //    40 55 53 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 27    string: game_chat_known_commands
	static const uint64_t fAttackMove = (uint64_t)0x89B220; // 48 83 EC 48 8B 42 48 45 33 C9 C6 44 24 ? ? 41 B0 01
	static const uint64_t fMove = (uint64_t)0x89B3D0; // 48 89 5C 24 ? 57 48 83 EC 50 48 8B D9 0F 29 74 24 ? 48 8B 0D ? ? ? ? 

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
	static const uint64_t oGetAttackDelay = (uint64_t)0x3B6120;
	static const uint64_t oGetAttackWindup = (uint64_t)0x3B6020;
	static const uint64_t fnGetBoundingRadius = (uint64_t)0x1FAC30;
	//oObjAttackRange 0x16B4


	//Spells
	static const uint64_t SpellInfo = (uint64_t)0x130; //64 a
	static const uint64_t ObjSpellBook = (uint64_t)0x29E8; //64   spellbook => instance
	static const uint64_t SpellInstance = (uint64_t)0x6D0; //64   spellslot => instance tai spellbookspellslot
	static const uint64_t SpellSlotTime = (uint64_t)0x30; // spell + 30

	static const uint64_t BuffManagerStart = (uint64_t)0x18;
	static const uint64_t BuffManagerEnd = (uint64_t)0x18;
};