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

void setup() {
  // put your setup code here, to run once:
  softSerial.begin(9600);  //opens/starts (soft) serial communication to computer
  actSerial.begin(9600);   //sets baud rate for act
  senseSerial.begin(9600); //and sense to 9600, matches softSerial
}

void loop() {
  // put your main code here, to run repeatedly:

  ////////////////////////////////////////////////////////////////////////////
  //Basic softSerial Loop Code Following
  ////////////////////////////////////////////////////////////////////////////
  if (actSerial.isListening()) //tests if port is actively listening
  {
   Serial.println("Act Arduino is listening!");
  }
  if (senseSerial.isListening()) //tests if port is actively listening
  {
   Serial.println("Sense Arduino is listening!");
  }
  
  if (actSerial.available()>0) //returns # of bytes/characters 
  //available for reading from actSerial port. this is data that 
  //arrived and was stored in the serial recieve buffer.
  {
    actSerial.read(); //reads data from act arduino and returns character read
    //Only one SoftwareSerial instance can receive incoming data at a time 
  }
  if (senseSerial.available()>0)
  {
    senseSerial.read();
  }
  
  Serial.println("Message to Computer"); //Prints data to serial port
  actSerial.println("Message to Act Arduino"); //Prints data to the transmit pin of the Act software serial port
  senseSerial.println("Message to Sense Arduino"); //Prints data to the transmit pin of the Sense software serial port

  actSerial.write("hello act");//Prints data to the transmit pin of the software serial port as raw bytes.
  senseSerial.write("hello sense");//Prints data to the transmit pin of the software serial port as raw bytes.
  //////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////
  //Very Basic Think Code Following
  //////////////////////////////////////////////////////////////////////////////////////
  //I think Think Arduino will tend to receive from sense and send to act. Both for computer
  //TODO: Do we know if the xbee uses the normal serial to communicate or something else------------------------------
  
  //take data from sense arduino (probably active)
  //Is sense sending pure data, sensor reading keywords, object map, direction, or other? Assuming key words----------
  if (senseSerial.available()>0)
  {
    //we could separate types of senses i.e. if sensors sensed fish, return F.MovementType, and if obstacle return O.MovementType
    //then say c = senseSerial.read() and if c[index0] = I, do this, if O, do that, etc.
    SENSED = senseSerial.read();
  }
  
  //send data to sense arduino   (probably passive)
  //What data would need to be sent to sensors, initializing data? i.e. start sensing
  //write() transmits raw data through serial pin, print works same as Serial.print() fn, simply prints data to serial port
  senseSerial.write();
  senseSerial.println();

  //take data from act arduino   (probably passive)
  //What data do we need from act arduino? Confirmation of working?
  if (actSerial.available()>0)
  {
    //if motor moves -> confirm
    //when rudder moves -> print angle and direction travelled
    //when table moves -> print heading
    //what else is important?
  }
  
  //send data to act arduino     (probably active)
  if (Move = Forward) 
  {
    actSerial.println("Forward")  //act code can the specify what forward equates to in speed / other
  }
  if (Move = Backward) 
  {
    actSerial.println("Backward")
  }
  if (Rudder = Right) 
  {
    actSerial.println("Right")  //how to transmit rudder angle?
  }
  if (Rudder = Left) 
  {
    actSerial.println("Left")  //how do you want data sent? format wise
  }
  
  //////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////
  //Functions  //as in functions that aren't in libraries that need to be made//fewer = better
  //////////////////////////////////////////////////////////////////////////////////////
  //any ideas for needed function
  //possibly fancy ways of arranging sense data
  //or gaussian arbiter, that's probably a function or 10
  //////////////////////////////////////////////////////////////////////////////////////
}
