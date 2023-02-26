// for bounds checking
extern const uint8_t D4;
extern const uint8_t D20;

void dice_type_decr(void);

void TaskReadButtonL( void *pvParameters __attribute__((unused)) )
{
  const uint8_t button_L_pin = 6;
  bool button_L_is_pressed = false;
  pinMode(button_L_pin, INPUT_PULLUP);

  for(;;)
  {
    if(digitalRead(button_L_pin) == LOW)
    {
      vTaskDelay(MS_DELAY(30));
      if(digitalRead(button_L_pin) == LOW)
      {
        button_L_is_pressed = true;
        dice_type_decr();
        while(digitalRead(button_L_pin) == LOW); // wait until depress
      }
      else
      {
        button_L_is_pressed = false;
      }
    }
  }
}

void dice_type_decr()
{
  // See if we can obtain the dice type Semaphore.
  // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
  if ( xSemaphoreTake( xDiceType_semphr, ( TickType_t ) 5 ) == pdTRUE )
  {
    // We were able to obtain or "Take" the semaphore and can now access the shared resource.
    // We want to have the dice type variable for us alone,
    // so we don't want it getting stolen during the middle of writing to it.
    g_DiceType--;

    // bounds check
    if(g_DiceType < D4)
    {
      g_DiceType = D20;
    }

    xSemaphoreGive( xDiceType_semphr ); // Now free or "Give" the Serial Port for others.
  }
}