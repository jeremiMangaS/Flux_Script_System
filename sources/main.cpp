#include "../includes/LuaEngine.h"

#include <chrono>
#include <thread>
#include <iostream>

int main()
{
    LuaEngine luaEngine;

    std::string script_path = "scripts/logic.lua";

    // Load file
    luaEngine.loadScript(script_path);

    std::cout << "Application running" << std::endl;

    while (true) {
        luaEngine.reloadChecking(script_path);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}