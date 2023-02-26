// create an instance of the TFT library
TFT TFTscreen = TFT(cs, dc, rst);

void TaskLCD( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  //initialize the library
  TFTscreen.begin();
  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);
  //set the text size
  TFTscreen.setTextSize(5);
  // set font color
  TFTscreen.stroke(255, 255, 255);

  for(;;)
  { 
    // print Hello, World! in the middle of the screen
    TFTscreen.text("17", 50, 50);
    
    // wait 200 miliseconds until change to next color
    vTaskDelay(MS_DELAY(200)); 
  }
}