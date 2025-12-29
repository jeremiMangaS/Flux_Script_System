#include "../includes/VisionEngineSystem.h"

VisionEngineSystem::VisionEngineSystem() {
    std::cout << "System | Vision Engine System Initialization" << std::endl;
}

VisionEngineSystem::~VisionEngineSystem() {
    vidCapture.release();
    cv::destroyAllWindows();
    std::cout << "System | Closing Vision Engine System" << std::endl;
}

cv::Mat VisionEngineSystem::getNextFrame() {
    cv::Mat frame;
    vidCapture >> frame;
    return frame;
}

void VisionEngineSystem::showFrame(const std::string& windowName, cv::Mat frame) {
    if (!frame.empty()) {
        cv::imshow(windowName, frame);
    }
}

bool VisionEngineSystem::isWindowOpen() {
    return cv::waitKey(1) != 'q';
}

bool VisionEngineSystem::openCamera(int index) {
    return true;
}