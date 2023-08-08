#pragma once

//#include "GetDragon.h"
#include "Kiero/kiero.h"
#include <dxgi.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include <d3d11.h>
#include "Kiero/minhook/include/MinHook.h"
#include <chrono>
#include <Windows.h>
#include "Renderer.h"
#include "Vector.h"
#include "Input.h"
#include "Utils.h"
#include "MinionManager.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern Present oPresent;
extern HWND window;
extern WNDPROC oWndProc;
extern ID3D11Device* pDevice;
extern ID3D11DeviceContext* pContext;
extern ID3D11RenderTargetView* mainRenderTargetView;

extern void InitImGui();

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

extern bool init;
extern bool menuOpen;
extern bool keyPressed;
extern bool Circle;
extern bool CoolDownToggle;
extern float size;
extern float oldgametime;

extern std::chrono::steady_clock::time_point lastKeyPressTime;

extern void DrawCircle(ImDrawList* canvas, const Vector3& worldPos, float radius, bool filled, int numPoints, ImColor color, float thickness);


extern HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

