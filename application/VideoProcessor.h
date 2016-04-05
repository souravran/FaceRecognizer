/*
 * VideoProcessor.h
 *
 *  Created on: Dec 3, 2015
 *      Author: sourav
 */

#ifndef __APPLICATION_VIDEOPROCESSOR_H_
#define __APPLICATION_VIDEOPROCESSOR_H_
//-------------------------------------------------------------------------------------------------
// Project Includes
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Global Includes
//-------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>

namespace facerecognition {

#define KNOWN_PERSON_NAME           "SOURAV"
#define UNKNOWN_PERSON_NAME         "UNKNOWN"

class VideoProcessor {
public:
    VideoProcessor();
    virtual ~VideoProcessor();

    bool SuccessVideoCapture();
    bool SuccessVideoCapOriginal();
    // method used for detecting the input faces and to display meta data like, frames and number of faces
    int FaceDetection(std::string& pClassifierPath);
};

} /* namespace facerecognition */

#endif /* __APPLICATION_VIDEOPROCESSOR_H_ */
