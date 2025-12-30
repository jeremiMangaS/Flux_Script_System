#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>

class VisionEngineSystem {
    public :

        // Const - Desct
        VisionEngineSystem();
        ~VisionEngineSystem();

        double getMotion(cv::Mat currentFrame);
        bool openCamera(int index = 0);
        bool isWindowOpen();
        void showFrame(const std::string& windowName, cv::Mat frame);
        cv::Mat getNextFrame();
        // cv::Rect getLastDetection() {return  lastDetection;}
        std::vector<cv::Rect> getDetectObjects() {return detectObjects;}

        // Face Recognize
        void detectFaces(cv::Mat frame);
        std::vector<cv::Rect> getDetectedFaces() {return faceObjects;}

    private :

        cv::VideoCapture vidCapture;
        cv::Mat previouslyFrame;
        // cv::Rect lastDetection = cv::Rect(0,0,0,0);
        std::vector<cv::Rect> detectObjects;
        
        // Face Recognize
        cv::CascadeClassifier faceCascade, profileCascade, fullBodyCascade, upperBodyCascade;
        std::vector<cv::Rect> faceObjects;
};