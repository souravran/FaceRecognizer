/*
 * FisherFaceTrainer.h
 *
 *  Created on: Dec 3, 2015
 *      Author: sourav
 */

#ifndef __APPLICATION_FISHERFACETRAINER_H_
#define __APPLICATION_FISHERFACETRAINER_H_
//-------------------------------------------------------------------------------------------------
// Project Includes
//-------------------------------------------------------------------------------------------------
#include <application/ISystemTrainer.h>

//-------------------------------------------------------------------------------------------------
// Global Includes
//-------------------------------------------------------------------------------------------------
#include <fstream>
#include <sstream>

namespace facerecognition {

class FisherFaceTrainer: public ISystemTrainer {
public:
 typedef std::shared_ptr<FisherFaceTrainer> Ptr;

 static Ptr Create();
 virtual ~FisherFaceTrainer();

 virtual void RunTrainer();
 virtual void ReadRecordStore(const std::string& pImagesStoreFilePath, std::vector<Mat>& pImageStore, std::vector<int>& pLabels, char pSeparator = ';');
 virtual int FaceRecognition();

 Mat GetNormalizedImage(InputArray pImageSource);
 void RunLocalBinaryPatternsHistograTrainer();

protected:
 explicit FisherFaceTrainer();
};

} /* namespace facerecognition */

#endif /* __APPLICATION_FISHERFACETRAINER_H_ */
