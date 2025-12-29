cmake_minimum_required(VERSION 3.10)
project(BasicSystemCppLua)
# OpenCV
find_package(OpenCV REQUIRED)
#LUA
set(LUA_INCLUDE_DIR "D:/gcc_g++/msys2/mingw64/include")
set(LUA_LIBRARIES "D:/gcc_g++/msys2/mingw64/lib/liblua.a")
# Includes
include_directories(includes)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${LUA_INCLUDE_DIR})
# Sources
set(SOURCE_FILES 
    sources/main.cpp 
    sources/LuaEngine.cpp 
    sources/VisionEngineSystem.cpp
)

add_executable(MyProgram ${SOURCE_FILES})
# Link OpenCV<->LUA
target_link_libraries(MyProgram ${OpenCV_LIBS} ${LUA_LIBRARIES})