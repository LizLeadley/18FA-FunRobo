////////////////////////////////////////////////
//Title: Sense Arduino
//Description: Sense Slave Arduino, serially connected (w/ digital pins
////12,13) to Master Arduino Think. Connected to Sharp IRs on pins 0-4,
////see below for order. 
//Robot Name: TugBoat
//What does code do: Code will simple serial connect Sense Arduino
////to Think arduino (not act) sending data and recieving commands
//Hardware Warnings:
//Created by Team Pixy-Tug
////////////////////////////////////////////////


///////////////////////////////
//Libraries
///////////////////////////////
#include <SoftwareSerial.h>  //includes software serial library
#include <SPI.h>             // pixystuff
#include <Pixy.h>            // more pixystuff
#include <math.h>            // math library
///////////////////////////////

//Sets up Simple Serial communication
SoftwareSerial senseSerial(12, 13);     //connects sense arduino to think arduino using pins 12 & 13

// All the variables we need
Pixy pixy;                     // This is the main Pixy object
int xValue;                    // x value of the center of the box, seen by the Pixy Cam
int offsetDeg;                 // position in degrees with 0 degrees = straight
float ratio;                   // value used in the remap function
String newValue;               // return value used for round off function
String strValue;               // string used to make a 3 digit string of the angle
String angleStr;               // String of the angle to put in the string sent over serial
String serialStr;              // String to send serial data
unsigned long previousMillis = 0;
const int analogPin0 = 0;     // Left
String left;
const int analogPin1 = 1;     // Right
String right;
const int analogPin2 = 2;     // soft left
String softLeft;
const int analogPin3 = 3;     // soft right
String softRight;
const int analogPin4 = 4;     // Back
String back;
int j = 0;


void setup() {
  // put your setup code here, to run once:
  senseSerial.begin(19200);               //sets baud rate for sense to 19200
  //senseSerial has same name in think and sense arduinos
  pixy.init();                           // pixy initialization
  Serial.begin(9600);                    // starts separate serial with computer at 9600
  Serial.print("Starting...\n");

}

void loop() {
  // put your main code here, to run repeatedly:
  
  /////////////////////////////////////
  // Sensor code:
  ////////////////////////////////////
  
  // pixy code:

  unsigned long currentMillis = millis();  // Millis initialization
  static int i = 0;                        // Random pixy variables I don't know
  uint16_t blocks;                         // see pixy tutorial link in lab doc
  char buf[32];

  // grab blocks!
  blocks = pixy.getBlocks();

  // If there is an object (fish), search for the center of the block,
  if (blocks)
  {
    i++;
    // do this (print) every 10 frames because printing every
    // frame would bog down the Arduino
    if (i % 10 == 0)
    {
      xValue = pixy.blocks[0].x;                                    // get the x value of the center of the block
      offsetDeg = remapInterval(xValue, 0, 319, -37.5, 37.5);       // remap x value to degrees
      previousMillis = currentMillis;                               // storing last time it saw a block
    }
  }
  else if (currentMillis - previousMillis > 500)                    // if it hasn't seen a block for a longer time (300 ms), it gives a value (999)
  {
    offsetDeg = 99;    
  }
  angleStr = makeString(offsetDeg);
  
  // Sharp IR's code
  
  left = roundOff(valToDist(analogRead(analogPin0)));               // reading the analogpin, convert to distance and round off to interval between [15,99]
  right = roundOff(valToDist(analogRead(analogPin1)));              // distances are in centimeters
  softLeft = roundOff(valToDist(analogRead(analogPin2)));
  softRight = roundOff(valToDist(analogRead(analogPin3)));          
  back = roundOff(valToDist(analogRead(analogPin4))); 
  
  serialStr =  angleStr + left + softLeft + softRight + right + back;   // Putting together the string to send through serial
  Serial.println(serialStr);                                            // See in serial what's it sending through

  
  
  ////////////////////////////////////////
  //Basic softSerial Code
  ////////////////////////////////////////

  senseSerial.println(serialStr);
  //Prints data to the transmit pin of the Sense software serial port
  //###Note: This never worked, so maybe there is a better way?
  ////////////////////////////////////////

}


/////////////////////////////////////////////////////
//Functions
/////////////////////////////////////////////////////

// Remap function between two intervals
//###Note: Actually there is a built-in function in arduino that also does this for you ('map')
float remapInterval(float value, float int1_start, float int1_end, float int2_start, float int2_end)
{
  ratio = (value - int1_start) / (int1_end - int1_start); //Convert the value into a ratio out of the initial total interval size
  return (int2_start + ratio * (int2_end - int2_start));  //Add the start value of the second interval, to the ratio mapped onto the new total interval size
}

// IR reading to cm function
int valToDist(int val)
{
  return pow((3027.4 / val), 1.2134);           //Uses the math library's function pow (power, as in exponents)
}

// Function rounding of value to [15,99] and make a 2 digit string
String roundOff(int val)
{
  if (val > 99)       // if the value is greater than 99, truncate it to exactly 99
  {
    newValue = "99";
  }
  else if (val < 15)  // if the value is less than 15, set it to 00 to be ignored
  {
    newValue = "00";
  }
  else                // if the value is within range, make it a string for serial handling
  {
    newValue = String(val);
  }
  return newValue;
}

// Function making a 3-digit string of the angle value, with the first digit (0,1) = (-,+) respectively
// ### Note: We first tried to first make a string and check if the first char was "-", which it didn't want to do for some reason.
    // That's why we make a string in both if-statements.
String makeString(int val)
{
  if (val < 0)                      // Turns the - into 0
  {
    strValue = String(val);
    strValue.replace('-','0');
  }
  else                              // adds a 1 in front of number (if positive)
  {
    strValue = String(val);
    strValue = "1"+strValue;
  }
  if (strValue.length() < 3)        // adds zeroes if the number is too short
  {
    strValue = strValue.substring(0,1) + "0" + strValue.substring(1);
  }
  return strValue;
}
