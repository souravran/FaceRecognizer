/*
 * RecognizerApp.h
 *
 *  Created on: Dec 3, 2015
 *      Author: sourav
 */

#ifndef __APPLICATION_RECOGNIZERAPP_H_
#define __APPLICATION_RECOGNIZERAPP_H_
//-------------------------------------------------------------------------------------------------
// Project Includes
//-------------------------------------------------------------------------------------------------
#include <application/ISystemTrainer.h>

//-------------------------------------------------------------------------------------------------
// Global Includes
//-------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

namespace facerecognition {

class RecognizerApp {
public:
    RecognizerApp();
    virtual ~RecognizerApp();
    void Run();

private:
    ISystemTrainer::Ptr mFisherFaceTrainer;
};
} /* namespace facerecognition */

#endif /* __APPLICATION_RECOGNIZERAPP_H_ */
