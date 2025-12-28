// Local 
    #include "../includes/LuaEngine.h"
#include <iostream>

LuaEngine::LuaEngine() {
    luaMainState = luaL_newstate();
    luaL_openlibs(luaMainState);
    std::cout << "System | Lua Engine initialization\n";
}

LuaEngine::~LuaEngine() {
    if (luaMainState) {
        lua_close(luaMainState);
        std::cout << "System | Closing lua state\n";
    }
}

bool LuaEngine::loadScript(const std::string& filename) {
    int status = luaL_dofile(luaMainState, filename.c_str());
    if (status != LUA_OK) {
        errorReport(status);
        return false;
    } return true;
}

void LuaEngine::errorReport(int status) {
    if (status != LUA_OK) {
        std::cerr << "System Error | " << lua_tostring(luaMainState, -1) << std::endl;
        lua_pop(luaMainState, 1);
    }   
}

void LuaEngine::reloadChecking(const std::string& filename) {
    try {
        auto current_write_time = std::filesystem::last_write_time(filename);
        if (current_write_time != last_writen) {
            std::cout << "System : reloading a new script" << std::endl;
            last_writen = current_write_time;
            loadScript(filename);
        }
    } catch (std::filesystem::filesystem_error& e) {
        std::cerr << "System error | " << e.what();
    }
}
