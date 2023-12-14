// #include <Arduino.h>

// // Define the pins connected to the sound sensor and the LED
// const int soundSensorPin = 34;
// const int ledPin = 2;

// // Define a variable to store the previous state of the sound sensor
// int previousState = LOW;

// void setup()
// {
//   // Initialize the serial port
//   Serial.begin(9600);

//   // Configure the sound sensor pin as an input
//   pinMode(soundSensorPin, INPUT);

//   // Configure the LED pin as an output
//   pinMode(ledPin, OUTPUT);
// }

// void loop()
// {
//   // Read the value from the sound sensor
//   int soundSensorValue = digitalRead(soundSensorPin);

//   // Print the sound sensor value to the serial port
//   Serial.println(soundSensorValue);

//   // If the sound sensor detects a high and the previous state was low, turn on the LED
//   if (soundSensorValue == HIGH && previousState == LOW)
//   {
//     digitalWrite(ledPin, HIGH);
//     delay(50);
//     Serial.println("LED on");
//   }

//   // If the sound sensor detects a low, turn off the LED
//   else
//   {
//     digitalWrite(ledPin, LOW);
//     //  Serial.println("LED off");
//   }

//   // Update the previous state of the sound sensor
//   previousState = soundSensorValue;
// }
