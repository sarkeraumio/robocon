/** robomaster motor (rm) control by can bus **/

#include <esp32_can.h>  //https://github.com/collin80/esp32_can  and https://github.com/collin80/can_common
#include "rm_set.h" //custom library

/**can frame  tx -> transmit data 
              rx -> receive data **/
CAN_FRAME tx_msg0, rx_msg0;

/** call the custom library rm_set **/
Rm_set motors;

/** variables **/
int rpm = 0; //control rpm 
int position = 0; //control position

void canCallback(CAN_FRAME *frame) {
  // call back function
  int rx_id = frame->id;
  motors.update_motor_status(rx_id - 0x201, micros(), frame->data.uint8[0] << 8 | frame->data.uint8[1], frame->data.uint8[2] << 8 | frame->data.uint8[3]);
}

//send can frame to the rm motors
void send_can_frame() {
  for (int i = 0; i < 8; i++) {
    tx_msg0.data.byte[i] = motors.can_msg0[i];
  }
  CAN0.sendFrame(tx_msg0);
}

void setup() {

  /** Setup Serial port to display data */
  Serial.begin(115200);

  tx_msg0.id = 0x200; //rm motors can bus id
  tx_msg0.length = 8;

  CAN0.begin(1000000); //set up can bus baud rate
  CAN0.watchFor();
  CAN0.setCallback(0, canCallback);

  for (int i = 0; i < motors.MOTOR_NUM; i++) {
    motors.set_pid_rpm(i, 1.5, 0.01, 0); //set pid for each rm motors
    motors.reset_gearbox_pos(i); //reset the encoder position to 0
  }

  // xTaskCreatePinnedToCore(
  //   Task_cantx,
  //   "Task_cantx",
  //   2048,
  //   NULL,
  //   1,
  //   NULL,
  //   1);

}

void loop() {

  if (Serial.available() > 0) {
    // receive the input data from the serial
    rpm = Serial.parseInt();

    // position = Serial.parseInt();
    if (Serial.read() == '\n' );

  }
  motors.set_target_rpm(0, rpm); //set id 1 rm motors rpm 
  // motors.set_target_pos(0, position); //set id 1 rm motors position 
  Serial.println(motors.gearbox_pos[0]);
  send_can_frame();
  delay(20);
}


// void Task_cantx(void *paramter) {
//   for (;;) {
//     send_can_frame();
//     vTaskDelay(2 / portTICK_PERIOD_MS);
//   }
// }



