// @author  Isaac Marquez
// @date    March 4th, 2021
// @details testing prototype of how the motor control
//          microcontroller will respond to our
//          request for controlling the robot.


//-------------------------------------------------
//-------------- GLOBAL VARIABLES -----------------
//-------------------------------------------------

// Macros of the command identifiers sending
// and recieving data over the serial port
#define COMMAND_DELIMITER      '$'
#define STOP_CMD_ID            "S"
#define FWD_CMD_ID             "F"
#define ACK                    "A"

// Global flags to know if the robot is stopped 
// or going forward
bool stopped = true;

//-------------------------------------------------
//------------------- SET UP ----------------------
//-------------------------------------------------

void setup() {
  // Create the serial communcation at a baude rate of 9600
  Serial.begin(9600);
}

//-------------------------------------------------
//-------------------- LOOP -----------------------
//-------------------------------------------------

// Listen for commands comming from navigation
void loop() 
{
  // Don't read if the line is busy
  if (Serial.available() > 0) 
  {
    // Read until you recieve the command delimiter character
    String cmd = Serial.readStringUntil(COMMAND_DELIMITER);

    // Run the command 
    RunCommand(cmd);
  }
}

//-------------------------------------------------
//-------------- HELPER FUNCTIONS -----------------
//-------------------------------------------------

// ---- Run the inputed command ----
void RunCommand(String cmd)
{
  // Change the status of the robot based on the 
  // inputed command
  if( cmd == STOP_CMD_ID )
  {
    StopRobot();
  }
  else if( cmd == FWD_CMD_ID )
  {
    MoveFoward();
  }
}

// ---- Stop the robot ----
void StopRobot()
{
    // Stop the robot
    stopped = true;

    // Send acknowledge back to navigation
    Serial.println(ACK);
    Serial.println(COMMAND_DELIMITER);
}

// ---- Move the robot forward ----
void MoveFoward()
{
    // move the robot forward
    stopped = false;

    // Send acknowledge back to navigation
    Serial.println(ACK);
    Serial.println(COMMAND_DELIMITER);
}
