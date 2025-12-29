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
        void setGlobalNumber(const std::string& name, double value);
        static int lua_getMotion(lua_State* luaNewState);
    private :
        lua_State* luaMainState;
        std::filesystem::file_time_type last_writen;
};