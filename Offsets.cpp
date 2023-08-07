#pragma once
#include "Offsets.h"

uint64_t Offsets::GameTime = (uint64_t)0x2189EB8; //64 
uint64_t Offsets::MinionList = (uint64_t)0x217E1A8; //64 
uint64_t Offsets::HeroList = (uint64_t)0x217B350; //64 
uint64_t Offsets::LocalPlayer = (uint64_t)0x2196050; //64 
uint64_t Offsets::Renderer = (uint64_t)0x21E5200; //64 
uint64_t Offsets::ViewProjMatrices = (uint64_t)0x21DCD60; //64
uint64_t Offsets::RendererWidth = (uint64_t)0xC; //64
uint64_t Offsets::RendererHeight = (uint64_t)0x10; //64 
uint64_t Offsets::oChatClient = (uint64_t)0x2196220; //64 a
uint64_t Offsets::HudInstance = (uint64_t)0x217b240;
uint64_t Offsets::HudInstanceSpellInfo = (uint64_t)0x68;
uint64_t Offsets::PingNet = (uint64_t)0x219e488;     // GetPingNet:   E8 ? ? ? ? 0F 10 4D 97 

uint64_t Offsets::fPrintChat = (uint64_t)0x84B600; //64     E8 ? ? ? ? 4C 8B C3 B2 01
uint64_t Offsets::fCastSpellWrapper = (uint64_t)0x88E996;    //64    E8 ? ? ? ? 48 8B 53 08 48 8B 42 60
uint64_t Offsets::fSendChat = (uint64_t)0x4BAC70;   //    40 55 53 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 27    string: game_chat_known_commands

// Missilemap  = 0x5195E58
//MissileInfo = 0x02E8

uint64_t Offsets::IsAlive = (uint64_t)0x328;
uint64_t Offsets::Position = (uint64_t)0x220; 
uint64_t Offsets::Health = (uint64_t)0x1058; 
uint64_t Offsets::Name = (uint64_t)0x35D8; 
uint64_t Offsets::ObjAtkRange = 0x16B4;
uint64_t Offsets::fnGetBoundingRadius = 0x1f99b0;

//Spells
uint64_t Offsets::SpellInfo = (uint64_t)0x130; //64 a
uint64_t Offsets::ObjSpellBook = (uint64_t)0x29E8; //64   spellbook => instance
uint64_t Offsets::SpellInstance = (uint64_t)0x6D0; //64   spellslot => instance tai spellbookspellslot
