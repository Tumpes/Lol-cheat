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

void MouseDown(int button) {
    INPUT input;
    input.type = INPUT_MOUSE;

    if (button == 0) {  // Left button down
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    }
    else if (button == 1) {  // Right button down
        input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    }

    SendInput(1, &input, sizeof(INPUT));
}

void MouseUp(int button) {
    INPUT input;
    input.type = INPUT_MOUSE;

    if (button == 0) {  // Left button up
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    }
    else if (button == 1) {  // Right button up
        input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    }

    SendInput(1, &input, sizeof(INPUT));
}

void SendKey(int keyID)
{
    PressKeyScan(keyID);
    Sleep(10);
    ReleaseKeyScan(keyID);
}

void Smite(Vector2 pos, int key) {
    BlockInput(true);
    POINT originalPos = {};
    GetCursorPos(&originalPos);
    SetCursorPos(pos.x, pos.y);
    SendKey(key);
    SetCursorPos(originalPos.x, originalPos.y);
    BlockInput(false);
}