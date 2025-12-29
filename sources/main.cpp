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

        double motion = vc.getMotion(frame);
        luaEngine.setGlobalNumber("current_motion", motion);
        
        luaEngine.reloadChecking(script_path);

        vc.showFrame("NexLogic Monitor", frame);

        // std::this_thread::sleep_for(std::chrono::milliseconds(500));

        if (cv::waitKey(1) == 'q') break;
    }

    return 0;
}