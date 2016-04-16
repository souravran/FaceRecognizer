/*
 * VideoProcessor.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: sourav
 */
//-------------------------------------------------------------------------------------------------
// Project Includes
//-------------------------------------------------------------------------------------------------
#include <application/VideoProcessor.h>

//-------------------------------------------------------------------------------------------------
// Global Includes
//-------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>

namespace facerecognition {
using namespace cv;

VideoProcessor::VideoProcessor() {}

VideoProcessor::~VideoProcessor() {}

bool VideoProcessor::SuccessVideoCapture() {
    VideoCapture startVideoCap(0);
    if (!startVideoCap.isOpened()) {
        std::cout << " Error occurred while starting the video capture" << std::endl;
        return false;
    }
    Mat capturedImageEdges;
    namedWindow("Test Capture", 1);
    for (;;) {
        Mat capturedImageFrame;
        startVideoCap >> capturedImageFrame;
        if (!capturedImageFrame.empty()) {
            cvtColor(capturedImageFrame, capturedImageEdges, CV_HLS2BGR);
            GaussianBlur(capturedImageEdges, capturedImageEdges, Size(7, 7), 1.5, 1.5);
            Canny(capturedImageEdges, capturedImageEdges, 0, 30, 3);
            imshow("Test Capture", capturedImageEdges);
        }
        if (waitKey(30) == 10) break;
    }
    return true;
}

bool VideoProcessor::SuccessVideoCapOriginal() {
    VideoCapture startVideoCap(0);
    if (!startVideoCap.isOpened()) {
        std::cout << " Error occurred while starting the video capture" << std::endl;
        return false;
    }
    namedWindow("Face Recognizer", 1);
    while (true) {
        // now read each frame and assign to the image matrix
        Mat initialImageFrame;
        startVideoCap.read(initialImageFrame);
        if (!initialImageFrame.empty()){
            imshow("Face Recognizer", initialImageFrame);
        }
        if (waitKey(30) >= 0) break;
    }
    return 0;
}

int VideoProcessor::FaceDetection(std::string& pClassifierPath){
    CascadeClassifier availableFaceCascade;
    std::string window = "Face Recognition";

    if (!availableFaceCascade.load(pClassifierPath)){
        std::cout << "Error occurred while loading the available cascade file" << std::endl;
        return -1;
    }

    VideoCapture startVideoCap(0);
    if (!startVideoCap.isOpened()) {
        std::cout << "exit" << std::endl;
        return -1;
    }
    namedWindow(window, 1);
    long framesCounter = 0;
    string personName = KNOWN_PERSON_NAME;
    while (true) {
        std::vector<Rect> inputFacesStore;
        Mat inputImageFrame;
        Mat greyIamgeSacleFrame;
        Mat imageRegionOfInterest;

        startVideoCap >> inputImageFrame;
        framesCounter = framesCounter + 1;
        if (!inputImageFrame.empty()){
            availableFaceCascade.detectMultiScale(inputImageFrame, inputFacesStore, 1.1, 3, 0, cv::Size(190, 190), cv::Size(200, 200));
            std::cout << inputFacesStore.size() << " The input face is detected !" << std::endl;
            std::string holdFrameSet = std::to_string(framesCounter);
            std::string holdFacesSet = std::to_string(inputFacesStore.size());
            int width = 0;
            int height = 0;
            cv::Rect localRegionOfInterest;
            for (int i = 0; i < inputFacesStore.size(); i++) {
                rectangle(inputImageFrame, Point(inputFacesStore[i].x, inputFacesStore[i].y), Point(inputFacesStore[i].x + inputFacesStore[i].width, inputFacesStore[i].y + inputFacesStore[i].height), Scalar(255, 0, 255), 1, 8, 0);
                std::cout << inputFacesStore[i].width << inputFacesStore[i].height << std::endl;
                width = inputFacesStore[i].width; height = inputFacesStore[i].height;
                localRegionOfInterest.x = inputFacesStore[i].x; localRegionOfInterest.width = inputFacesStore[i].width;
                localRegionOfInterest.y = inputFacesStore[i].y; localRegionOfInterest.height = inputFacesStore[i].height;
                imageRegionOfInterest = inputImageFrame(localRegionOfInterest);
            }
            std::string outputWidth = std::to_string(width);
            std::string outputHeight = std::to_string(height);
            cv::putText(inputImageFrame, "Frames: " + holdFrameSet, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
            cv::putText(inputImageFrame, "Faces Detected: " + holdFacesSet, cvPoint(30, 60), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
            cv::putText(inputImageFrame, "Resolution: " + outputWidth + " x " + outputHeight, cvPoint(30, 90), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
            cv::imshow(window, inputImageFrame);
        }
        if (waitKey(30) >= 0) break;
    }
}
} /* namespace facerecognition */
