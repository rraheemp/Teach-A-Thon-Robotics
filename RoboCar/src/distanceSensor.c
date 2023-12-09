// Serial.print("SDA :");
//   Serial.print(SDA); //
//   Serial.print("SCL :");
//   Serial.print(SCL); //

//   Wire.begin(SDA, SCL);

//   VL53.setTimeout(500);
//   if (!VL53.init())
//   {
//     Serial.println("Failed to detect and initialize VL53!");
//     while (1)
//     {
//     }
//   }
//   digitalWrite(LED, LOW); //

// #if defined LONG_RANGE
//   // lower the return signal rate limit (default is 0.25 MCPS)
//   VL53.setSignalRateLimit(0.1);
//   // increase laser pulse periods (defaults are 14 and 10 PCLKs)
//   VL53.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
//   VL53.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
// #endif

// #if defined HIGH_SPEED
//   // reduce timing budget to 20 ms (default is about 33 ms)
//   VL53.setMeasurementTimingBudget(20000);
// #elif defined HIGH_ACCURACY
//   // increase timing budget to 200 ms
//   VL53.setMeasurementTimingBudget(200000);
// #endif
// }