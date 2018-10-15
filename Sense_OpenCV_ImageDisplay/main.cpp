/*
 * Display an Image file, similar to the built-in eog function, in a new window
 * Uses openCV
 * Commented by Liz
 * Ripped from tutorial website:
 * https://docs.opencv.org/3.4/db/df5/tutorial_linux_gcc_cmake.html
 */

#include <stdio.h> //include standard library
#include <opencv2/opencv.hpp> //include opencv files

using namespace cv; //we will talk in cv functions.
            // this will mean common funs like cout will require std::

int main(int argc, char** argv )
{
    if ( argc != 2 ) //argc looks to be some sort of control flag?
    {
      //Tells user how function is supposed to be called
        printf("usage: DisplayImage.out <Image_Path>\n");
        std::cout << "Use as: OpenCVImageDisplay.out <Image_Path>\n";
        return -1;
    }

    Mat image; //Creates a matrix called image
    image = imread( argv[1], 1 ); //built-in imread funciton populates image object

    //in case there's no data in the image, don't display it, and tell us so.
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    //Create a named window. Name it Display image, and give it an automatic size
    //Automatic size seems to detect the image file's size and using that
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    //shows an image, named Display Image, and referencing our Image object from earlier
    imshow("Display Image", image);
    //waits x milliseconds before moving on (most common in video loops)
    //zero is an infinite, immediate loop.; this is how to affect slow-mo
    waitKey(0);
    return 0;
}
