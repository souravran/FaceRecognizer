#
# main
#------------------------------------------------------------
set(FaceRecognizer_SRCS
    RecognizerApp.cpp
    ImageProcessor.cpp
    VideoProcessor.cpp
    FisherFaceTrainer.cpp
)
add_executable(FaceRecognizerApp ${FaceRecognizer_SRCS})
target_link_libraries(FaceRecognizerApp ${OpenCV_LIBS})
#-------------------------------------------------------------------------------

#
# add directories
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
