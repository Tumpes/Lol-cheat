#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include "Offsets.h"
#include <fstream>
#include "Globals.h"
#include "Object.h"
#include "MinionManager.h"
#include <sstream>

class Utils {

public:

     static std::string ReadString(void* dst, void* addr, int length) {
        char name[32];

        memcpy(&name, addr, length);

        name[length] = '\0';
        std::string str(name);
        return name;
    }

    static float GetSmiteDamage() {

        float SmiteDamage = 0;

        // -------------------------

        Object* me = Globals::localPlayer;

        std::string spell1Name = me->getSpellByIndex(4)->GetSpellInfo()->GetSpellName();
        std::string spell2Name = me->getSpellByIndex(5)->GetSpellInfo()->GetSpellName();

        //Funcs::PrintChat(spell1Name);
        //Funcs::PrintChat(spell2Name);

        if (spell1Name == "SummonerSmite" || spell2Name == "SummonerSmite") {
            SmiteDamage = 600.0f;
        }
        else if (spell1Name == "S5_SummonerSmitePlayerGanker" || spell2Name == "S5_SummonerSmitePlayerGanker")
        {
            SmiteDamage = 900.0f;
        }
        else if (spell1Name == "SummonerSmiteAvatarUtility" || spell2Name == "SummonerSmiteAvatarUtility" || spell1Name == "SummonerSmiteAvatarDefensive" || spell2Name == "SummonerSmiteAvatarDefensive" || spell1Name == "SummonerSmiteAvatarOffensive" || spell2Name == "SummonerSmiteAvatarOffensive") {
            SmiteDamage = 1200.0f;
        }

        return SmiteDamage;
    }

    static int GetSmiteSlot() {

        int SmiteSlot = 0;

        Object* me = Globals::localPlayer;

        std::string spell1Name = me->getSpellByIndex(4)->GetSpellInfo()->GetSpellName();
        std::string spell2Name = me->getSpellByIndex(5)->GetSpellInfo()->GetSpellName();

        if (spell1Name == "SummonerSmite" || spell1Name == "S5_SummonerSmitePlayerGanker" || spell1Name == "SummonerSmiteAvatarUtility" || spell1Name == "Smite") {
            SmiteSlot = 4;
        }
        else if (spell2Name == "SummonerSmite" || spell2Name == "S5_SummonerSmitePlayerGanker" || spell2Name == "SummonerSmiteAvatarUtility" || spell2Name == "Smite") {
            SmiteSlot = 5;
        }

        return SmiteSlot;
    }

    static uint64_t GetPointerAddress(uint64_t ptr, std::vector<uint64_t> offsets)

    {
        uint64_t addr = ptr;
        for (int i = 0; i < offsets.size(); ++i) {
            addr = *(uint64_t*)addr;
            addr += offsets[i];
        }

        return addr;
    }

    static bool IsPointOnScreen(Vector2 pos) {
        if (pos.x < 0 || pos.x > Globals::GetWindowDimensions().x || pos.y < 0 || pos.y > Globals::GetWindowDimensions().y) {
            return false;
        }
        return true;
    }

   static  std::string intToString(uint64_t inputint) {
        std::stringstream stream;
        stream << inputint;

        std::string addressString = stream.str();

        return addressString;
    }

    static void logToFile(std::ofstream& file, std::string message) {
        file.open("log-kebab.txt", std::ios_base::app);

        file << message << std::endl;

        file.close();
    }

    static void fninit() {

        Globals::BaseAddress = (uint64_t)GetModuleHandleA("League of Legends.exe");
        Globals::localPlayer = *(Object**)(Globals::BaseAddress + oLocalPlayer);
        Globals::MinionList = *(CObjectManager**)(Globals::BaseAddress + oMinionList);
        Globals::HeroList = *(CObjectManager**)(Globals::BaseAddress + oHeroList);
        Globals::pMinionListLength = (int*)(*(uint64_t*)(Globals::BaseAddress + oMinionList) + 0x10);
        Globals::HUDInput = *(uint64_t*)(*(uint64_t*)(Globals::BaseAddress + oHudInstance) + 0x24);
    }

};