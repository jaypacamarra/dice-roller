#include <Arduino_FreeRTOS.h>
#include <TFT.h>
#include <SPI.h>

// define two Tasks for DigitalRead & AnalogRead
void TaskLCD( void *pvParameters );
void TaskRoll( void *pvParameters );


// pin definition for Arduino UNO
#define cs            10
#define dc            9
#define rst           8

// macro to convert ms delay properly since rtos ticks are every 15ms
#define MS_DELAY(x)   (x/15) 



// create an instance of the TFT library
TFT TFTscreen = TFT(cs, dc, rst);


// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  xTaskCreate(
    TaskLCD
    ,  "TaskLCD"  // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters for the task
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL ); //Task Handle

  xTaskCreate(
    TaskRoll
    ,  "TaskRoll" // A name just for humans
    ,  128  // Stack size
    ,  NULL //Parameters for the task
    ,  1  // Priority
    ,  NULL ); //Task Handle

  // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

