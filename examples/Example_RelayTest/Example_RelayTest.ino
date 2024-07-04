/***********************************************************************
 * Project      :     Example_RelayTest
 * Description  :     Test Relay on tiny32_v3 board
 * Hardware     :     tiny32_v3         
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     19/02/2022
 * Revision     :     1.1
 * Rev1.0       :     Initial
 * Rev1.1       :     Change message status between "ON" and "OFF"
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@tenergyinnovation.co.th
 * TEL          :     +66 89-140-7205
 ***********************************************************************/
#include <tiny32_v3.h>

tiny32_v3 mcu; //define object

void setup() {
  Serial.begin(115200);
  Serial.printf("\r\n**** Example_RelayTest ****\r\n");
  mcu.library_version();
}

void loop() {
  
  /**** one beep ****/
  Serial.printf("Relay => OFF\r\n");
  mcu.Relay(0); //NO disconnect COM  
  vTaskDelay(1000);

  /**** two beep ****/
  Serial.printf("Relay => ON\r\n");
  mcu.Relay(1); //NO connect COM
  vTaskDelay(1000);

  
}
