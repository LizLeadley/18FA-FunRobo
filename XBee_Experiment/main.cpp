///**********************************************************************************
// *
// * Title: 18FA FunRobo Basic Operations
// * Description:
// *    *Sample code and experimentation with XBee communications shielf
// * Robot or hardware: Laptop computer running C++, XBee shield, XBee shield on arduino
// * Hardware notes and warnings: none
// * Created by: Liz Leadley, 10-2-18
// * Edited by:
// * Conventions:
// *    *Strict camelCase naming without underscores for variables
// *    *Keep comments locally aligned; when overflow, comment on an empty line below
// *
// *********************************************************************************/
//
///*
// * TODO: Wait for Dave to figure this out, include the libraries, and make it modularly pop-in
// * TODO: For now, use Serial with USB
// */
//
//#include <iostream>
//#include "SerialPort.h"
//#include <stdio.h>
//#include <string.h>
//
//using namespace std;
//
//char* portName = "\\\\.\\COM20";
//
//#define MAX_DATA_LENGTH 255
//
//char incomingData[MAX_DATA_LENGTH];
//
////Control signals for turning on and turning off the led
////Check arduino code
//char ledON[] = "ON\n";
//char ledOFF[] = "OFF\n";
//
////Arduino SerialPort object
//SerialPort *arduino;
//
////Blinking Delay
//const unsigned int BLINKING_DELAY = 1000;
//
////If you want to send data then define "SEND" else comment it out
//#define SEND
//
//void exampleReceiveData(void)
//{
//    int readResult = arduino->readSerialPort(incomingData, MAX_DATA_LENGTH);
//    printf("%s", incomingData);
//    Sleep(10);
//}
//
//void exampleWriteData(unsigned int delayTime)
//{
//    arduino->writeSerialPort(ledON, MAX_DATA_LENGTH);
//    Sleep(delayTime);
//    arduino->writeSerialPort(ledOFF, MAX_DATA_LENGTH);
//    Sleep(delayTime);
//}
//
//void autoConnect(void)
//{
//    //wait connection
//    while (!arduino->isConnected()) {
//        Sleep(100);
//        arduino = new SerialPort(portName);
//    }
//
//    //Checking if arduino is connected or not
//    if (arduino->isConnected()) {
//        std::cout << "Connection established at port " << portName << endl;
//    }
//
//#ifdef SEND
//    while(arduino->isConnected()) exampleWriteData(BLINKING_DELAY);
//#else // SEND
//    while(arduino->isConnected()) exampleReceiveData();
//#endif // SEND
//
//    //if the serial connection is lost
//    autoConnect();
//}
//
//int main()
//{
//    arduino = new SerialPort(portName);
//
//    autoConnect();
//}

//---------------------------------------Testing straightup Serial-------------------------------

#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

int main()
{
    FILE *file;
//int file;
    //Opening device file

    char getnum;

    while (1)
    {
        file = fopen("/dev/ttyACM0", "w");
        cout << "Input key, q to quit >>" << endl;
        cin >> getnum;
//        if (getnum == "q")
//        {
//            break;
//        }
//        else
//        {
//            write(file, "%d", getnum);
            fprintf(file, "%d", getnum); //Writing to the file

            fclose(file);
//        }
    }

}

