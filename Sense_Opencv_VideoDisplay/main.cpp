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


int main() //call on a file to be displayed
{

    VideoCapture cap("Spin.avi"); //Create videocapture object on a file
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
