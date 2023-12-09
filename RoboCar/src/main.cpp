#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <DabbleESP32.h>

#define USER_SDA 21
#define USER_SCL 22

#include <Wire.h>
// #include <VL53L0X.h>
#include <SparkFun_TB6612.h>

/*------------------------------------------------------------
------------------------LED Definition------------------------
--------------------------------------------------------------*/

#define LED 2
#define REAR_LEFT_LED 33
#define REAR_RIGHT_LED 32

/*------------------------------------------------------------
----------------Motor Driver Pin Definition-------------------
--------------------------------------------------------------*/

#define MOTOR1_A 13   // AIN1
#define MOTOR1_B 12   // AIN2
#define MOTOR2_C 14   // BIN1
#define MOTOR2_D 27   // BIN2
#define MOTOR1_PWM 26 // PWM for Motor 1
#define MOTOR2_PWM 25 // PWM for Motor 2
#define STBY 23       // Standby Pin

// these constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1

const int offsetA = 1;
const int offsetB = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.

/*------------------------------------------------------------
--------------------Object initialization---------------------
--------------------------------------------------------------*/

// Motors
Motor motor1 = Motor(MOTOR1_A, MOTOR1_B, MOTOR1_PWM, offsetA, STBY);
Motor motor2 = Motor(MOTOR2_C, MOTOR2_D, MOTOR2_PWM, offsetB, STBY);

// //Distance Sensor
// VL53L0X VL53;
// #define HIGH_ACCURACY

/*------------------------------------------------------------
----------------------Speed Constants--------------------------
--------------------------------------------------------------*/

#define SLOW 85
#define MEDIUM 140
#define FAST 195

/*------------------------------------------------------------
---------------------------Variables--------------------------
--------------------------------------------------------------*/
// int distance = 0;

unsigned long previousMillis = 0;
unsigned long interval = 10;
int speed_state = SLOW; // start with SLOW speed
int current_speed = 0;  // start with 0 speed

void nonBlockingDelay(unsigned long period)
{
  // Serial.println("nonBlockingDelay of 10ms");
  static unsigned long time_now = 0;
  time_now = millis();
  while (millis() < time_now + period)
  {
    // wait approx. [period] ms
  }
}

void FlashBlueLed(int count)
{
  for (int i = 0; i < count; i++)
  {
    digitalWrite(LED, HIGH);
    nonBlockingDelay(50);
    digitalWrite(LED, LOW);
    nonBlockingDelay(50);
  }
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(MOTOR1_A, OUTPUT);
  pinMode(MOTOR1_B, OUTPUT);
  pinMode(MOTOR2_C, OUTPUT);
  pinMode(MOTOR2_D, OUTPUT);
  pinMode(REAR_LEFT_LED, OUTPUT);
  pinMode(REAR_RIGHT_LED, OUTPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(115200);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("RoboCart1"); // set bluetooth name of your device
  digitalWrite(LED, LOW);
  digitalWrite(REAR_LEFT_LED, LOW);
  digitalWrite(REAR_RIGHT_LED, LOW);

  FlashBlueLed(10);
}

void loop()
{
  Dabble.processInput();

  if (GamePad.isSelectPressed())
  {
    switch (speed_state)
    {
    case SLOW:
      FlashBlueLed(1);
      speed_state = MEDIUM;
      Serial.println("Speed set to MEDIUM");
      break;
    case MEDIUM:
      FlashBlueLed(2);
      speed_state = FAST;
      Serial.println("Speed set to FAST");
      break;
    case FAST:
      FlashBlueLed(3);
      speed_state = SLOW;
      Serial.print("Speed set to SLOW");
      break;
    default:
      speed_state = SLOW;
      Serial.print("Speed set to default.");
      break;
    }

    Serial.print("Speed state changed to: ");
    Serial.println(speed_state);
    nonBlockingDelay(250);
  }

  if (GamePad.isUpPressed())
  {
    // Forward
    motor1.drive(speed_state);
    motor2.drive(speed_state);

    // Brake lights
    digitalWrite(REAR_LEFT_LED, LOW);
    digitalWrite(REAR_RIGHT_LED, LOW);
    nonBlockingDelay(10); // non-blocking delay

    Serial.println("Idling. Brakes");
  }
  else if (GamePad.isDownPressed())
  {

    // Backward
    motor1.drive(-speed_state);
    motor2.drive(-speed_state);

    // Brake lights
    digitalWrite(REAR_LEFT_LED, HIGH);
    digitalWrite(REAR_RIGHT_LED, HIGH);
    nonBlockingDelay(10); // non-blocking delay

    Serial.println("Down Pressed. Reversing...");
  }
  else if (GamePad.isLeftPressed())
  {
    // Turn left
    motor1.drive(-speed_state);
    motor2.drive(speed_state);

    // Brake lights
    digitalWrite(REAR_LEFT_LED, HIGH);
    digitalWrite(REAR_RIGHT_LED, LOW);
    nonBlockingDelay(10); // non-blocking delay

    Serial.println("Left Pressed. Turning Left...");
  }
  else if (GamePad.isRightPressed())
  {
    // Turn right
    motor1.drive(speed_state);
    motor2.drive(-speed_state);

    // Brake lights
    digitalWrite(REAR_LEFT_LED, LOW);
    digitalWrite(REAR_RIGHT_LED, HIGH);
    nonBlockingDelay(10); // non-blocking delay

    Serial.println("Left Pressed. Turning Right...");
  }
  else
  {
    // Stop both motors.
    motor1.brake();
    motor2.brake();

    // Brake lights
    digitalWrite(REAR_LEFT_LED, HIGH);
    digitalWrite(REAR_RIGHT_LED, HIGH);
    Serial.println("Idling. Brakes");
  }
  nonBlockingDelay(10); // non-blocking delay
}
