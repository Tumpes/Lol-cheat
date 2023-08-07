#include "menu.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
bool menuOpen = false;
bool keyPressed = false;
bool Circle = false;
float size = 400.0f;
float oldgametime;
bool autosmite;
std::chrono::steady_clock::time_point lastKeyPressTime = std::chrono::steady_clock::now();



void DrawCircle(ImDrawList* canvas, const Vector3& worldPos, float radius, bool filled, int numPoints, ImColor color, float thickness) {

	if (numPoints >= 200)
		return;
	static ImVec2 points[200];

	float step = 6.2831f / numPoints;
	float theta = 0.f;
	for (int i = 0; i < numPoints; i++, theta += step) {
		Vector3 worldSpace = { worldPos.x + radius * cos(theta), worldPos.y, worldPos.z - radius * sin(theta) };
		Vector2 screenSpace = renderer.WorldToScreen(worldSpace);

		points[i].x = screenSpace.x;
		points[i].y = screenSpace.y;
	}

	if (filled)
		canvas->AddConvexPolyFilled(points, numPoints, color);
	else
		canvas->AddPolyline(points, numPoints, color, true, thickness);
}


HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

		/*if (autosmite & 1 && *(uint64_t*)(Globals::BaseAddress + Offsets::GameTime) - oldgametime > 1000 && Globals::localPlayer->IsAlive()) {
		
			CMinionManager* MinionManager = new CMinionManager();
			uint64_t DragonIndex = MinionManager->GetDragonIndex();
	
			if (DragonIndex != 0xDEADBEEFF00D && GetSmiteDamage() != 0) {
	
				Object* Dragon = MinionManager->getMinionByIndex((int)DragonIndex);
				Vector3 DragonPos = Dragon->GetPos();
				float DragonHealth = Dragon->GetHealth();
				Vector3 pos = { DragonPos.x, 30.0f, DragonPos.z };
				Vector2 ScreenPos = renderer.WorldToScreen(pos);
	
				double DistanceToDragon = (double)sqrt(pow((DragonPos.x - Globals::localPlayer->GetPos().x), 2) + pow((DragonPos.z - Globals::localPlayer->GetPos().z), 2));
	
	
				int key = 0;
				if (GetSmiteSlot() == 4) key = 33;
				else if (GetSmiteSlot() == 5) key = 32;
				if (DistanceToDragon < 500 && (DragonHealth <= GetSmiteDamage()) && DragonHealth > 0 && IsPointOnScreen(ScreenPos)) {
					ClickAt(ScreenPos, key);
				}
			}
			oldgametime = *(uint64_t*)(Globals::BaseAddress + Offsets::GameTime);
			delete MinionManager;
		}*/
	
	if (!keyPressed && GetAsyncKeyState(VK_NEXT) & 1)
	{
		keyPressed = true;
		lastKeyPressTime = std::chrono::steady_clock::now();
	}
	auto currentTime = std::chrono::steady_clock::now();
	if (keyPressed && std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastKeyPressTime).count() > 200) // Adjust the delay as needed
	{
		menuOpen = !menuOpen;
		keyPressed = false;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (menuOpen) {

		//float size = 50;

		//auto draw = ImGui::GetBackgroundDrawList();
		//draw->AddCircle(ImVec2(1920 / 2, 1080 / 2), size, IM_COL32(255, 0, 0, 255), 100, 1.f);

		ImGui::Begin("ImGui Window");
		ImGui::SetNextWindowSize(ImVec2(150.0f, 140.0f), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(25, 25));

		ImGui::Checkbox("Show Circle", &Circle);
		ImGui::Checkbox("Autosmite on", &Globals::autosmite);

		ImGui::End();


	}

	if (Circle) {
		ImGui::Begin("##kebab", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);
		auto draw = ImGui::GetBackgroundDrawList();
		DrawCircle(draw, Globals::localPlayer->GetPos(), Globals::localPlayer->GetRealAttackRange(), 0, 100, IM_COL32(0, 0, 255, 255), 1);
		ImGui::End();
	}

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return oPresent(pSwapChain, SyncInterval, Flags);

}

