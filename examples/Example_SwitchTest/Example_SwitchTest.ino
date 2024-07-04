/***********************************************************************
 * Project      :     Example_SwitchTest
 * Description  :     Test button and slid switch for tiny32_v3 board
 * Hardware     :     tiny32_v3         
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     19/02/2022
 * Revision     :     1.0
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@tenergyinnovation.co.th
 * TEL          :     +66 89-140-7205
 ***********************************************************************/
#include <tiny32_v3.h>

tiny32_v3 mcu; //define object

void setup() {
  Serial.begin(115200);
  Serial.printf("\r\n**** Example_SwitchTest ****\r\n");
  mcu.library_version();
}

void loop() {
  
  /**** read switch status ****/
  boolean _sw1 = mcu.Sw1();
  boolean _sw2 = mcu.Sw2();
  boolean _slidSw = mcu.Slid_sw();

  /**** Show switch status ****/
  Serial.printf("SW1 => %d\r\n",_sw1);
  Serial.printf("SW2 => %d\r\n",_sw2);
  Serial.printf("SLID SW => %d\r\n",_slidSw);
  Serial.println("------------------------");
  vTaskDelay(1000);
}
