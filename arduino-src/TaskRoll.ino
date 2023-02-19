/*
    TaskRoll:

    Process accelerometer and gyro data and classifies if a user roll has been performed
    Generates dice roll number based on user roll action
    User roll action is performed after shaking the dice (enclosure) and the 
    Detects if dice is still by checking accelerometer and gyro derivative if near zero for a second
*/


void TaskRoll(void *pvParameters)
{
  sensors_event_t a, g, temp;
  for(;;)
  {
    /* Get new sensor events with the readings */
    mpu.getEvent(&a, &g, &temp);

    /* Print out the values */
    Serial.print("Acceleration X: ");
    Serial.print(a.acceleration.x);
    Serial.print(", Y: ");
    Serial.print(a.acceleration.y);
    Serial.print(", Z: ");
    Serial.print(a.acceleration.z);
    Serial.println(" m/s^2");

    Serial.print("Rotation X: ");
    Serial.print(g.gyro.x);
    Serial.print(", Y: ");
    Serial.print(g.gyro.y);
    Serial.print(", Z: ");
    Serial.print(g.gyro.z);
    Serial.println(" rad/s");

    Serial.print("Temperature: ");
    Serial.print(temp.temperature);
    Serial.println(" degC");

    Serial.println("");
    vTaskDelay(500);
  }
}