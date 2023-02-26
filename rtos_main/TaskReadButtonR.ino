// for bounds checking
extern const uint8_t D4;
extern const uint8_t D20;

void dice_type_incr(void);

void TaskReadButtonR( void *pvParameters __attribute__((unused)) )
{
  const uint8_t button_R_pin = 7;
  bool button_R_is_pressed = false;
  pinMode(button_R_pin, INPUT_PULLUP);

  for(;;)
  {
    if(digitalRead(button_R_pin) == LOW)
    {
      vTaskDelay(MS_DELAY(30));
      if(digitalRead(button_R_pin) == LOW)
      {
        button_R_is_pressed = true;
        while(digitalRead(button_R_pin) == LOW); // wait until depress
      }
      else
      {
        button_R_is_pressed = false;
      }
    }
  }
}

void dice_type_incr()
{
  // See if we can obtain the dice type Semaphore.
  // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
  if ( xSemaphoreTake( xDiceType_semphr, ( TickType_t ) 5 ) == pdTRUE )
  {
    // We were able to obtain or "Take" the semaphore and can now access the shared resource.
    // We want to have the dice type variable for us alone,
    // so we don't want it getting stolen during the middle of writing to it.
    g_DiceType++;

    // bounds check
    if(g_DiceType > D20)
    {
      g_DiceType = D4;
    }

    xSemaphoreGive( xDiceType_semphr ); // Now free or "Give" the Serial Port for others.
  }
}