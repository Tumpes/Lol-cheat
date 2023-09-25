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
#include "Globals.h"
#include "Config.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef HRESULT(__stdcall* ResizeBuffers) (IDXGISwapChain* pThis, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern Present oPresent;
extern ResizeBuffers oResizeBuffers;
extern HWND window;
extern WNDPROC oWndProc;
extern ID3D11Device* pDevice;
extern ID3D11DeviceContext* pContext;
extern ID3D11RenderTargetView* mainRenderTargetView;
extern IDXGISwapChain* gSwapchain;

extern void InitImGui();

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

extern bool init;
extern bool menuOpen;
extern bool keyPressed;
extern float size;
extern float oldgametime;
extern bool Waitingmouseclick;
extern float lastAttack;
extern float lastMove;
extern int orbwalkKey;
extern bool Waitingmouseorbwalker;

extern POINT originalPos;

extern void DrawCircle(ImDrawList* canvas, const Vector3& worldPos, float radius, bool filled, int numPoints, ImColor color, float thickness);

extern HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

extern HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

