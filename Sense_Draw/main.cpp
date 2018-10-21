/*
 * Draw lines and shapes on a blank background and display the result
 * Uses openCV
 * Commented by Liz
 * Ripped from tutorial website:
 * https://docs.opencv.org/3.4/db/df5/tutorial_linux_gcc_cmake.html
 */

#include <stdio.h> //include standard library
#include <opencv2/opencv.hpp> //include opencv files

using namespace cv; //we will talk in cv functions.
using namespace std; //we will also talk in std functions
//this avoids having to preface with std:: or cv::

//Practice defining some things
// Point pt1;
// pt1.x = 10;
// pt1.y = 8;
//
// Point pt2 = Point(20,16);
//
// //Define color (in B,G,R order, for whatever reason)
// Scalar cyan = Scalar(255, 255, 0);

int w = 500;

//Declare some functions
//These are basically fancy ways of calling built-in opencv functions with a few presets
//See below definitions for more details on how to call the built-ins
void drawLine(Mat img, Point start, Point end);
void drawEllipse(Mat img, double angle);
void drawCircle(Mat img, Point center);
//void drawPoly();


int main()
{

    char atom_window[] = "Drawing1: an Atom";

    Mat atom = Mat::zeros( w, w, CV_8UC3 ); //Creates a matrix called atom
    //make it w by w pixels, and fill with all black (unless zeros means transparent)

//Draw the atom
    //Ellipses for electron orbits, and a circle for the nucleus
    drawEllipse(atom, 90);
    drawEllipse(atom, 0);
    drawEllipse(atom, 45);
    drawEllipse(atom, -45);
    drawCircle(atom, Point(w/2.0, w/2.0));

    //Create a named window. Name it Atom, and give it an automatic size
    //Automatic size seems to detect the image file's size and using that
    namedWindow("Atom", WINDOW_AUTOSIZE );
    //shows an image, in the window named Atom, and referencing our Image object from earlier
    imshow("Atom", atom);

    //waits x milliseconds before moving on (most common in video loops)
    //zero is an infinite, immediate loop, used for single images
    //this is how to affect slow-mo
    waitKey(0);
    return 0;
}


//------------------------Functions---------------------
//This really isn't how I would go about it; unless you need something specific,
//just call the default functions directly.
//This is just whatever I found online as practice

void drawLine(Mat img, Point start, Point end)
{
  int thickness = 2;
  int lineType = 8;
  line(img, start, end,
        Scalar(0,0,0), thickness, lineType);
    //Line args: image to draw on (cv::Mat type object); start point (a tuple or Point),
      //end point (again, tuple or Point), color, which is that Scalar(B,G,R),
      //optional line thickness (use -1 for filled in), and line Type (not sure what that one does, probably has dotted options)
}
void drawEllipse(Mat img, double angle)
{
  int thickness = 2;
  int lineType = 8;
  ellipse(img, Point(w/2.0, w/2.0), Size(w/4.0, w/16.0), angle,
        0, 360, Scalar(255, 0, 0), thickness, lineType);
        //Ellipse args: image to draw on (cv::Mat type object); center point (a tuple or Point);
          //Size, which is a tuple for major and minor axes; angle to rotate ellipse by (didn't determine which is 0deg)
          //two more angles for how much of the ellipse arc to draw; color, which is that Scalar(B,G,R);
          //optional line thickness (use -1 for filled in), and line Type (not sure what that one does, probably has dotted options)
}
void drawCircle(Mat img, Point center)
{
  int thickness = -1;
  int lineType = 8;
  circle(img, center, w/32.0, Scalar(0, 0, 255), thickness, lineType);
  //Circle args: image to draw on (cv::Mat type object); center point (a tuple or Point);
    //Size, an integer; color, which is that Scalar(B,G,R);
    //optional line thickness (use -1 for filled in), and line Type (not sure what that one does, probably has dotted options)
}
