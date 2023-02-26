#include <Arduino_FreeRTOS.h>
#include <string.h>
#include <semphr.h>
#include <TFT.h>
#include <SPI.h>

// define two Tasks for DigitalRead & AnalogRead
void TaskLCD( void *pvParameters );
void TaskRoll( void *pvParameters );
void TaskReadButtonL( void *pvParameters );
void TaskReadButtonR( void *pvParameters );


// pin definition for Arduino UNO
#define cs            10
#define dc            9
#define rst           8

// macro to convert ms delay properly since rtos ticks are every 15ms
#define MS_DELAY(x)   (x/15) 

// semaphore for dice type
SemaphoreHandle_t xDiceType_semphr;

const char* sDiceType[] = {"D4", "D6", "D8", "D10", "D12", "D20"};
const uint8_t D4 = 0;
const uint8_t D6 = 1;
const uint8_t D8 = 2;
const uint8_t D10 = 3;
const uint8_t D12 = 4;
const uint8_t D20 = 5;
int8_t g_DiceType = D20; // variable to hold dice type currently selected, default is D20


// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
  // because it is sharing a resource, such as the Serial port.
  // Semaphores should only be used whilst the scheduler is running, but we can set it up here.
  if ( xDiceType_semphr == NULL )  // Check to confirm that the dice type Semaphore has not already been created.
  {
    xDiceType_semphr = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage dice type changes
    if ( ( xDiceType_semphr ) != NULL )
      xSemaphoreGive( ( xDiceType_semphr ) );  // Make the dice type variable available for use, by "Giving" the Semaphore.
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

  xTaskCreate(
    TaskReadButtonL
    ,  "TaskReadButtonL" // A name just for humans
    ,  128  // Stack size
    ,  NULL //Parameters for the task
    ,  1  // Priority
    ,  NULL ); //Task Handle

  xTaskCreate(
    TaskReadButtonR
    ,  "TaskReadButtonR" // A name just for humans
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

