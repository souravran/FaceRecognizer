# FaceRecognizer

Face Recognition - a machine learning way
=========================================
:Author: Sourav Senapati
-----------------------------------------

### What is about?
Facial Recognition sucks. But its getting better. This isa trivial toy project to learn how good Facial Recognition is.

Currently, the work is on face recognition but soon, I will be updating the code base for face, gender detection and cool face tracking.

### Compile 

This is a CMake project. CMake takes a CMakeList file, and outputs to a platform-specific build format. If in Linux system, create a build directory, preferably parallel to source directory (src) and go to the buld directory. To achieve that, open a terminal and type the following command:

```sh
$ mkdir build_x86-64
$ cd build_x86-64
```
Then run cmake and point to the source directory. Type the followiing command:
```sh
$ cmake ../src
```
And finally run make in the build directory to generate the executables, the executables are found under application folder. Type with the following command:
```sh
$ make
```
ECLIPSE EDITOR : If Eclipse is your favorite editor, then a small script is being provided for making an Eclipse build project. Run the following command in the source folder while providing the arguments:
```sh
$ ./mk-eclipse-build-project.sh SRC_DIR BUILD_DIR BUILD_TYPE
```
### Run

To run the application, open a terminal, go to the build directory and type the follwing:
```sh
$ ./application/FaceRecognizerApp
```
The results are shown on the terminal console.

### Document generation

Support for Doxygen document generation system has been supplied with the project. A CMake file is
provided that generates required config file in the build directory. After successfully building the project, open a terminal, go to the build directory and type:
```sh
$ doxygen Doxyfile
```
This generates Doxygen docuementation inside doxygen folder for the current project. The document generation is both in HTML and Latex. In case the doxygen doc is not required, please comment out the follwing line in 
CMakeLists.txt file unders source folder:

include(cmake/doxygen.cmake)

