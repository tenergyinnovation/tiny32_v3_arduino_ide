/***********************************************************************
 * Project      :     Example_PWM_Test
 * Description  :     Test PWM for tiny32_v3, for drive DC motor or LED
 * Hardware     :     tiny32_v3         
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     19/02/2022
 * Revision     :     1.0
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@tenergyinnovation.co.th
 * TEL          :     +66 89-140-7205
 ***********************************************************************/
#include <tiny32_v3.h>

/* define parameter */
#define CHANNEL           0  //channel [0-15]
#define FREQ              5000 //freequency(Hz)
#define RESOLUTION_BIT    8  //Resolution [1-15 bit]
#define PWM_PIN           18 //pin on tiny32_v3

tiny32_v3 mcu; //define object

String Percentage=""; //global string variable


void setup() {
  Serial.begin(115200);
  Serial.printf("\r\n**** Example_PWM_Test ****\r\n");
  mcu.library_version();
  mcu.PWM_Setup(CHANNEL, FREQ, RESOLUTION_BIT, PWM_PIN); //initial function
}

void loop() {

    while(Serial.available()) //waiting percentage from serial
    {
      int inChar =Serial.read();
      if (isDigit(inChar)) 
      {
        Percentage += (char)inChar;
      }
      if (inChar == '\n') {
          int _percentage_int = Percentage.toInt();
      
          mcu.PWM_Drive(CHANNEL,_percentage_int);
          Serial.printf("PWM[%c] => %d\r\n",37,_percentage_int);
          Percentage = ""; //clear value
      }

    }

}
