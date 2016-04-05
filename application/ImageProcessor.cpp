/*
 * ImageProcessor.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: sourav
 */
//-------------------------------------------------------------------------------------------------
// Project Includes
//-------------------------------------------------------------------------------------------------
#include <application/ImageProcessor.h>

//-------------------------------------------------------------------------------------------------
// Global Includes
//-------------------------------------------------------------------------------------------------

#define IMAGE_SAMPLE_FILE           "data/0.jpg"

namespace facerecognition {
using namespace cv;

ImageProcessor::ImageProcessor() {
}

ImageProcessor::~ImageProcessor() {
}

bool ImageProcessor::SuccessImageSmoothing() {
    Mat inputImage, outputImage;
    inputImage = imread(IMAGE_SAMPLE_FILE,1);
    if (inputImage.empty()){
        std::cout << "Error occurred while reading input image!" << std::endl;
        return false;
    }
    std::cout << "Input image resolution is : ["<< inputImage.cols << " X " << inputImage.rows <<"]"<< std::endl;
    namedWindow("Source", 1);
    imshow("Source", inputImage);

    for (int i = 1; i < 5; i++) {
        std::string value = std::to_string(i);
        std::string name = value + " x " + value;
        blur(inputImage, outputImage, Size(i, i), Point(-1, -1), 4);
        namedWindow(name,1);
        imshow(name, outputImage);
    }
    waitKey(0);
    destroyAllWindows();
    return true;
}

int ImageProcessor::SuccessEdgeDetection(){
    VideoCapture initiateCapture;
    Mat originalImage, greyScaleImage, inputImageEdge, imageDetectEdges;
    vector<vector<Point> > contoursStore;
    vector<Vec4i> contoursHierarchy;
    RNG inputImageRing(12345);

    initiateCapture.open(0);
    if (!initiateCapture.isOpened()) {
        std::cout << " camera opened error" << std::endl;
        return -1;
    }
    namedWindow("Edge Detection", 1);
    while (true) {
        initiateCapture >> originalImage;

        if (!originalImage.empty()) {
            // convert image to gray scale
            cvtColor(originalImage, greyScaleImage, CV_BGR2GRAY);
            // blurring image
            blur(originalImage, inputImageEdge, Size(3, 3));
            // detecting edges using canny edge detection
            Canny(inputImageEdge, imageDetectEdges, 10, 100, 3, true);
            findContours(imageDetectEdges, contoursStore, contoursHierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
            Mat drawing = Mat::zeros(imageDetectEdges.size(), CV_8UC3);
            for (int i = 0; i< contoursStore.size(); i++) {
                drawContours(originalImage, contoursStore, i, Scalar(0, 0, 255), 1, 8, contoursHierarchy, 0, Point());
            }
            // now show the frames in window
            imshow("Edge Detection", originalImage);
        }
        if (waitKey(30) >= 0) break;
    }
}
} /* namespace facerecognition */
