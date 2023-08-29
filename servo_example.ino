/** There are two ways to control servo in esp32:

1. LEDC function
2. Servo.h Library (based on LEDC function)

**/

#include <Servo.h> //https://randomnerdtutorials.com/esp32-servo-motor-web-server-arduino-ide/

#define SERVO_PIN 13

int pos = 0;
Servo servo;

void setup() {

  Serial.begin(115200);
  servo.attach(SERVO_PIN, 2);  // attaches the servo on pin 13 to the servo object at LEDC Channel 2
}

void loop() {
  if (Serial.available() > 0) {
    // receive the input data from the serial
    pos = Serial.parseInt();

    if (Serial.read() == '\n');

  }
  servo.write(pos); //set the position of servo
  Serial.println(pos); //print the data in serial
  delay(10); //set delay
}
