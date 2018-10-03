/**********************************************************************************
 *
 * Title: 18FA FunRobo Basic Operations
 * Description:
 *    *Sense-Think-Act structure
 *    *Practicing structure and commands
 * Robot or hardware: Laptop computer running C++
 *    *Prompt for input commands and respond appropriately
 * Hardware notes and warnings: none
 * Created by: Liz Leadley, 9-27-18
 * Edited by:
 * Conventions:
 *    *Strict camelCase naming without underscores for variables
 *    *Keep comments locally aligned; when overflow, comment on an empty line below
 *
 *********************************************************************************/

//=====To do list:=====------------------------------------------------------------
//Resolve Arduino to CLion translation
// TODO: add loop error checking to main loop
// TODO: un-serial input call


//=================================================================================
//Supporting Libraries
//=================================================================================
//#include <Servo.h>                     //load ServoMotors library
#include <iostream>                    // include input-output stream
#include <cstdio>                      // include standard input-output
#include <cstdlib>                     // include standard libraries
#include <string>                      // include string variable type
#include <ctime>                       // prepare to have timers with 'precision time handling' library
#include <termios.h>                   // header contains definitions used by the terminal I/O
#include <unistd.h>                    // header defines miscellaneous symbolic constants
#include <fcntl.h>                     // define requests and arguments for use by some functions
#include <sys/time.h>                  // header defines the timeval structure
#include <sys/types.h>                 // header include definitnions for at least the system types

using namespace std;                   // declare default namespace to be standard

//=================================================================================
//Initialize Functions
//=================================================================================
string getInput();                      // announce operator input function
void blinkAliveLED();                   // announce blinkny light function
char robotStop();                       // announce robot keyboard stop function

//=================================================================================
//Global variables, objects, and constants
//=================================================================================
//Create and initialize:
bool aliveLEDState = true;      //state for blinky light to use with timer
bool eStop = true;              //state for Emergency Stop of all motors
bool realTimeRunStop = true;    //flag for real time run control loop
bool runController = true;      //flag to un-duino the main loop
string command;                 //operator command string
string loopError;               //real time control loop error system string
clock_t oldLoopTime = 0;     //past loop time, clock ticks
clock_t newLoopTime = 0;     //new loop time, clock ticks
clock_t cycleTime = 0;       //elapsed loop cycle time
clock_t controlLoopInterval = 100000;
                                  //control loop cycle time, clock ticks
char key;                         // initialize key for command storages

//=================================================================================
//SETUP: Single-run code to start, configure, and pre-test functionality
//    Set up robot mission to prepare for launch
//=================================================================================
int main()
{
    //=====Robot=====----------------------------------------------------------------
    //Device setup code (runs once):

//    Serial.begin(9600);                 //open serial communications
    cout << "*****Controller initializing. Stay clear, please.***** \n";
    //give fair warning and test serial comm

    //=====Mission=====--------------------------------------------------------------
    //Mission setup code (runs once):

//------------End of void setup------------



//=================================================================================
//THE LOOP: Continuously-run flight code for think, sense, and act functionality
//    Repeats until power-down
//=================================================================================
    while (runController)
    {
        //====Outer Loop=====Outer Loop=====Outer Loop=====Outer Loop=====Outer Loop=====
        //Outer Loop=====Outer Loop=====Outer Loop=====Outer Loop=====Outer Loop====Outer
        //Non real-time dependant tasks
        //=====Operator to Robot Input=====----------------------------------------------
        command = getInput();                     //get commands from serial monitor
        if (command == "quit") break;              //break to escape infinite loop
        else if (command == "stop") realTimeRunStop = false;
                                                    // set flag to skip real time loop
        else if (command == "follow") realTimeRunStop = true;
        else if (command == "avoid") realTimeRunStop = true;
                                                    // set flag to run real time loop
        else
        {                                           // catch bad commands and flag to skip real time loop
            cout << "Not a command we can handle, please try again \n";
            realTimeRunStop = false;
        }

        //=====Robot Status Report=====--------------------------------------------------


//------------End of Outer Loop------------

        //====Real Time Loop=====Real Time Loop=====Real Time Loop=====Real Time Loop====
        //Real Time Loop=====Real Time Loop=====Real Time Loop=====Real Time Loop====Real
        //Repeatedly running at a fixed 'real-time' period

        while (realTimeRunStop)
        {     //unless stop is commanded, run control loop

            //Clock control for soft real-time
            //Ensures loop runs once per interval
            newLoopTime = clock();           //store current time
            if (newLoopTime - oldLoopTime >= controlLoopInterval)
            {
                //if interval has passed, run flight code
                oldLoopTime = newLoopTime;      //prepare for new newLoopTime
                blinkAliveLED();                //blink 'alive' blinky light
                //if structure stays open for control loop


                //=====Sense=====
                //Sense=====Sense=====Sense=====Sense=====Sense=====Sense=====Sense=====Sense====

                key = robotStop();              // poll keyboard for command


                //=====Think=====
                //Think=====Think=====Think=====Think=====Think=====Think=====Think=====Think====

                //if-then select behavior based on command previously input
                if (key == 's')
                {
                    cout << "Bot will cease. \n";
                    cout << "Terminating real time control loop. \n";
                    realTimeRunStop = false;
                    break;                              //exit control loop
                }
                else if (command == "follow")
                {          //move to commanded position
                    cout << "Follow mode. \n";
//                    cout << "Use 's' and ENTER to stop bot \n";
                    realTimeRunStop = true;             //stay in control loop
                }
                else if (command == "avoid")
                {          //keep alive-ness with small motions
                    cout << "Avoid mode. \n";
//                    cout << "Use 's' and ENTER to stop bot \n";
                    realTimeRunStop = true;             //stay in control loop
                }
                else if (key != 'n')
                    {
                    cout << "============================================================== \n";
                    cout << "|           ***Invalid input ignored*** Try again            | \n";
                    cout << "============================================================== \n";
                    realTimeRunStop = true;
                }

                //=====Act=====
                //Act=====Act=====Act=====Act=====Act=====Act=====Act=====Act=====Act=====Act====
//            eStop = digitalRead(eStopPin);        // Check eStop switch



                //Check timing, whether loop ran within increment time
                cycleTime = clock() - newLoopTime;       //check loop execution time
                if (cycleTime > controlLoopInterval)
                {
                    cout << "************************************************************ \n";
                    cout << "Error! Real time has failed. Stopping robot now. \n";
                    //loop took too long
                    cout << "1000 ms, 100000 tick loop instead took ";
                    cout << (float) cycleTime / CLOCKS_PER_SEC << " ms\n";            //print time taken
                    cout << "************************************************************ \n";
                    break;                                //exit control loop
                }

            }                //end of if (newLoopTime - oldLoopTime >= ...)
        }                //end of while(realTimeRunStop ...)
//------------End of Real Time Loop------------

//Report state to operator
        cout << "============================================================== \n";
        cout << "|     Robot control loop stopping to wait for new command    | \n";
        cout << "============================================================== \n";
        //alert operator to current status

    }
//------------End of main while loop------------
//=================================================================================
//End of flight code section
//=================================================================================
}
//------------End of main()------------
//=================================================================================
//End of setup and run sections
//=================================================================================



//=================================================================================
//FUNCTIONS: Simple functions serving sense, think, act functionalities.
//    Most functions should live in a separate .h file, #include file at start
//=================================================================================


//=====Setup Functions=====--------------------------------------------------------

//=====Flight Functions====Flight Functions====Flight Functions====Flight Functions
//Flight Functions====Flight Functions====Flight Functions====Flight Functions=====


//=====Operator Control=====-------------------------------------------------------

string getInput()
{
    //Print operator command options to serial, prompt for input of command
    cout << "============================================================== \n";
    cout << "|            Robot Commands: follow, avoid, quit             | \n";
    cout << "|            Use 's' and ENTER at any time to stop           | \n";
    cout << "|                                                            | \n";
    cout << "|           Type desired command, then press ENTER           | \n";
    cout << "============================================================== \n";

//    while (Serial.available()==0) {};         //wait until command is given
//    command = Serial.readString();            //save given string to 'command'
    cin >> command;
    cout << "============================================================== \n";
    cout << "|               New behavior command accepted:                | \n";
    cout << "                           " << command << "\n"; // << "                            | \n";
    cout << "|Use 's' and ENTER to exit control loop and input new command |\n";
    cout << "============================================================== \n";
    return command;                           //send command back out of the function

}
//-----End getInput-----

//====Real Time=====---------------------------------------------------------------


//Blink blinky alive light by announcing in cout
void blinkAliveLED()
{
    //toggle the state of aliveLED blinky light
    //if it's on, turn it off; if it's off, turn it on:
    if (aliveLEDState == true)
    {
        cout << "Blinky light _\\|/_ \n";
        aliveLEDState = false;
    }
    else if (aliveLEDState == false)
    {
        cout << "Blinky light       \n";
        aliveLEDState = true;
    }

}

char robotStop()
{
// polls keyboard and returns character entered (or 'n' for no key)
// while allowing outer loop to run
// requires inclusions: #include <termios.h>;  #include <unistd.h>; #include <fcntl.h>;
//      #include <sys/time.h>; #include <sys/types.h>; #include <iostream>; using namespace std

    struct termios oldSettings, newSettings;
    char key = 'n';
    tcgetattr( fileno( stdin ), &oldSettings );
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr( fileno( stdin ), TCSANOW, &newSettings );
        fd_set set;
        struct timeval tv;
        tv.tv_sec = 2;
        tv.tv_usec = 0;
        FD_ZERO( &set );
        FD_SET( fileno( stdin ), &set );
        int res = select (fileno( stdin )+1, &set, NULL, NULL, &tv );
        if( res > 0 )
        {
            char c;
            printf( "Command received\n" );
            read( fileno( stdin ), &c, 1 );
            key = c;
        }
        else if( res < 0 )
        {
            perror( "Select error" );
            tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
            return 'e';
        }
        else
        {
//            printf( "Real-time control loop running: type 's' and 'enter' to stop\n" );
        }

        if ( key != 'n' )
        {
            tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
            return key;
        }
        else
        {
            tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
            return 'n';
        }



}
//=====Sense=====------------------------------------------------------------------


//=====Think=====------------------------------------------------------------------


//=====Act=====--------------------------------------------------------------------



//------------End of Functions------------
//------------------End of Code------------------
