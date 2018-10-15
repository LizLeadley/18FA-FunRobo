/*
 * Display an Image file, similar to the built-in eog function, in a new window
 * Uses openCV
 * Commented by Liz
 * Ripped from tutorial websites:
 * https://docs.opencv.org/3.4/db/df5/tutorial_linux_gcc_cmake.html
 * https://www.learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
 */

#include <stdio.h> //include standard library
#include <opencv2/opencv.hpp> //include opencv files
#include <iostream> //include input-output common stream

//we will talk in cv and standard functions both
using namespace cv;
using namespace std;

//call on a file to be displayed
int main(int argc, char** argv)
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
      //Tells user how function is supposed to be called
        cout << "Call with: VideoDisplay <Video_File_Path>\n";
        return -1;
    }


    // calls argv[1], which is the video file
    VideoCapture cap(argv[1]); //Create videocapture object on a file
    //to open camera instead of file, pass an integer, i.e. 0 for inbuilt webcam


    //Check if camera/file opened successfully
    //If it did not, say so and return -1
    if (!cap.isOpened())
    {
      cout << "Could not open video stream or file" << endl;
      return -1;
    }

    //Make an infinite loop to run the video constantly
    //consider using for(;;) to stop once the video runs out
    while(1)
    {
      Mat frame; //create matrix called frame
      cap >> frame; //give frame one frame from cap object

      //if there's nothing in the frame, stop.
      if (frame.empty())
        break;

      //Show the frame, and call it "Frame"
      imshow("Frame", frame);

      // set the waitKey to 25ms for a normal video; make this 0 for updating webcam
      //set an escape key, such that we can break the infinite loop
      char c=(char)waitKey(20);
      if (c==27) //If Esc is pressed (while active on the window), stop.
        break;

    }

//Once we're done, release the VideoCapture object and close all opened windows
cap.release();
destroyAllWindows;

return 0;
}
