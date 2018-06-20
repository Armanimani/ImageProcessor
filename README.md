# ImageProcessor
A simple program for processing image files written using png++ library

# Features
The following features has been added to the code
1) Removing the background of the image by setting its alpha value to 1 (The color of background is provided by the user and a tolerance need to be specified). This is done using union-find algorithm to solve connectivity of colors
2) Fitting the image to the screen

# usage
* png++ library is required that can be installed using https://www.nongnu.org/pngpp/doc/0.2.1/
* The header file `ImageProcessor.hpp` need to be included in a file to create an object of `ImageProcessor` type

# example
The following example is included in the package and can be invoked by `make all run` command
## Note: Output of this test is available inside `test` folder
