#pragma once
#include "Offsets.h"

uint64_t Offsets::GameTime = (uint64_t)0x21ABFFC; //64 a
uint64_t Offsets::MinionList = (uint64_t)0x219FE58; //64 
uint64_t Offsets::HeroList = (uint64_t)0x219D000; //64 a
uint64_t Offsets::LocalPlayer = (uint64_t)0x21B7BC0; //64 a
uint64_t Offsets::Renderer = (uint64_t)0x22078F0; //64 
uint64_t Offsets::ViewProjMatrices = (uint64_t)0x21FEE30; //64
uint64_t Offsets::RendererWidth = (uint64_t)0xC; //64
uint64_t Offsets::RendererHeight = (uint64_t)0x10; //64 
uint64_t Offsets::oChatClient = (uint64_t)0x21B7D78; //64 a
uint64_t Offsets::HudInstance = (uint64_t)0x219CEF0; // a
uint64_t Offsets::HudInstanceSpellInfo = (uint64_t)0x68;
uint64_t Offsets::PingNet = (uint64_t)0x21C0858;     // GetPingNet:   E8 ? ? ? ? 0F 10 4D 97 

uint64_t Offsets::fPrintChat = (uint64_t)0x85A830; //64     E8 ? ? ? ? 4C 8B C3 B2 01
//uint64_t Offsets::fCastSpellWrapper = (uint64_t)0x88E996;    //64    E8 ? ? ? ? 48 8B 53 08 48 8B 42 60
uint64_t Offsets::fSendChat = (uint64_t)0x4C4840;   //    40 55 53 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 27    string: game_chat_known_commands
uint64_t Offsets::fAttackMove = (uint64_t)0x89B220; // 48 83 EC 48 8B 42 48 45 33 C9 C6 44 24 ? ? 41 B0 01
uint64_t Offsets::fMove = (uint64_t)0x89B3D0; // 48 89 5C 24 ? 57 48 83 EC 50 48 8B D9 0F 29 74 24 ? 48 8B 0D ? ? ? ? 

// Missilemap  = 0x5195E58
//MissileInfo = 0x02E8

uint64_t Offsets::IsAlive = (uint64_t)0x328;
uint64_t Offsets::Position = (uint64_t)0x220; 
uint64_t Offsets::Health = (uint64_t)0x1058; 
uint64_t Offsets::MaxHealth = (uint64_t)0x1070;
uint64_t Offsets::Name = (uint64_t)0x35D8; 
uint64_t Offsets::ObjAtkRange = (uint64_t)0x16B4;
uint64_t Offsets::ObjVisible = (uint64_t)0x310;
uint64_t Offsets::ObjTeam = (uint64_t)0x3C;
uint64_t Offsets::ObjTargetable = (uint64_t)0xEB0;
uint64_t Offsets::oActionState = (uint64_t)0x13C0;
//oGetBoundingRadius 0x1F99B0
uint64_t Offsets::oGetAttackDelay = (uint64_t)0x3B6120;
uint64_t Offsets::oGetAttackWindup = (uint64_t)0x3B6020;
uint64_t Offsets::fnGetBoundingRadius = (uint64_t)0x1FAC30;
//oObjAttackRange 0x16B4


//Spells
uint64_t Offsets::SpellInfo = (uint64_t)0x130; //64 a
uint64_t Offsets::ObjSpellBook = (uint64_t)0x29E8; //64   spellbook => instance
uint64_t Offsets::SpellInstance = (uint64_t)0x6D0; //64   spellslot => instance tai spellbookspellslot
uint64_t Offsets::SpellSlotTime = (uint64_t)0x30; // spell + 30