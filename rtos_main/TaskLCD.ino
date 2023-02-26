void TaskLCD( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  //initialize the library
  TFTscreen.begin();
  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);
  //set the text size
  TFTscreen.setTextSize(2);

  for(;;)
  {
    //generate a random color
    int redRandom = random(0, 255);
    int greenRandom = random (0, 255);
    int blueRandom = random (0, 255);
    
    // set a random font color
    TFTscreen.stroke(redRandom, greenRandom, blueRandom);
    
    // print Hello, World! in the middle of the screen
    TFTscreen.text("Hello, World!", 6, 57);
    
    // wait 200 miliseconds until change to next color
    vTaskDelay(MS_DELAY(200)); 
  }
}