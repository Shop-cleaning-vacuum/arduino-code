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
#define COMMAND_DELIMITER  '$'
#define READ_TABLE_CMD     "R"
#define WRITE_TABLE_CMD    "W"
#define TABLE_START        "S"
#define TABLE_END          "E"

// Global variables to control the motor speed, 0-10
byte left_motor  = 0;
byte right_motor = 0;

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
  // Run the inputed commands corresponding functions
  if( cmd == READ_TABLE_CMD )
  {
    SendTable();
  }
  else if( cmd == WRITE_TABLE_CMD )
  {
    WriteTable();
  }
}

// ---- Send the table data over the serial port ----
void SendTable() 
{
  // Send beginning of table id
  Serial.println(TABLE_START);
  
  // Send all the motor data
  Serial.println(right_motor);
  Serial.println(left_motor);
}

// ---- Write the data from the serial port to teh table ----
void WriteTable() 
{
  // Update all the motor data
  Serial.readBytes(&right_motor,1);
  Serial.readBytes(&left_motor,1);
}
