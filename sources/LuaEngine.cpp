// Local 
    #include "../includes/LuaEngine.h"
#include <iostream>

LuaEngine::LuaEngine() {
    luaMainState = luaL_newstate();
    luaL_openlibs(luaMainState);
    lua_register(luaMainState, "drawText", lua_drawText);
    lua_register(luaMainState, "drawRect", lua_drawRect);
    lua_register(luaMainState, "saveImg", lua_saveImg);
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

// TESTING
int LuaEngine::lua_getMotion(lua_State* luaNewState) {
    lua_pushnumber(luaNewState, 100.0); // Push to LUA stack
    return 1;
}

void LuaEngine::setGlobalNumber(const std::string& name, double value) {
    lua_pushnumber(luaMainState, value);
    lua_setglobal(luaMainState, name.c_str());
}

void LuaEngine::callUpdate(double motionValue) {
    lua_getglobal(luaMainState, "on_update");
    if (lua_isfunction(luaMainState, -1)) {
        lua_pushnumber(luaMainState, motionValue);
        if (lua_pcall(luaMainState, 1, 0, 0) != LUA_OK) {
            std::cerr << "System Error | Cannot calling on_update from LUA\nMessage : " << lua_tostring(luaMainState, -1) << std::endl;
            lua_pop(luaMainState, 1);
        }
    } else {
        lua_pop(luaMainState, 1);
    }
}

int LuaEngine::lua_drawText(lua_State* luaMainState) {
    const char* text = luaL_checkstring(luaMainState, 1);
    //  x y r g b
    int x = luaL_checkinteger(luaMainState, 2);
    int y = luaL_checkinteger(luaMainState, 3);
    double scale = luaL_checknumber(luaMainState, 4);
    int r = luaL_checkinteger(luaMainState, 5);
    int g = luaL_checkinteger(luaMainState, 6);
    int b = luaL_checkinteger(luaMainState, 7);
    if (globalFramePointer != nullptr && !globalFramePointer->empty()) {
        cv::putText(*globalFramePointer, text, cv::Point(x, y), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(b, g, r), 2);
    }
    return 0;
}

int LuaEngine::lua_drawRect(lua_State* luaMainState) {
    // x y w h r g b
    int x = luaL_checkinteger(luaMainState, 1);
    int y = luaL_checkinteger(luaMainState, 2);
    int w = luaL_checkinteger(luaMainState, 3);
    int h = luaL_checkinteger(luaMainState, 4);
    int r = luaL_checkinteger(luaMainState, 5);
    int g = luaL_checkinteger(luaMainState, 6);
    int b = luaL_checkinteger(luaMainState, 7);
    if (globalFramePointer && !globalFramePointer->empty()) {
        cv::rectangle(*globalFramePointer, cv::Rect(x, y, w, h), cv::Scalar(b, g, r), 2);
    }
    return 0;
}

void LuaEngine::sendObjectsToLua(const std::vector<cv::Rect>& objects, const std::string& tableName) {
    lua_newtable(luaMainState);
    for (int i = 0; i < objects.size(); i++) {
        lua_pushinteger(luaMainState, i + 1);
        
        lua_newtable(luaMainState); // x y w h
            lua_pushinteger(luaMainState, objects[i].x);
            lua_setfield(luaMainState, -2, "x");
            lua_pushinteger(luaMainState, objects[i].y);
            lua_setfield(luaMainState, -2, "y");
            lua_pushinteger(luaMainState, objects[i].width);
            lua_setfield(luaMainState, -2, "w");
            lua_pushinteger(luaMainState, objects[i].height);
            lua_setfield(luaMainState, -2, "h");
        lua_settable(luaMainState, -3);
    }
    lua_setglobal(luaMainState, tableName.c_str()); // Lua Variable
}

int LuaEngine::lua_saveImg(lua_State* luaMainState) {
    const char* filename = luaL_checkstring(luaMainState, 1);
    if (globalFramePointer != nullptr && !globalFramePointer->empty()) {
        cv::imwrite(filename, *globalFramePointer);
        std::cout << "SYSTEM | Photo taken and saved at : " << filename << std::endl;
    }
    return 0;
}