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
  //argc always tracks the number of arguments given when running a c++ program
  //with arguments (ie from terminal)
  //argv is the vector of char arguments given, e.g. [./programName, fileName]
  //for something like this calling a file.
  //0th index will be the function being called, and the next will be the
  //additional arguments passed, in this case the video file.
  //(these can be renamed)

   //If the user passes more arguments than the function name and file name,
   //print out to them the proper calling syntax
    if ( argc != 2 )
    {
      //If it's called wrong,
      //Tells user how function is supposed to be called
        std::cout << "Call using: OpenCVImageDisplay.out <Image_File_Path>\n";
        return -1;
    }

    Mat image; //Creates a matrix called image
    //Calling argv[1], which is the image file
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
