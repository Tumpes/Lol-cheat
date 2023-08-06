#pragma once

#include <Windows.h>
#include "Vector.h"

UINT PressKeyScan(WORD scanCode);

UINT ReleaseKeyScan(WORD scanCode);

void SendKey(int keyID);

void ClickAt(Vector2 pos, int key);