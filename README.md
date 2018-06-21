# ImageProcessor
A simple program for processing image files written using png++ library

# Features
The following features have been added to the code so far...
1) Removing the background of the image by setting its alpha value to 1 (The color of background is provided by the user and a tolerance need to be specified). This is done using union-find algorithm to solve for the zone which has the most colors close to background. The background replacement background color can also be chosen.
2) Fitting the image to the screen (by finding the border of the image which its alpha is not zero)
3) Cropping image (The user has the full control over both the number of divisions and their individual length)

# usage
* png++ library is required for compilation. It can be installed by following steps on https://www.nongnu.org/pngpp/doc/0.2.1/
* The header file `ImageProcessor.hpp` need to be included in a file to create an object of `ImageProcessor` type.

# example
There are multiple tests included in the package. They can be invoked by `make all run` command
