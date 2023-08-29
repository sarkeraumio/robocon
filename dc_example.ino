int speed = 190;               // set speed 0-255
int timer = 1000;           // variable timer

const int IN1 = 22;          //L298N IN1 pin to ESP32 pin 22
const int IN2 = 23;          //L298N IN2 pin to ESP32 pin 23
const int IN3 = 5;           //L298N IN3 pin to ESP32 pin 5
const int IN4 = 4;           //L298N IN4 pin to ESP32 pin 4

void setup() 
{
  Serial.begin(115200);    
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  pinMode(IN4,OUTPUT);     
  pinMode(IN3,OUTPUT);
}

void loop() {
 Spin_cw();
 delay(3000);
 Serial.println("Finish clockwise");
 Stop();
 delay(timer);
 Spin_ccw();
 Serial.println("Finish counter clockwise");
 delay(3000);
 Stop();
 delay(timer);
}

void Spin_cw(void)          
{
  analogWrite(IN1, speed); // set pwm to motor 1
  analogWrite(IN2, 0);

  analogWrite(IN3, 0);
  analogWrite(IN4, speed); // set pwm to motor 2
} 

void Stop(void)              //Stop all the motor
{
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);

  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

void Spin_ccw(void)          
{
  analogWrite(IN1, 0); // set pwm to motor 1
  analogWrite(IN2, speed);

  analogWrite(IN3, speed);
  analogWrite(IN4, 0); // set pwm to motor 2
} 
