////////////////////////////////////////////////
//Title: Act Arduino
//Description: Act Slave Arduino, serially connected (w/ digital pins
////10,11) to Master Arduino Think
//Robot Name?: Boat?
//What does code do: Code will simple serial connect Act Arduino 
////to Think arduino (not sense) sending data and recieving commands
//Hardware Warnings:
//Created by Team Think
////////////////////////////////////////////////

///////////////////////////////
//Libraries
///////////////////////////////
#include <SoftwareSerial.h> //includes software serial library
///////////////////////////////

//Sets up Simple Serial communication
SoftwareSerial senseSerial(10,11); //connects act arduino to think arduino using pins 10 & 11

void setup() {
  // put your setup code here, to run once:
  actSerial.begin(9600); //sets baud rate for act to 9600
  //actSerial has same name in think and act arduinos
}

void loop() {
  // put your main code here, to run repeatedly:
   ////////////////////////////////////////
  //Basic softSerial Code
  ////////////////////////////////////////
  if (senseSerial.available()>0) //if any data sent through connection
  {
    senseSerial.read(); //read and return data sent
  }
  senseSerial.println("Message to Think Arduino");//Prints data to the transmit pin of the Act software serial port
  senseSerial.write("hello think"); //Prints data to the transmit pin of the software serial port as raw bytes.
  ////////////////////////////////////////

  ////////////////////////////////////////
  //Basic Act Actions Following
  ////////////////////////////////////////

  //read data from think arduino  (probably active)
  if (actSerial.available()>0)
  {
    if (Rudder)
    {
      Turn = senseSerial.read(); 
    }
    else if (Move)
    {
      Move = senseSerial.read();
    }
  }
  //send data to think arduino    (probably passive)
  //send motor, rudder, heading movement updates
  ////////////////////////////////////////
}
