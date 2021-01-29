//EDMO-Motor Module - PID Control Template
//Author: DKE-SwarmLab
//This script contains a template for the implementation of a PID controller with the EDMO-Motor Module and the L298N DC motor driver board.
//The template provides a framework for the implementation of the PID controller and the operation of the DC motor driver board L298N.
//Furthermore it provides a function to read the PID-gains kp, ki, and kd via the serial monitor. Those need to be entered in the format <kp-value>,<ki-value>,<kd-value>

// *********************************************************************************************************************** //
// Variables                                                                                                               //
// *********************************************************************************************************************** //

//pin definition
#define ENA 9 //Arduino pin connected to the enable pin of the motor driver (for setting the motor speed via PWM)
#define IN1 21 //Arduino pin connected to the In1-pin of the DC motor driver board L298N(for setting the motor direction)
#define IN2 20 //Arduino pin connected to the In2-pin of the DC motor driver board L298N(for setting the motor direction)
#define SENSOR_PIN A0 //Analog input pin of the rotary encoder

// ******** <TODO> **********************
// ******** define interval between recomputing error and adjusting feedback (in milliseconds) ********************** 
const int INTERVAL = 0; 
unsigned long previousTime = 0;

int motorSpeed = 0; // speed of the motor, values between 0 and 255
int target = 512; // position (as read by potentiometer) to move the motor to, default value 512

// ******** <TODO> **********************
// ******** define the different gains **********************
float kp = 0.0; // proportional gain
float ki = 0.0; // integral gain
float kd = 0.0; // derivative gain

int pos = 0; // current position for plotting
//serial communication variables
float PID_values[4];
byte i = 0;
char record[100];
char recvchar;
byte indx = 0;

// setup code, setting pin modes and initialising the serial connection
void setup() 
{
    Serial.begin(115200);

    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);    
    pinMode(SENSOR_PIN, INPUT);   
}

void loop() 
{
        //  ******** <TODO> **********************
        //  ******** implement your code  here **********************

        //print actual motor position and target value to serial-monitor/plotter
        Serial.print(pos);
        Serial.print(" ");   
        Serial.println(target);
    
}

// method to set direction and speed of the motor
void setMovement(int dir, int speed1) 
{
        //  ******** <TODO> **********************
        //  ******** implement your code  here **********************
}
// *********************************************************************************************************************** //
// method for receiving commands over the serial port
void readInput() 
{
      if (Serial.available())
    {
        recvchar = Serial.read();
        if (recvchar != '\n')
        { 
            record[indx++] = recvchar;
        }
        else if (recvchar == '\n')
        {
          record[indx] = '\0';
          indx = 0;
          
          convertData(record);
          if(i==4){
          target = PID_values[0];
          kp = PID_values[1];
          ki = PID_values[2];
          kd = PID_values[3];
          Serial.print("Entered Values:");
          printData(PID_values);
          }
          else
          {
          Serial.println("Enter correct number of values separated by commas!!");            
          }
        }
    }
}
// *********************************************************************************************************************** //
//method for reading/interpreting serial input 
void convertData(char record[])
{
    i = 0;
    char *index = strtok(record, ",");
    while(index != NULL)
    {
       PID_values[i++] = atof(index); 
        index = strtok(NULL, ",");
    }
}
// *********************************************************************************************************************** //
//method for printing values entered via the serial monitor
void printData(float data[])
{
    for (byte j = 0 ; j < 4 ; j++)
    {
      Serial.print(data[j]);
      Serial.print('\t');
    }
    Serial.println(); 
}
