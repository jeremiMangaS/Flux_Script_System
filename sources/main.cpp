#include "../includes/LuaEngine.h"
#include "../includes/VisionEngineSystem.h"

#include <chrono>
#include <thread>
#include <iostream>

int main()
{
    LuaEngine luaEngine;
    VisionEngineSystem vc;

    if (!vc.openCamera(0)) {
        std::cerr << "System | Failed open camera" << std::endl;
        return -1;
    }

    std::string script_path = "../../scripts/logic.lua";

    luaEngine.setGlobalNumber("current_motion", 0);

    // Load file
    luaEngine.loadScript(script_path);

    std::cout << "Application running" << std::endl;

    while (vc.isWindowOpen()) {
        cv::Mat frame = vc.getNextFrame();
        if (frame.empty()) continue;

        luaEngine.globalFramePointer = &frame;

        double motion = vc.getMotion(frame);
        vc.detectFaces(frame);
        auto faces = vc.getDetectedFaces();
        auto objects = vc.getDetectObjects();

        luaEngine.sendObjectsToLua(objects, "detected_list");
        luaEngine.sendObjectsToLua(faces, "face_lists");
        luaEngine.setGlobalNumber("current_motion", motion);

        // Lua Function
        luaEngine.callUpdate(motion);
        
        luaEngine.reloadChecking(script_path);

        vc.showFrame("NexLogic Monitor", frame);

        luaEngine.globalFramePointer = nullptr;

        // std::this_thread::sleep_for(std::chrono::milliseconds(500));

        if (cv::waitKey(1) == 'q') break;
    }

    return 0;
}