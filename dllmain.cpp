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


#include "Kiero/kiero.h"
#include <dxgi.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include <d3d11.h>
#include "Kiero/minhook/include/MinHook.h"

#include "Menu.h"





//#include "SigScan.h"




bool console = false;
bool dbgToFile = false;


HMODULE myhModule;

//int decimalToHex(int decimal) {
//    std::stringstream stream;
//    stream << std::hex << decimal;
//    std::string hex_string = stream.str();
//    int hex_int = static_cast<int>(strtoul(hex_string.c_str(), nullptr, 16));
//    return hex_int;
//}

inline uint64_t GetDragonIndex(CMinionManager* MinionManager) {
	//std::cout << *MinionListLength << std::endl;

	std::ofstream logfile;

	uint64_t DragonIndex = 0xDEADBEEFF00D;
	const std::vector<std::string> Dragons{ "SRU_Dragon_Air", "SRU_Dragon_Earth", "SRU_Dragon_Water", "SRU_Dragon_Fire", "SRU_Dragon_Hextech", "SRU_Dragon_Chemtech", "SRU_Baron", "SRU_RiftHerald", "SRU_Dragon_Elder" };
	for (uint64_t i = 0; i < *Globals::pMinionListLength; i++) {


		Object* Minion = MinionManager->getMinionByIndex((int)i);
		if (Minion == nullptr) break;
		char* pMinionName = Minion->GetName();
		if (Minion == nullptr) break;
		std::string str(pMinionName);
		if (Minion == nullptr) break;
		Vector3 MinionPos = Minion->GetPos();

		//if (console) {
		//    std::cout << "pMinionName: " << pMinionName << std::endl;
		//    std::cout << "MinionNameLength: " << *MinionNameLength << std::endl;
		//}
		// logi tähän
		//std::cout << MinionNameLength << std::endl;

		Object* me = Globals::localPlayer;



		//logfile2.open("log-dragon.txt", std::ios_base::app);
		//logfile2 << "------------------\n";
		//logfile2 << "\Time = ";
		//logfile2 << *reinterpret_cast<int*>(BaseAddress + Offsets::GameTime);
		//logfile2 << "MinionName:" << &name;
		//logfile2 << "\n";
		//logfile2 << "MinionNameLength:" << &MinionNameLength;
		//logfile2 << "\n";
		//logfile2.close();
		//std::cout << *Dragonx << "  -  " << *Dragony << std::endl;
		float DistanceToDragon = (float)sqrt(pow((MinionPos.x - me->GetPos().x), 2) + pow((MinionPos.z - me->GetPos().z), 2));
		//std::cout << "name: " << name << std::endl;
		//std::cout << "Dragons: " << typeid(Dragons[0]).name() << "\n" << "Name: " << typeid(name).name() << "\n" << std::endl;
		//if(console)std::cout << name << std::endl;
		auto it = std::find(Dragons.begin(), Dragons.end(), pMinionName);
		//logToFile(logfile, intToString((uint64_t)Minion));
		//Sleep(1000000);
		if (it != Dragons.end() && DistanceToDragon < 500.0f) {
			//std::cout << "Distance: " << DistanceToDragon << std::endl;
			//std::cout << "Dx: " << *Dragonx << std::endl;
			//std::cout << "Dy: " << *Dragony << std::endl;
			//std::cout << "Px: " << *Playerx << std::endl;
			//std::cout << "Py: " << *Playery << std::endl;
			DragonIndex = i;
			//std::cout << DragonIndex << std::endl;
		}
		//if (dbgToFile && (asd % 20 == 0)) {
		//	std::ofstream logfile2;
		//	logfile2.open("log-dragon.txt", std::ios_base::app);
		//	logfile2 << "------------------\n";
		//	logfile2 << "\Time = ";
		//	logfile2 << *reinterpret_cast<int*>(BaseAddress + Offsets::GameTime);
		//	logfile2 << "\nDistanceToDragon = ";
		//	logfile2 << DistanceToDragon;
		//	logfile2 << "\n";
		//	logfile2 << "name = ";
		//	logfile2 << name;
		//	logfile2 << "\nMinionNameLength = ";
		//	logfile2 << *MinionNameLength;
		//	logfile2 << "\nDragonIndex = ";
		//	logfile2 << DragonIndex;
		//	logfile2 << "\n";
		//	logfile2.close();
		//}
	}

	return DragonIndex;
}

//class Chat {
//public:
//    void printChat(const char* message) noexcept
//    {
//		static const auto PrintChat{ reinterpret_cast<void(__fastcall*)(void*, const char*, int)>(std::uintptr_t(::GetModuleHandle(nullptr)) + Offsets::fPrintChat) };
//        PrintChat(this, message, 4);
//    }
//};
//
//[[nodiscard]] __forceinline auto getChat() noexcept { return *reinterpret_cast<Chat**>(GetModuleHandle(NULL) + Offsets::oChatClient); }


uint64_t __stdcall EjectThread(LPVOID lpParameter) {
	Sleep(100);
	FreeLibraryAndExitThread(myhModule, 0);

	return 0;
}

uint64_t WINAPI MainThread(HMODULE hModule) {

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
		float* GameTimePtr = (float*)(Globals::BaseAddress + Offsets::GameTime);
		if (GameTimePtr != nullptr || *GameTimePtr > 3.0f) break;
		Sleep(300);
	}

	fninit();

	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);

	logToFile(logfile, "1.1");
	logToFile(logfile, "1.2");
	CMinionManager* MinionManager = new CMinionManager();
	logToFile(logfile, "1.3");

	//logToFile(logfile, "asdaasdasdasd");
	//logToFile(logfile, intToString((uint64_t)Globals::MinionList));

	Funcs::PrintChat(u8"--- H\u00e4kit p\u00e4\u00e4ll\u00e4 ---"); // Häkit päällä

	//while (!GetAsyncKeyState(VK_HOME)) {
	//	Sleep(1000);
	//}

		//typedef uint64_t(__fastcall* fnSendChat)(void*);
		//fnSendChat ingame_SendChat = (fnSendChat)(Globals::BaseAddress + 0x842A50);

		//std::string message = "kebaab";

		//ingame_SendChat(*(void**)(Globals::BaseAddress + 0x421F888));

	Object* me = Globals::localPlayer;

	//const char* pattern = "48 8B 05 ? ? ? ? 48 85 C9 0F 84 ? ? ? ?"; 
	//std::vector<int> pattern2 = { 0x48, 0x8B, 0x05, -1, -1, -1, -1, 0x48, 0x85, 0xC9, 0x0F, 0x84, -1, -1, -1, -1 };

	//uint64_t address = GetAddressFromSignature(pattern2, BaseAddress + 0x350000, BaseAddress + 0x370000);
	//logfile << "address found: " << address << std::endl;

	//ObjManager = (CObjectManager*)(baseAddr + oObjManager);

	//getChat()->printChat("Miki_on_homo");


	//typedef void(__fastcall* fnPrintChat)(DWORD, const char*, int);

	//// Function object											Pointing game function to the object
	//fnPrintChat PrintChat = (fnPrintChat)((DWORD)GetModuleHandle(NULL) + Offsets::fPrintChat);

	//// Executing function
	//PrintChat(BaseAddress + Offsets::oChatClient, "Miki on homo", 0xFFFFFF);

	//std::cout << std::hex << BaseAddress << std::endl;

	//const uint64_t Localplayer = *reinterpret_cast<uint64_t*>(BaseAddress + Offsets::LocalPlayer);     //toimii
	logToFile(logfile, "1.4");
	int SmiteSlot = GetSmiteSlot();
	logToFile(logfile, "1.55");
	logfile << "Smite slot:" << SmiteSlot;

	//Funcs::PrintChat(Spells::getSpellByIndex(4)->GetSpellInfo()->GetSpellName());
	//Funcs::PrintChat(Spells::getSpellByIndex(4)->GetSpellInfo()->GetSpellNameLength());

	/*float* SmiteDamage = reinterpret_cast<float*>(spell1 + 0x84);*/

	//float* y = (float*)GetPointerAddress(BaseAddress + 0x00109B74, { 0x3C });

	//std::cout << std::hex << Localplayer << std::endl;
	//std::cout << std::hex << smite1 << std::endl;

	//auto minionList = MinionManager.getMinionList();
	//int* MinionListLength = MinionManager->getMinionListLengthPtr();
	//int* MinionListLength = MinionManager->getMinionListLengthPtr();
	//int MinionListLength;
	//std::stringstream ss;
	//ss << std::hex << *MinionListLengthHex;
	//ss >> MinionListLength;
	//std::cout << "Smite damage: " << SmiteDamage << std::endl;
	//std::cout << "Minionlist Length: " << *MinionListLength << std::endl;
	//std::cout << "--------------" << "\n" << std::endl;
	//std::cout << MinionList << std::endl;
	//uint64_t Minion = (uint64_t)GetPointerAddress(BaseAddress + 0x251F22C, { 0x4, (0x4 * 15), 0x2B04, 0x0 });
	//std::string name = ""; 
	//for (int i = 0; i < *MinionListLength; ++i) {
	//    uint64_t Minion = (uint64_t)GetPointerAddress(BaseAddress + 0x251F22C, { 0x4, (0x4 * (unsigned long)i), 0x2B04, 0x0 });
	//    std::string name = "";
	//    for (int j = 0; j < 32; ++j) {
	//        unsigned char* p = (unsigned char*)(Minion + 0x1 * j);
	//        if (*p == '\0') break;
	//        name.push_back(*p);
	//    }
	//    //std::cout << "name: " << name << std::endl;
	//    if (std::find(Dragons.begin(), Dragons.end(), name) != Dragons.end()) { DragonIndex = i; std::cout << "asdassadsadasdasdsadsad " << std::endl; }
	//}
	//for (int i = 0; i < 16; ++i) {
	//    unsigned char* p = (unsigned char*)(Minion + 0x1 * i);
	//    name.push_back(*p);
	//    std::cout << *p << std::endl;
	//}
	//std::cout << "name: " << name << std::endl;
	//std::string Minion2 = *Minion;
	//std::cout << Minion2.substr(0, 32) << std::endl;
	//int DistanceToDragon = sqrt(pow((*Dragonx - *Playerx), 2) + pow((*Dragony - *Playery), 2));
	//std::cout << *Dragonx << std::endl;
	//std::cout << *Dragony << std::endl;
	//std::cout << std::dec << DistanceToDragon << std::endl;
	//float* y = (float*)GetPointerAddress(BaseAddress + 0x00109B74, { 0x3C });
	//std::cout << "Health address: " << health << std::endl;
	//while(!GetAsyncKeyState(VK_END)) {
	//    if (*TargetHealth < 600 && *TargetHealth > 0 && GetAsyncKeyState(VK_MENU)) {
	//        SendKey(33);
	//    } 
	//    Sleep(50);
	//}
	//Vector3 pos = { 500.0f, 0.0f, 500.0f };
	//uint64_t RendererAddress = *reinterpret_cast<uint64_t*>(BaseAddress + 0x319E770);
	//GameRenderer renderer;
	//Vector2 result = renderer.WorldToScreen(pos, RendererAddress, BaseAddress, myhModule);
	//std::cout << result.x << " - " << result.y << std::endl;
	//if(result.x > 1920 || result.x < -1920 || result.y < )

	logfile << "adsadasdasdadsadas";
	//logToFile(logfile, intToString((uint64_t)MinionListLength));




	//         char* pMinionName = (char*)GetPointerAddress(BaseAddress + Offsets::MinionList, { 0x8, (0x8 * (unsigned long)i), Offsets::Name});

	logfile << "stats: " << *Globals::pMinionListLength << "  " << me << "  " << MinionManager;
	logfile.close();
	while (!GetAsyncKeyState(VK_END)) {

		if (GetAsyncKeyState(VK_DELETE)) {
			for (int i = 0; i < 11; i++) {
				Funcs::SendChat("?");
			}
			Sleep(2000);
		}

		if (!Globals::localPlayer->IsAlive()) { Sleep(50); continue; }

		//uint64_t HudInstance = *(uint64_t*)(Globals::BaseAddress + Offsets::HudInstance);
		//uint64_t HudInstanceSpellInfo = *(uint64_t*)(HudInstance + Offsets::HudInstanceSpellInfo);

		//if (GetAsyncKeyState(VK_HOME)) {
		//	CastSpellWrapper((uint64_t*)HudInstanceSpellInfo, (uint64_t*)(HudInstanceSpellInfo + 8));
		//}

		uint64_t DragonIndex = GetDragonIndex(MinionManager);
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
		if (GetAsyncKeyState(VK_PRIOR)) {
			logToFile(logfile, "not in autosmite func");
			logToFile(logfile, intToString((DragonIndex)));
			logToFile(logfile, intToString((int)GetSmiteDamage()));
		}

		if (DragonIndex != 0xDEADBEEFF00D && GetSmiteDamage() != 0) {

			Object* Dragon = MinionManager->getMinionByIndex((int)DragonIndex);
			Vector3 DragonPos = Dragon->GetPos();
			float DragonHealth = Dragon->GetHealth();
			Vector3 pos = { DragonPos.x, 30.0f, DragonPos.z };
			Vector2 ScreenPos = renderer.WorldToScreen(pos);
			////std::cout << result.x << " | " << result.y << std::endl;
			double DistanceToDragon = (double)sqrt(pow((DragonPos.x - me->GetPos().x), 2) + pow((DragonPos.z - me->GetPos().z), 2));

			//logToFile(logfile, "stats:");
			//logToFile(logfile, intToString(DragonHealth));
			//logToFile(logfile, intToString(DistanceToDragon));
			//logToFile(logfile, intToString(*SmiteDamage));

			if (GetAsyncKeyState(VK_PRIOR)) {
				logToFile(logfile, intToString(DistanceToDragon < 500));
				logToFile(logfile, intToString((DragonHealth <= GetSmiteDamage())));
				logToFile(logfile, intToString(DragonHealth > 0));

				logToFile(logfile, "---------");

				logToFile(logfile, intToString(DistanceToDragon));
				logToFile(logfile, intToString((DragonHealth)));
				logToFile(logfile, intToString((GetSmiteDamage())));
				logToFile(logfile, intToString(DragonHealth));
				logToFile(logfile, "---------");
			}

			int key = 0;
			//std::cout << SmiteSlot << std::endl;
			if (SmiteSlot == 4) key = 33;
			else if (SmiteSlot == 5) key = 32;
			if (DistanceToDragon < 500 && (DragonHealth <= GetSmiteDamage()) && DragonHealth > 0 && IsPointOnScreen(ScreenPos)) {
				ClickAt(ScreenPos, key);
			}
			Sleep(5);
		}
		else Sleep(50);
		//Sleep(50);

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
		DisableThreadLibraryCalls(myhModule);
		_beginthreadex(nullptr, 0, (_beginthreadex_proc_type)MainThread, hModule, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:

		break;
	}
	return TRUE;

}