#include <iostream>

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

int main()
{
    lua_State* luaState = luaL_newstate();
    luaL_openlibs(luaState);

    std::cout << "Menjalankan LUA" << std::endl;

    int status = luaL_dofile(luaState, "test.lua");
    if (status != LUA_OK) {
        std::string err = lua_tostring(luaState, -1);
        std::cerr << "Error : " << err << std::endl;
    }

    lua_close(luaState);

    return 0;
}