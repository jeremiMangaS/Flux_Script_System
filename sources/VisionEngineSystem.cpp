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
    // return cv::waitKey(1) != 'q';
    return true;
}

bool VisionEngineSystem::openCamera(int index) {
    vidCapture.open(index);
    return vidCapture.isOpened();
}

double VisionEngineSystem::getMotion(cv::Mat currentFrame) {
    if (currentFrame.empty()) return 0.0;

        // Gray Scale
        cv::Mat grayScale, deltaFrame, thresh;
        cv::cvtColor(currentFrame, grayScale, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(grayScale, grayScale, cv::Size(21, 21), 0);

    // First frame
    if (previouslyFrame.empty()) {
        previouslyFrame = grayScale.clone();
        return 0.0;
    }

    // Detect the Different
    // By calculating the difference
    cv::absdiff(previouslyFrame, grayScale, deltaFrame);
    cv::threshold(deltaFrame, thresh, 25, 255, cv::THRESH_BINARY);

    double motion = (double)cv::countNonZero(thresh);

    previouslyFrame = grayScale.clone();
    return motion;
}