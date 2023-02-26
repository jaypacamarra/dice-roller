extern const uint8_t D4;
extern const uint8_t D6;
extern const uint8_t D8;
extern const uint8_t D10;
extern const uint8_t D12;
extern const uint8_t D20;

void TaskRoll( void *pvParameters __attribute__((unused)) )  // This is a Task.
{

  randomSeed(analogRead(A0));
  bool shake = false;
  uint8_t roll_value;

  for (;;)
  {
    // If shake detected, generate roll number
    if(shake)
    {
      if(strcmp(sDiceType[g_DiceType], sDiceType[D4]))
      {
        roll_value = roll_dice(1,4);
      }
      if(strcmp(sDiceType[g_DiceType], sDiceType[D6]))
      {
        roll_value = roll_dice(1,6);
      }
      if(strcmp(sDiceType[g_DiceType], sDiceType[D8]))
      {
        roll_value = roll_dice(1,8);
      }
      if(strcmp(sDiceType[g_DiceType], sDiceType[D10]))
      {
        roll_value = roll_dice(1,10);
      }
      if(strcmp(sDiceType[g_DiceType], sDiceType[D12]))
      {
        roll_value = roll_dice(1,12);
      }
      if(strcmp(sDiceType[g_DiceType], sDiceType[D20]))
      {
        roll_value = roll_dice(1,20);
      }
    }

    vTaskDelay(MS_DELAY(1)); 
  }
}

uint8_t roll_dice(uint8_t min, uint8_t max)
{
  return random(min,(max+1));
}