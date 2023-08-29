#include <PS4Controller.h>  //https://github.com/aed3/PS4-esp32

unsigned long lastTimeStamp = 0;

void notify()
{
  char messageString[200];
  // print all received data from PS4 Controller
  sprintf(messageString, "%4d,%4d,%4d,%4d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d",
  PS4.LStickX(), //int_8
  PS4.LStickY(), //int_8
  PS4.RStickX(), //int_8
  PS4.RStickY(), //int_8
  PS4.Left(), //boolean type
  PS4.Down(), //boolean type
  PS4.Right(), //boolean type
  PS4.Up(), //boolean type
  PS4.Square(), //boolean type
  PS4.Cross(), //boolean type
  PS4.Circle(), //boolean type
  PS4.Triangle(), //boolean type
  PS4.L1(), //boolean type
  PS4.R1(), //boolean type
  PS4.L2(), //boolean type
  PS4.R2(), //boolean type  
  PS4.Share(), //boolean type
  PS4.Options(), //boolean type
  PS4.PSButton(), //boolean type
  PS4.Touchpad(),
  PS4.Charging(),
  PS4.Audio(),
  PS4.Mic(),
  PS4.Battery());

  //Only needed to print the message properly on serial monitor. Else we dont need it.
  if (millis() - lastTimeStamp > 50)
  {
    Serial.println(messageString);
    lastTimeStamp = millis();
  }
}

void onConnect()
{
  Serial.println("Connected!.");
  PS4.setLed(255, 0, 0); //RGB Color
  PS4.sendToController();
}

void onDisConnect()
{
  Serial.println("Disconnected!.");    
}

void setup() 
{
  Serial.begin(115200);
  PS4.attach(notify);
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin("0a:0a:0a:0a:0a:0a");  //set the six axis mac address by our own. Please make sure the mac address is unique and the last bit of the first byte must be zero. https://www.rapidtables.com/convert/number/hex-to-binary.html
  Serial.println("Ready.");
}

void loop() 
{
}
