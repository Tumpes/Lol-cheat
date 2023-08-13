#pragma once

enum CharacterState : unsigned short
{
	CanAttack = 1,
	CanCast = 2,
	CanMove = 4,
	Immovable = 8,
	Unknownz = 16,
	IsStealth = 32,
	Taunted = 64,
	Feared = 128,       //pastettu
	Fleeing = 256,
	Supressed = 512,
	Asleep = 1024,
	NearSight = 2048,
	Ghosted = 4096,
	HasGhost = 8192,
	Charmed = 16384,
	NoRender = 32768
};