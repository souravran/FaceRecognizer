/*
 * ISystemTrainer.h
 *
 *  Created on: Dec 3, 2015
 *      Author: sourav
 */

#ifndef __APPLICATION_ISYSTEMTRAINER_H_
#define __APPLICATION_ISYSTEMTRAINER_H_
//-------------------------------------------------------------------------------------------------
// Project Includes
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Global Includes
//-------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <memory>
#include <iostream>
#include <string>

namespace facerecognition {
using namespace cv;
/*! An interface class for a trainer for face recognition
 *
 */
#define IMAGE_STORE_FILE            "data/image_store.txt"
#define IMAGE_TRAIN_MODEL_FILE      "data/trainer.yml"
#define IMAGE_SAMPLE_FILE           "data/0.jpg"

#define KNOWN_PERSON_NAME           "SOURAV"
#define UNKNOWN_PERSON_NAME         "UNKNOWN"

class ISystemTrainer {
public:
    typedef std::shared_ptr<ISystemTrainer> Ptr;

    virtual ~ISystemTrainer() {}
    virtual void RunTrainer() = 0;
    virtual void ReadRecordStore(const std::string& pImagesStoreFilePath, std::vector<Mat>& pImageStore, std::vector<int>& pLabels, char pSeparator = ';') = 0;
    virtual int FaceRecognition() = 0;
};
} /* namespace facerecognition */

#endif /* __APPLICATION_ISYSTEMTRAINER_H_ */
