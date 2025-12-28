#pragma once

#include <string>
#include <filesystem>

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

class LuaEngine {
    public :
        LuaEngine();
        ~LuaEngine();
        bool loadScript(const std::string& filename);
        void reloadChecking(const std::string& filename);
        void errorReport(int status);
    private :
        lua_State* luaMainState;
        std::filesystem::file_time_type last_writen;
};