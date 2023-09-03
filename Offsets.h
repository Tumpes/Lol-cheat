#pragma once
#include <Windows.h>


//class Offsets {
//public:
//	static const uint64_t GameTime = (uint64_t)0x21ABFFC; //64 a
//	static const uint64_t MinionList = (uint64_t)0x219FE58; //64 
//	static const uint64_t HeroList = (uint64_t)0x219D000; //64 a
//	static const uint64_t TurretList = (uint64_t)0x21A6530; //64 a
//	static const uint64_t LocalPlayer = (uint64_t)0x21B7BC0; //64 a
//	static const uint64_t BuffManager = (uint64_t)0x27B0;        //    [[[[<league of Legends.exe> +0x21B7BC0]+ 0x27C8] + 0x00] + 0x10] + 0x8
//	static const uint64_t Renderer = (uint64_t)0x22078F0; //64 
//	static const uint64_t ViewProjMatrices = (uint64_t)0x21FEE30; //64
//	static const uint64_t RendererWidth = (uint64_t)0xC; //64
//	static const uint64_t RendererHeight = (uint64_t)0x10; //64 
//	static const uint64_t oChatClient = (uint64_t)0x21B7D78; //64 a
//	static const uint64_t HudInstance = (uint64_t)0x219CEF0; // a
//	static const uint64_t HudInstanceSpellInfo = (uint64_t)0x68;
//	static const uint64_t PingNet = (uint64_t)0x21C0858;     // GetPingNet:   E8 ? ? ? ? 0F 10 4D 97 
//
//	static const uint64_t fPrintChat = (uint64_t)0x85A830; //64     E8 ? ? ? ? 4C 8B C3 B2 01
//	//uint64_t fCastSpellWrapper = (uint64_t)0x88E996;    //64    E8 ? ? ? ? 48 8B 53 08 48 8B 42 60
//	static const uint64_t fSendChat = (uint64_t)0x4C4840;   //    40 55 53 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 27    string: game_chat_known_commands
//	static const uint64_t fAttackMove = (uint64_t)0x89B220; // 48 83 EC 48 8B 42 48 45 33 C9 C6 44 24 ? ? 41 B0 01
//	static const uint64_t fMove = (uint64_t)0x89B3D0; // 48 89 5C 24 ? 57 48 83 EC 50 48 8B D9 0F 29 74 24 ? 48 8B 0D ? ? ? ? 
//
//	// Missilemap  = 0x5195E58
//	//MissileInfo = 0x02E8
//
//	static const uint64_t IsAlive = (uint64_t)0x328;
//	static const uint64_t Position = (uint64_t)0x220;
//	static const uint64_t Health = (uint64_t)0x1058;
//	static const uint64_t MaxHealth = (uint64_t)0x1070;
//	static const uint64_t Name = (uint64_t)0x35D8;
//	static const uint64_t ObjAtkRange = (uint64_t)0x16B4;
//	static const uint64_t ObjVisible = (uint64_t)0x310;
//	static const uint64_t ObjTeam = (uint64_t)0x3C;
//	static const uint64_t ObjTargetable = (uint64_t)0xEB0;
//	static const uint64_t oActionState = (uint64_t)0x13C0;
//	//oGetBoundingRadius 0x1F99B0
//	static const uint64_t oGetAttackDelay = (uint64_t)0x3B6120;
//	static const uint64_t oGetAttackWindup = (uint64_t)0x3B6020;
//	static const uint64_t fnGetBoundingRadius = (uint64_t)0x1FAC30;
//	//oObjAttackRange 0x16B4
//
//
//	//Spells
//	static const uint64_t SpellInfo = (uint64_t)0x130; //64 a
//	static const uint64_t ObjSpellBook = (uint64_t)0x29E8; //64   spellbook => instance
//	static const uint64_t SpellInstance = (uint64_t)0x6D0; //64   spellslot => instance tai spellbookspellslot
//	static const uint64_t SpellSlotTime = (uint64_t)0x30; // spell + 30
//
//	static const uint64_t BuffManagerStart = (uint64_t)0x18;
//	static const uint64_t BuffManagerEnd = (uint64_t)0x18;
//};

/*13.17.529.525*/
#define oRenderer 0x21FEA90	//48 8B 0D ? ? ? ? 4C 8D 44 24 ? 48 8B D0 
#define oViewProjMatrices 0x21F6110	//4C 8D 05 ? ? ? ? 48 8D 54 24 ? 48 8B 48 08
#define oChatClient 0x21ADE68	//48 8B 0D ? ? ? ? 44 0F B6 C3 BA ? ? ? ? 48 83 C4 20 5B E9 ? ? ? ? 48 83 C4 20 5B C3 CC CC CC CC CC CC CC CC CC 40 53 48 83 EC 20 0F B6 D9 48 8B 0D ? ? ? ?
#define oLocalPlayer 0x21AD080	//48 8B 05 ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 
#define oGameTime 0x21A1F48	//F3 0F 5C 35 ? ? ? ? 0F 28 F8 
#define oTurretList 0x219C340	//48 8B 0D ? ? ? ? 48 89 74 24 ? E8 ? ? ? ? 48 8B F0 48 85 C0 74 6E 
#define oMinionList 0x2195D08	//4C 8B 05 ? ? ? ? 49 8B 78 08 41 8B 40 10 48 8D 0C C7 48 3B F9 73 47 48 39 1F 74 0B 48 83 C7 08 48 3B F9 72 F2 EB 37 48 83 C1 F8 48 3B F9 73 1E 48 2B CF 48 89 74 24 ? 48 FF C9 48 8D 77 08 48 C1 E9 03 48 FF C1 F3 48 A5 48 8B 74 24 ? 41 FF 48 10 48 8B D3 49 8B 00 49 8B C8 FF 50 10 48 8B 83 ? ? ? ? 
#define oHeroList 0x2192F28	//48 8B 1D ? ? ? ? E8 ? ? ? ? 8B D0 48 8B CB E8 ? ? ? ? 48 8B 17 48 8B CF 48 8B D8 FF 92 ? ? ? ? F3 0F 10 97 ? ? ? ? 48 8B CB F3 0F 10 8F ? ? ? ? 0F 28 D8 48 89 7C 24 ? E8 ? ? ? ? 0F 28 74 24 ? 
#define oHudInstance 0x2192E18	//48 8B 0D ?? ?? ?? ?? 48 89 5C 24 ?? 48 8B 59 60
#define oPingNet 0x2192E00	//48 8B 1D ? ? ? ? 44 0F B6 E8 
#define oDerefPointer 0x1033110	//E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 80 3B 00
#define oTryRightClick 0x8A4AD0	//48 89 5C 24 ? 57 48 83 EC 50 48 8B D9 0F 29 74 24 ? 48 8B 0D ? ? ? ?
#define oAttackMove 0x8A4920	//48 83 EC 48 8B 42 48 45 33 C9 C6 44 24 ? ? 41 B0 01
#define oPrintChat 0x860750	//E8 ? ? ? ? 4C 8B C3 B2 01
#define oSendChat 0x852DA6	//E9 ? ? ? ? CC CC CC CC CC 48 8B 0D ? ? ? ?
#define oGetAttackWindup 0x3B5A90	//E8 ? ? ? ? 48 8B CE F3 0F 11 83 ? ? ? ? 
#define oGetAttackDelay 0x3B5B90	//48 8B 0D ? ? ? ? 48 89 5C 24 ? 48 8B 59 60 
#define oGetBoundingRadius 0x1F7B90	//E8 ? ? ? ? 0F 28 F8 48 8B D6


#define oSpellInfo 0x130
#define oObjSpellBook 0x29E8
#define oSpellInstance 0x6D0
#define oSpellSlotTime 0x30

#define oRendererWidth 0xC
#define oRendererHeight 0x10

//#define BuffManagerStart = 0x18
//#define BuffManagerEnd = 0x18

#define oObjIsAlive 0x328
#define oObjPosition 0x220
#define oObjHealth 0x1058
#define oObjMaxHealth 0x1070
#define oObjName 0x35D8
#define oObjAtkRange 0x16B4
#define oObjVisible 0x310
#define oObjTeam 0x3C
#define oObjTargetable 0xEB0
#define oObjActionState 0x13C0