/*
 * RecognizerApp.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: sourav
 */
//-------------------------------------------------------------------------------------------------
// Project Includes
//-------------------------------------------------------------------------------------------------
#include <application/RecognizerApp.h>
#include <application/VideoProcessor.h>
#include <application/ImageProcessor.h>
#include <application/FisherFaceTrainer.h>

//-------------------------------------------------------------------------------------------------
// Global Includes
//-------------------------------------------------------------------------------------------------

namespace facerecognition {
using namespace cv;

RecognizerApp::RecognizerApp()
: mFisherFaceTrainer() {
}

RecognizerApp::~RecognizerApp() {}

void RecognizerApp::Run() {

    VideoProcessor	vidProcessor;
    ImageProcessor  imgProcessor;

    // creating a trainer from the interface class
    // its a good idea to have an interface class cause which gives consistency while implementing any other kind of trainer
    mFisherFaceTrainer = FisherFaceTrainer::Create();
    mFisherFaceTrainer->RunTrainer();
    mFisherFaceTrainer->FaceRecognition();

//    if (! imgProcessor.SuccessImageSmoothing()) {
//        std::cout<< "Error while processing image !" << std::endl;
//    }
    return;
}
} /* namespace facerecognition */

//-------------------------------------------------------------------------------------------------
// main
//-------------------------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
    // create the object and run the app
    facerecognition::RecognizerApp  app;
    app.Run();
    return 0;
}
