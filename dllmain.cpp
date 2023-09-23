#include <Windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Vector.h"
//#include "CopyThread.h"
#include <cstdint>
#include <cmath>
#include <algorithm>
#include "Input.h"
#include "Renderer.h"
#include "Offsets.h"
#include "Utils.h"
#include <process.h>
#include <fstream>
#include "MinionManager.h"
#include <regex>
#include "Globals.h"
#include "Object.h"
#include <conio.h>

#include "Kiero/kiero.h"
#include <dxgi.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include <d3d11.h>
#include "Kiero/minhook/include/MinHook.h"

#include "Menu.h"




bool console = false;
bool dbgToFile = false;


HMODULE myhModule;

uint64_t __stdcall EjectThread(LPVOID lpParameter) {
	Sleep(100);
	FreeLibraryAndExitThread(myhModule, 0);

	return 0;
}

__declspec(dllexport) uint64_t WINAPI MainThread(HMODULE hModule) {

	std::ofstream logfile;
	logfile.open("log-kebab.txt", std::ios_base::app);

	FILE* f = NULL;
	if (console) {
		AllocConsole();
		freopen_s(&f, "CONOUT$", "w", stdout);

		printf("--- Loli koodit ---");
		printf("\n");
	}
	logfile << "\n" << "----------" << "\n";
	Sleep(100);

	while (true) {
		float* GameTimePtr = (float*)(Globals::BaseAddress + oGameTime);
		if (GameTimePtr != nullptr || *GameTimePtr > 3.0f) break;
		Sleep(300);
	}

	Utils::fninit();

	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
			kiero::bind(13, (void**)&oResizeBuffers, hkResizeBuffers);
			init_hook = true;
		}
	} while (!init_hook);

	CObjectManager* MinionManager = *(CObjectManager**)(Globals::BaseAddress + oMinionList);


	Funcs::PrintChat(u8"--- H\u00e4kit p\u00e4\u00e4ll\u00e4 ---"); // Häkit päällä


	Object* me = Globals::localPlayer;

	int SmiteSlot = Utils::GetSmiteSlot();

	logfile << "stats: " << *Globals::pMinionListLength << "  " << me << "  " << MinionManager;
	while (!GetAsyncKeyState(VK_END)) {

		if (!Globals::localPlayer->IsAlive()) { Sleep(50); continue; }

		int gameState = *(int*)(*(uint64_t*)(Globals::BaseAddress + oHudInstance) + 0xB8);
		bool gameEnded = (bool)(gameState & 0x10000);
		if (gameEnded) break;

		if (GetAsyncKeyState(VK_DELETE)) {
		Funcs::SendChat("#........#..#..........#....#####....");
		Funcs::SendChat("#......#......#......#....#..............#..");
		Funcs::SendChat("#....#.........#..#......#..................");
		Funcs::SendChat("###.............#..........#####....");
		Funcs::SendChat("#....#............#.......................#..");
		Funcs::SendChat("#......#..........#........#............#..");
		Funcs::SendChat("#........#........#..........#####....");
		Sleep(2000);
		}



		if (GetAsyncKeyState(VK_PRIOR)) {

			//CObjectManager* Turretlist = *(CObjectManager**)(Globals::BaseAddress + oTurretList);

			//for (int i = 0; i < Turretlist->GetListSize(); i++) {
			//	Object* Turret = Turretlist->getMinionByIndex(i);
			//	Utils::logToFile(logfile, std::to_string(Turret->GetHealth()));
			//}

			

			uint64_t BuffManagerStart = *(uint64_t*)(*(uint64_t*)(Globals::BaseAddress + oLocalPlayer) + 0x27C8);
			uint64_t BuffManagerEnd = *(uint64_t*)(*(uint64_t*)(Globals::BaseAddress + oLocalPlayer) + 0x27D0);

			//Funcs::PrintChat(BuffManagerStart);
			//Funcs::PrintChat(BuffManagerEnd);
			for (uint64_t addr = BuffManagerStart; addr < BuffManagerEnd - 0x20; addr = addr + 0x10) {
				if (*(uint64_t*)((*(uint64_t*)addr) + 0x10) == 0) continue;
				const char* name = (const char*)(*(uint64_t*)((*(uint64_t*)addr) + 0x10) + 0x8);
				std::string strName = std::string(name);
				Utils::logToFile(logfile, strName);
			}
			Sleep(2000);
		}

		//uint64_t HudInstance = *(uint64_t*)(Globals::BaseAddress + HudInstance);
		//uint64_t HudInstanceSpellInfo = *(uint64_t*)(HudInstance + HudInstanceSpellInfo);
		//if (GetAsyncKeyState(VK_HOME)) {
		//	CastSpellWrapper((uint64_t*)HudInstanceSpellInfo, (uint64_t*)(HudInstanceSpellInfo + 8));
		//}
		//Minion* Minion = MinionManager->getMinionByIndex(5);
		//std::cout << Minion << std::endl;
			//std::ofstream logfile2;
			//logfile2.open("log-dragon.txt", std::ios_base::app);
			//logfile2 << "------------------\n";
			//logfile2 << "Minion = ";
			//logfile2 << Minion->GetNameLengthptr();
			//logfile2 << "\n";
			//logfile2.close();
		//if (dbgToFile && SmiteDamage != nullptr) {
		//    logfile << "\nDragonIndex = ";
		//    logfile << DragonIndex;
		//    logfile << "\nSmiteDamage = ";
		//    logfile << *SmiteDamage;
		//    logfile << "\n";
		//    logfile << "\n";
		//}
		//if (GetAsyncKeyState(VK_PRIOR)) {
		//	Utils::logToFile(logfile, "not in autosmite func");
		//	//logToFile(logfile, intToString((DragonIndex)));
		//	Utils::logToFile(logfile, Utils::intToString((int)Utils::GetSmiteDamage()));
		//}
		//float GameTime = *(float*)(Globals::BaseAddress + GameTime);
		//uint64_t DragonIndex = 0xDEADBEEFF00D;
		//if (GameTime > 180.0f) DragonIndex = MinionManager->GetDragonIndex();
		//if (DragonIndex != 0xDEADBEEFF00D && Utils::GetSmiteDamage() != 0 && Globals::autosmite & 1 && GameTime > 180.0f ) {
		//	Object* Dragon = MinionManager->getMinionByIndex((int)DragonIndex);
		//	Vector3 DragonPos = Dragon->GetPos();
		//	float DragonHealth = Dragon->GetHealth();
		//	Vector3 pos = { DragonPos.x, 30.0f, DragonPos.z };
		//	Vector2 ScreenPos = renderer.WorldToScreen(pos);
		//	////std::cout << result.x << " | " << result.y << std::endl;
		//	double DistanceToDragon = (double)sqrt(pow((DragonPos.x - me->GetPos().x), 2) + pow((DragonPos.z - me->GetPos().z), 2));
		//	//logToFile(logfile, "stats:");
		//	//logToFile(logfile, intToString(DragonHealth));
		//	//logToFile(logfile, intToString(DistanceToDragon));
		//	//logToFile(logfile, intToString(*SmiteDamage));
		//	//if (GetAsyncKeyState(VK_PRIOR)) {
		//	//	logToFile(logfile, intToString(DistanceToDragon < 500));
		//	//	logToFile(logfile, intToString((DragonHealth <= Utils::GetSmiteDamage())));
		//	//	logToFile(logfile, intToString(DragonHealth > 0));
		//	//	logToFile(logfile, "---------");
		//	//	logToFile(logfile, intToString(DistanceToDragon));
		//	//	logToFile(logfile, intToString((DragonHealth)));
		//	//	logToFile(logfile, intToString((GetSmiteDamage())));
		//	//	logToFile(logfile, intToString(DragonHealth));
		//	//	logToFile(logfile, "---------");
		//	//}
		//	int key = 0;
		//	//std::cout << SmiteSlot << std::endl;
		//	if (SmiteSlot == 4) key = 32;
		//	else if (SmiteSlot == 5) key = 33;
		//	if (DistanceToDragon < 500 && (DragonHealth <= Utils::GetSmiteDamage()) && DragonHealth > 0 && Utils::IsPointOnScreen(ScreenPos)) {
		//		Smite(ScreenPos, key);
		//	}
		//	Sleep(5);
		//}
		//else Sleep(50);

		Sleep(50);

		//GameRenderer renderer;
		//Vector2 ScreenCoordinates = renderer::WorldToScreen(pos, RendererAddress, BaseAddress, NULL);
		//std::cout << ScreenCoordinatces.x << ScreenCoordinates.y << std::endl;

	}


	if (GetAsyncKeyState(VK_END) && console && f != NULL) {
		fclose(f);
		std::cout << "Unloading" << std::endl;
		FreeConsole();
		//if(dbgToFile)logfile.close();
	}

	Funcs::PrintChat(u8"--- H\u00e4kit pois ---"); // Häkit pois

	kiero::shutdown();

	_beginthreadex(0, 0, (_beginthreadex_proc_type)EjectThread, 0, 0, 0);

	if (console) {
		FreeConsole();
	}
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, uint64_t reason, LPVOID lpReserved) {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		myhModule = hModule;
		//DisableThreadLibraryCalls(myhModule);
		_beginthreadex(nullptr, 0, (_beginthreadex_proc_type)MainThread, hModule, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:

		break;
	}
	return TRUE;

}