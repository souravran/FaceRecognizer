/*
 * ImageProcessor.h
 *
 *  Created on: Dec 3, 2015
 *      Author: sourav
 */

#ifndef __APPLICATION_IMAGEPROCESSOR_H_
#define __APPLICATION_IMAGEPROCESSOR_H_
//-------------------------------------------------------------------------------------------------
// Project Includes
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Global Includes
//-------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

namespace facerecognition {

class ImageProcessor {
public:
    ImageProcessor();
    virtual ~ImageProcessor();

    bool SuccessImageSmoothing();
    int SuccessEdgeDetection();
};
} /* namespace facerecognition */

#endif /* __APPLICATION_IMAGEPROCESSOR_H_ */
