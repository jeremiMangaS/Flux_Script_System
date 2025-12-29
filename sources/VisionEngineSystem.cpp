#include "../includes/VisionEngineSystem.h"

VisionEngineSystem::VisionEngineSystem() {
    std::cout << "System | Vision Engine System Initialization" << std::endl;
    if (!faceCascade.load("../../resources/haarcascade_frontalface_default.xml")) {
        std::cerr << "System Error | Cannot opent or find face rcodnize model" << std::endl;
    }
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
    cv::dilate(thresh, thresh, cv::Mat(), cv::Point(-1, -1), 3);

        // For draw rect
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        detectObjects.clear();

        for (const auto& contour : contours) {
            double area = cv::contourArea(contour);
            if (area > 800) {
                detectObjects.push_back(cv::boundingRect(contour));
            }
        }

    double motion = (double)cv::countNonZero(thresh);

    previouslyFrame = grayScale.clone();
    return motion;
}

void VisionEngineSystem::detectFaces(cv::Mat frame) {
    faceObjects.clear();
    cv::Mat grayScale;
    cv::cvtColor(frame, grayScale, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(grayScale, grayScale);
    faceCascade.detectMultiScale(grayScale, faceObjects, 1.1, 3, 0, cv::Size(30, 30));
}