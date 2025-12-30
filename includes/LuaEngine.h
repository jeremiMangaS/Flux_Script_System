#pragma once

#include <string>
#include <filesystem>
#include <opencv2/opencv.hpp>

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

class LuaEngine {
    public :
        static inline cv::Mat* globalFramePointer = nullptr;
        LuaEngine();
        ~LuaEngine();
        static int lua_drawText(lua_State* luaMainState);
        static int lua_drawRect(lua_State* luaMainState);
        static int lua_getMotion(lua_State* luaNewState);
        static int lua_saveImg(lua_State* luaMainState);
        bool loadScript(const std::string& filename);
        void reloadChecking(const std::string& filename);
        void errorReport(int status);
        void setGlobalNumber(const std::string& name, double value);
        void callUpdate(double motionValue);
        void sendObjectsToLua(const std::vector<cv::Rect>& objects, const std::string& tableName);
        lua_State* getLuaState() {return luaMainState;}
    private :
        lua_State* luaMainState;
        std::filesystem::file_time_type last_writen;
};