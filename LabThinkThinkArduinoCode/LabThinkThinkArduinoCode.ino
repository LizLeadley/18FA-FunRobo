////////////////////////////////////////////////
//Title: Think Arduino
//Description: Master Arduino, Serially connected (w/ digital 
////pins 10,11,12,13) to 2 slave Arduinos, Sense and Act, 
////Runs Gaussian Arbiter.
//Robot Name?: Boat?
//What does code do: Code will simple serial connect Think Arduino
////with Act and Sense Arduino, reading and writing commands and 
////deciding on best course of action using Gaussian Arbiter
//Software Warnings: Software Serial Library can't send and recieve
////data at the same time, or continuously transmit between mult.
////serial connections. One at a time. Alternative library is
////AltSoftSerial library (has dif weaknesses) if this doesn't 
////work, I2C uses analog pins to communicate but is more difficult 
////to use.
//Other info: For more SoftSerial fn's go to https://www.arduino.cc/en/Reference/SoftwareSerial
//Created by Team Think 
////////////////////////////////////////////////

///////////////////////////////
//Libraries
///////////////////////////////
#include <SoftwareSerial.h> //includes software serial library

//Sets up Simple Serial communication
SoftwareSerial actSerial(10,11);    //connects arduino to act arduino using pins 10 & 11
SoftwareSerial senseSerial(12,13);  //connects arduino to sense arduino using pins 12 & 13

////////////////////////////////
//Global Variables
///////////////////////////////
String data = "";   //initializes data string
String propSpeed = "135"; //half speed forward
String angle = "000"


void setup() {
  // put your setup code here, to run once:
  softSerial.begin(9600);  //opens/starts (soft) serial communication to computer
  actSerial.begin(9600);   //sets baud rate for act
  senseSerial.begin(9600); //and sense to 9600, matches softSerial
}

void loop() {
  // put your main code here, to run repeatedly:

  //////////////////////////////////////////////////////////////////////////////////////
  //Very Basic Think Code Following
  //////////////////////////////////////////////////////////////////////////////////////
  //Think Arduino will receive from sense, decide what to do, then send to act. It will also send updates and recieve commands from comp.
  //TODO: Do we know if the xbee uses the normal serial to communicate or something else------------------------------
  
  //take data from sense arduino (probably active)
  //Sense arduino is sending and angle from the pixy, and 5 distances from the IR sensors
  if (senseSerial.available()>0)
  {
    data = "";
    while (data.length() < 13)
    {
      char c = senseSerial.read();//reads c to check if it's n or not
       while (char c != 'n')  //stops reading c at null character at null character
       {
         c = senseSerial.read(); //if c = #, reads each number
         data = data + c;  //new data str = old data + character c
         //data.concat(c); //adds each number to string
       }
    }
  }

  pixy = parsePixy(data);  //returns angle 
  leftCenterIR = parseLCIR(data);  //returns distance LCIR
  rightCenterIR = parseRCIR(data);  //returns distance RCIR
  leftIR = parseLIR(data);   //returns distance LIR
  rightIR = parseRIR(data);  //returns distance RIR
  backIR = parseBIR(data);   //returns distance BIR
  
  if (leftCenterIR == "000") //if the 3 characters that represent LCIR == "000",LCIR is detecting distance less than 15
  {
    propSpeed = "090";  //0 speed
  }
  if (rightCenterIR == "000")
  {
    propSpeed = "090";  //0 speed
  }
  if (leftIR == "000")
  {
    propSpeed = "090";  //0 speed
  }
  if (rightIR == "000")
  {
    propSpeed = "090";  //0 speed
  }
  if (backIR == "000")
  {
    propSpeed = "090";  //0 speed
  }
  else
  {
    propSpeed = "135";  //half speed forward
  }
  
  //send data to act arduino
  actSerial.print(angle);  //sends angle from pixy cam
  actSerial.print(propSpeed);  //sends speed to act
  actSerial.println('n');

  //////////////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////////////
  //Functions  //as in functions that aren't in libraries that need to be made//fewer = better
  //////////////////////////////////////////////////////////////////////////////////////
  String parsePixy(String data)  //if you want to return in change 1st word String to int
  {
    //String pixySign = data.substring(0,0);  //first character (0,0) determines if angle is positive or negative
    String pixyAngle = data.substring(0,2);  //next 2 characters (1,2) determine angle
    //make strings to integers
    //sign = pixySign.toInt();//if 0 sign is -, if 1 sign is +
    //angle = pixyAngle.toInt(); //if you want to return int use this line
    return angle;
  }
  String parseLCIR(String data) //if you want to return in change 1st word String to int
  {
    String strLCIR = data.substring(3,4);
    //LCIR = strLCIR.toInt();//if you want to return int use this line
    return LCIR;
  }
  String parseRCIR(String data)//if you want to return in change 1st word String to int
  {
    String strRCIR = data.substring(3,4);
    //RCIR = strRCIR.toInt(); //if you want to return int use this line
    return RCIR;
  }
  String parseLIR(String data)//if you want to return in change 1st word String to int
  {
    String strLIR = data.substring(3,4);
    //LIR = strLIR.toInt(); //if you want to return int use this line
    return LIR;
  }
  String parseRIR(String data)//if you want to return in change 1st word String to int
  {
    String strRIR = data.substring(3,4);
    //RIR = strRIR.toInt(); //if you want to return int use this line
    return RIR;
  }
  String parseBIR(String data)//if you want to return in change 1st word String to int
  {
    String strBIR = data.substring(3,4);
    //BIR = strBIR.toInt(); //if you want to return int use this line
    return BIR;
  }

  //////////////////////////////////////////////////////////////////////////////////////
}
