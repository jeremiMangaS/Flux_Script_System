#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>

class VisionEngineSystem {
    public : 
        VisionEngineSystem();
        ~VisionEngineSystem();
        bool openCamera(int index = 0);
        bool isWindowOpen();
        void showFrame(const std::string& windowName, cv::Mat frame);
        cv::Mat getNextFrame();
    private :
        cv::VideoCapture vidCapture;
};