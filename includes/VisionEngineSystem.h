#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>

class VisionEngineSystem {
    public : 
        VisionEngineSystem();
        ~VisionEngineSystem();
        double getMotion(cv::Mat currentFrame);
        bool openCamera(int index = 0);
        bool isWindowOpen();
        void showFrame(const std::string& windowName, cv::Mat frame);
        cv::Mat getNextFrame();
        // cv::Rect getLastDetection() {return  lastDetection;}
        std::vector<cv::Rect> getDetectObjects() {return detectObjects;}
    private :
        cv::VideoCapture vidCapture;
        cv::Mat previouslyFrame;
        // cv::Rect lastDetection = cv::Rect(0,0,0,0);
        std::vector<cv::Rect> detectObjects;
};