#pragma once

#include <Windows.h>
#include "Vector.h"

UINT PressKeyScan(WORD scanCode);

UINT ReleaseKeyScan(WORD scanCode);

void MouseDown(int button);

void MouseUp(int button);

void SendKey(int keyID);

void Smite(Vector2 pos, int key);
