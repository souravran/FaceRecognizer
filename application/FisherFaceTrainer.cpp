/*
 * FisherFaceTrainer.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: sourav
 */
//-------------------------------------------------------------------------------------------------
// Project Includes
//-------------------------------------------------------------------------------------------------
#include <application/FisherFaceTrainer.h>

//-------------------------------------------------------------------------------------------------
// Global Includes
//-------------------------------------------------------------------------------------------------

namespace facerecognition {

FisherFaceTrainer::Ptr FisherFaceTrainer::Create() {
    FisherFaceTrainer::Ptr retVal = FisherFaceTrainer::Ptr(new FisherFaceTrainer());
    return retVal;
}

FisherFaceTrainer::FisherFaceTrainer() {
}

FisherFaceTrainer::~FisherFaceTrainer() {
}

void FisherFaceTrainer::RunTrainer() {

    // the vectors for holding the list of training images and corresponding labels
    std::vector<Mat> imagesList;
    std::vector<int> labelsList;
    try{
        std::string filenameImageStore = IMAGE_STORE_FILE;
        ReadRecordStore(filenameImageStore, imagesList, labelsList);
        std::cout << "Number of stored images for training : " << imagesList.size() << std::endl;
        std::cout << "Number of labels for training : " << labelsList.size() << std::endl;
        std::cout <<std::endl << "Starting the training process ..." << std::endl;
    }
    catch (cv::Exception& e){
        std::cerr << "Error occurred while opening the file " << e.msg << std::endl;
        exit(1);
    }
    cv::Ptr<cv::FaceRecognizer> trainModel = cv::createFisherFaceRecognizer();
    trainModel->train(imagesList, labelsList);
    int height = imagesList[0].rows;
    trainModel->save(IMAGE_TRAIN_MODEL_FILE);
    std::cout <<std::endl << "Finishing the training process ..." << std::endl;

    // the way to get matrix for the Eigen values
    Mat matrixEigenValues = trainModel->getMat("eigenvalues");
    // the way to get matrix for the Eigen vectors
    Mat matrixEigenVectors = trainModel->getMat("eigenvectors");
    // the way to get mean from the trained model
    Mat mean = trainModel->getMat("mean");
    waitKey(10000);
}

void FisherFaceTrainer::RunLocalBinaryPatternsHistograTrainer() {
    // the vectors for holding the list of training images and corresponding labels
    std::vector<Mat> imagesList;
    std::vector<int> labelsList;
    try{
        std::string filenameImageStore = IMAGE_STORE_FILE;
        ReadRecordStore(filenameImageStore, imagesList, labelsList);
        std::cout << "Number of stored images for training : " << imagesList.size() << std::endl;
        std::cout << "Number of labels for training : " << labelsList.size() << std::endl;
        std::cout <<std::endl << "Starting the training process ..." << std::endl;
    }
    catch (cv::Exception& e){
        std::cerr << "Error occurred while opening the file " << e.msg << std::endl;
        exit(1);
    }

    //lbph face recognier model
    cv::Ptr<cv::FaceRecognizer> trainModel = cv::createLBPHFaceRecognizer();
    trainModel->train(imagesList, labelsList);
    int height = imagesList[0].rows;
    trainModel->save(IMAGE_TRAIN_MODEL_FILE);
    std::cout <<std::endl << "Finishing the training process ..." << std::endl;
    waitKey(10000);
}

void FisherFaceTrainer::ReadRecordStore(const std::string& pImagesStoreFilePath, std::vector<Mat>& pImageStore, std::vector<int>& pLabels, char pSeparator) {
    std::ifstream file(pImagesStoreFilePath.c_str(), std::ifstream::in);
    if (!file){
        std::string error = "no valid input file";
        CV_Error(CV_StsBadArg, error);
    }
    std::string line, path, label;
    while (getline(file, line)) {
        std::stringstream liness(line);
        getline(liness, path, pSeparator);
        getline(liness, label);
        if (!path.empty() && !label.empty()){
            pImageStore.push_back(imread(path, 0));
            pLabels.push_back(atoi(label.c_str()));
        }
    }
}

Mat FisherFaceTrainer::GetNormalizedImage(InputArray pImageSource) {
    // this is how the images are created and normalized
    Mat imageSrcNormalized = pImageSource.getMat();
    Mat imageDestiNormalized;
    switch (imageSrcNormalized.channels()) {
    case 1:
        cv::normalize(pImageSource, imageDestiNormalized, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(pImageSource, imageDestiNormalized, 0, 255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        imageSrcNormalized.copyTo(imageDestiNormalized);
        break;
    }
    return imageDestiNormalized;
}

int  FisherFaceTrainer::FaceRecognition(){
    std::cout << "Starting face recognition process ..." << std::endl;

    // here we load a trained model and the provide a same image file
    cv::Ptr<cv::FaceRecognizer>  model = cv::createFisherFaceRecognizer();
    model->load(IMAGE_TRAIN_MODEL_FILE);
    Mat sampleImage = imread(IMAGE_SAMPLE_FILE, 0);

    int setImagemgWidth = sampleImage.cols;
    int setImageHeight = sampleImage.rows;
    // this is how we use the provided classifier, this path is set under Ubuntu 15.04 system
    std::string classifierSystemPath = "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml";

    CascadeClassifier availableFaceCascade;
    std::string capturingWindow = "Face Recognition";
    if (!availableFaceCascade.load(classifierSystemPath)) {
        std::cout << "Error occurred while loading file" << std::endl;
        return -1;
    }

    VideoCapture setVideoCapture(0);
    if (!setVideoCapture.isOpened()) {
        std::cout << "exit" << std::endl;
        return -1;
    }
    // start a new window
    namedWindow(capturingWindow, 1);
    long frameCounter = 0;

    while (true) {
        std::vector<Rect> inputFacesStream;
        Mat outputFrame;
        Mat graySacleFrame;
        Mat originalFrame;

        setVideoCapture >> outputFrame;
        frameCounter = frameCounter + 1;
        if (!outputFrame.empty()) {
            originalFrame = outputFrame.clone();
            // transferring images to grey scale and equalize the images
            cvtColor(originalFrame, graySacleFrame, CV_BGR2GRAY);
            // detect the face in gray image
            availableFaceCascade.detectMultiScale(graySacleFrame, inputFacesStream, 1.1, 3, 0, cv::Size(90, 90));
            // number of faces detected
            std::cout << inputFacesStream.size() << "Face Detected" << std::endl;
            std::string frameset = std::to_string(frameCounter);
            std::string faceset = std::to_string(inputFacesStream.size());

            int width = 0, height = 0;
            // person name
            std::string personName = "";
            for (int i = 0; i < inputFacesStream.size(); i++) {
                // region of interest
                Rect regionOfInterestForFace = inputFacesStream[i];
                //crop the region of interest from grey image
                Mat processedFaceImage = graySacleFrame(regionOfInterestForFace);
                // resizing the cropped image to suit to stored images sizes
                Mat resizedFaceImage;
                cv::resize(processedFaceImage, resizedFaceImage, Size(setImagemgWidth, setImageHeight), 1.0, 1.0, INTER_CUBIC);
                // finally, set to recognize the faces detected from the stream
                int obtainedLabelValue = -1;
                double obtainedConfidenceValue = 0;
                model->predict(resizedFaceImage, obtainedLabelValue, obtainedConfidenceValue);
                std::cout << " The Confidence : " << obtainedConfidenceValue << " Label :" << obtainedLabelValue << std::endl;
                // now, just draw a cool green rectangular frame while recognizing the face
                rectangle(originalFrame, regionOfInterestForFace, CV_RGB(0, 255, 0), 1);
                std::string text = " Recognized ";
                if (obtainedLabelValue == 1) {
                    personName = KNOWN_PERSON_NAME;
                }
                else {
                     personName = UNKNOWN_PERSON_NAME;
                }
                int posXCoord = std::max(regionOfInterestForFace.tl().x - 10, 0);
                int posYCoord = std::max(regionOfInterestForFace.tl().y - 10, 0);
                // set the name of the person who got recognized in the frame
                putText(originalFrame, text, Point(posXCoord, posYCoord), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0, 255, 0), 1.0);
            }
            putText(originalFrame, "Frames: " + frameset, Point(30, 60), CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0, 255, 0), 1.0);
            putText(originalFrame, "Person: " + personName, Point(30, 90), CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0, 255, 0), 1.0);
            // okay, now we display to the window frame
            cv::imshow(capturingWindow, originalFrame);
        }
        if (waitKey(30) >= 0) break;
    }
}
} /* namespace facerecognition */
