#pragma once

#include "Vector.h"

class N0000004E
{
public:
	Vector3 position; //0x0000
	Vector3 LookAt; //0x000C
	Vector3 up; //0x0018
	char pad_0024[36]; //0x0024
	Vector3 Cameravelocity; //0x0048
	char pad_0054[76]; //0x0054
}; //Size: 0x00A0

class N00000077
{
public:
	char pad_0000[4]; //0x0000
	Vector3 head; //0x0004
	char pad_0010[36]; //0x0010
	Vector3 feet; //0x0034
	char pad_0040[2128]; //0x0040
}; //Size: 0x0890