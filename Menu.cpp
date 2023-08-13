#include "menu.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef HRESULT(__stdcall* ResizeBuffers) (IDXGISwapChain* pThis, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
ResizeBuffers oResizeBuffers;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
IDXGISwapChain* gSwapchain;

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

void DrawCircle(ImDrawList* canvas, const Vector3& worldPos, float radius, bool filled, int numPoints, ImColor color, float thickness) {
	// takes world units as radius input
	//

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

bool init = false;
bool menuOpen = false;
bool keyPressed = false;
bool Circle = false;
float oldgametime;
bool autosmite;
bool CoolDownToggle;
bool Orbwalker;
bool Waitingmouseclick;
bool Waitingmouseorbwalker;
float lastAttack = 0.0f;
float lastMove = 0.0f;

POINT originalPos = {};
std::chrono::steady_clock::time_point lastKeyPressTime = std::chrono::steady_clock::now();

HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{

	if (mainRenderTargetView) {
		pContext->OMSetRenderTargets(0, 0, 0);
		mainRenderTargetView->Release();
	}

	HRESULT hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	ID3D11Texture2D* pBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
	// Perform error handling here!

	pDevice->CreateRenderTargetView(pBuffer, NULL, &mainRenderTargetView);
	// Perform error handling here!
	pBuffer->Release();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);

	// Set up the viewport.
	D3D11_VIEWPORT vp;
	vp.Width = Width;
	vp.Height = Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1, &vp);
	return hr;
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

		ImGui::Checkbox("Show Attack Range", &Circle);
		ImGui::Checkbox("Autosmite", &autosmite);
		ImGui::Checkbox("Show Cooldowns (not enemy)", &CoolDownToggle);
		ImGui::Checkbox("Orbwalker", &Orbwalker);

		ImGui::End();


	}

	if (autosmite && Globals::localPlayer->IsAlive()) {

		CMinionManager* MinionManager = *(CMinionManager**)(Globals::BaseAddress + Offsets::MinionList);
		uint64_t DragonIndex = MinionManager->GetDragonIndex();

		if (DragonIndex != 0xDEADBEEFF00D && Utils::GetSmiteDamage() != 0) {

			Object* Dragon = MinionManager->getMinionByIndex((int)DragonIndex);
			Vector3 DragonPos = Dragon->GetPos();
			float DragonHealth = Dragon->GetHealth();
			Vector3 pos = { DragonPos.x, DragonPos.y, DragonPos.z };
			Vector2 ScreenPos = renderer.WorldToScreen(pos);

			double DistanceToDragon = (double)sqrt(pow((DragonPos.x - Globals::localPlayer->GetPos().x), 2) + pow((DragonPos.z - Globals::localPlayer->GetPos().z), 2));


			int key = 0;
			if (Utils::GetSmiteSlot() == 4) key = 32;
			else if (Utils::GetSmiteSlot() == 5) key = 33;
			if (DistanceToDragon < 500 && (DragonHealth <= Utils::GetSmiteDamage()) && DragonHealth > 0 && Utils::IsPointOnScreen(ScreenPos) && !Waitingmouseclick) {
				BlockInput(true);
				GetCursorPos(&originalPos);
				SetCursorPos(ScreenPos.x, ScreenPos.y);
				PressKeyScan(key);
				if (!Waitingmouseclick) oldgametime = Funcs::GetGameTime();
				Waitingmouseclick = true;
				MouseUp(1);
			}
			if (Funcs::GetGameTime() - oldgametime > 0.005f && Waitingmouseclick) {
				Waitingmouseclick = false;
				ReleaseKeyScan(key);
				SetCursorPos(originalPos.x, originalPos.y);
				BlockInput(false);
			}
		}
	}

	ImGui::Begin("##kebab", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);

	auto draw = ImGui::GetBackgroundDrawList();



	if (Circle) {
		CMinionManager* HeroManager = *(CMinionManager**)(Globals::BaseAddress + Offsets::HeroList);

		for (int i = 0; i < HeroManager->GetListSize(); i++) {
			Object* Hero = HeroManager->getMinionByIndex(i);
			if (!Hero->IsEnemy() && Hero == Globals::localPlayer) DrawCircle(draw, Hero->GetPos(), Hero->GetRealAttackRange(), 0, 100, IM_COL32(255, 0, 0, 255), 1);
			else if(Hero->IsEnemy()) DrawCircle(draw, Hero->GetPos(), Hero->GetRealAttackRange(), 0, 100, IM_COL32(0, 0, 255, 255), 1);
		}
	}

	if (CoolDownToggle) {
		CMinionManager* HeroManager = *(CMinionManager**)(Globals::BaseAddress + Offsets::HeroList);

		for (int i = 0; i < HeroManager->GetListSize(); i++) {
			Object* Hero = HeroManager->getMinionByIndex(i);
			for (int j = 0; j <= 5; j++) {
				const char* text = "";
				Vector2 Screenpos = renderer.WorldToScreen(Hero->GetPos());
				if (j == 0) text = "Q";
				if (j == 1) text = "W";
				if (j == 2) text = "E";
				if (j == 3) text = "R";
				if (j == 4) text = "D";
				if (j == 5) text = "F";

				draw->AddText(ImVec2(Screenpos.x - 75 + j * 25, Screenpos.y - 200), IM_COL32(255, 255, 255, 255), text);

				float Cooldown = Hero->getSpellByIndex(j)->GetSpellCooldown();
				std::string strCooldown = std::to_string((int)std::ceil(Cooldown));
				const char* ptrCooldown = strCooldown.c_str(); // Now the pointer is valid

				draw->AddText(ImVec2(Screenpos.x - 75 + j * 25, Screenpos.y - 180), IM_COL32(255, 255, 255, 255), ptrCooldown);
			}
		}
	}

	if (Orbwalker && Globals::localPlayer->CanAttack()) {
		CMinionManager* HeroManager = *(CMinionManager**)(Globals::BaseAddress + Offsets::HeroList);

		std::vector<Object*> attackable;

		for (int i = 0; i < HeroManager->GetListSize(); i++) {
			Object* Hero = HeroManager->getMinionByIndex(i);
			if (Hero == Globals::localPlayer) continue;

			float distance = Hero->DistanceToObject(Globals::localPlayer);
			if (distance < Globals::localPlayer->GetRealAttackRange() && Hero->IsValidTarget()) {
				attackable.push_back(Hero);
			}
		}

		Object* target = nullptr;
		float lowHealth = 1000000000000; // hp should never he this high so its fine

		for (int i = 0; i < attackable.size(); i++) {
			if (attackable[i]->GetHealth() < lowHealth) {
				lowHealth = attackable[i]->GetHealth();
				target = attackable[i];
			}
		}
		if (target != nullptr && lastAttack + Globals::localPlayer->GetAttackDelay() + .004f < Funcs::GetGameTime()) {
			Vector3 pos = target->GetPos();
			Vector2 screenpos = renderer.WorldToScreen(pos);
			Funcs::AttackMoveOnPos(screenpos);
			lastAttack = Funcs::GetGameTime() + Globals::localPlayer->GetAttackWindUp();
		}
		else if (target != nullptr && Funcs::GetGameTime() > lastAttack + Globals::localPlayer->GetAttackWindUp() && lastMove < Funcs::GetGameTime()) {
			//if (Funcs::GetGameTime() <= lastAttack + Globals::localPlayer->GetAttackDelay() && Funcs::GetGameTime() < lastMove) {

			POINT pos;
			Vector2 vectorpos;
			GetCursorPos(&pos);
			vectorpos.x = pos.x;
			vectorpos.y = pos.y;
			Funcs::MoveOnPos(vectorpos);

			lastMove = Funcs::GetGameTime() + 0.005f;
		}

	}

	ImGui::End();

	ImGui::Render();


	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return oPresent(pSwapChain, SyncInterval, Flags);

}

