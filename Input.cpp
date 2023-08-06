#include "Input.h"

UINT PressKeyScan(WORD scanCode)
{
    INPUT input[1] = { 0 };
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = NULL;
    input[0].ki.wScan = scanCode;
    input[0].ki.dwFlags = KEYEVENTF_SCANCODE;

    UINT ret = SendInput(1, input, sizeof(INPUT));

    return ret;
}

UINT ReleaseKeyScan(WORD scanCode)
{
    INPUT input[1] = { 0 };
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = NULL;
    input[0].ki.wScan = scanCode;
    input[0].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;


    UINT ret = SendInput(1, input, sizeof(INPUT));

    return ret;
}


void SendKey(int keyID)
{
    PressKeyScan(keyID);
    Sleep(10);
    ReleaseKeyScan(keyID);
}

void ClickAt(Vector2 pos, int key) {
    BlockInput(true);
    POINT originalPos = {};
    GetCursorPos(&originalPos);
    SetCursorPos(pos.x, pos.y);
    SendKey(33);
    SetCursorPos(originalPos.x, originalPos.y);
    BlockInput(false);
}