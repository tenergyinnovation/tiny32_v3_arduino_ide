/***********************************************************************
 * Project      :     Example_rs485_Test
 * Description  :     Test rs485 port on tiny32_v3 board
 * Hardware     :     tiny32_v3         
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     19/02/2022
 * Revision     :     1.0
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     admin@innovation.co.th
 * TEL          :     +66 82-308-3299
 ***********************************************************************/
#include <tiny32_v3.h>

tiny32_v3 mcu; //define object
HardwareSerial RS485(1);

void setup() {
  Serial.begin(115200);
  RS485.begin(9600, SERIAL_8N1, 16, 17);
  Serial.printf("\r\n**** Example_rs485_Test ****\r\n");
  mcu.library_version();
}

void loop() {
  RS485.println("Hello World[RS485]"); //must connect rs485 port to rs485 to usb converter https://www.allnewstep.com/product/572/usb-to-rs485-usb-485-converter-adapter
  Serial.println("Hello World[Serial]");
  vTaskDelay(1000);

}
