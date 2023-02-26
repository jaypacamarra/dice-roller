void TaskRoll( void *pvParameters __attribute__((unused)) )  // This is a Task.
{

  randomSeed(analogRead(A0));
  bool shake = false;

  for (;;)
  {
    // If shake detected, generate roll number
    if(shake)
    {
      ;
    }

    //delay 1000ms
    vTaskDelay(MS_DELAY(500)); 
  }
}