/***********************************************************************
 * File         :     tiny32_v3.cpp
 * Description  :     Class for Hardware config and function for tiny32_v3 module
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     23 Nov 2021
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@innovation.co.th
 * TEL          :     089-140-7205
 ***********************************************************************/

#include "tiny32_v3.h"
#include "Arduino.h"
#include "Ticker.h"
#include "tiny32_v3_Lib.h"

Ticker tickerRedLED;
Ticker tickerBlueLED;
Ticker tickerBuilinLED;

// rs485
HardwareSerial rs485(1);
HardwareSerial rs485_2(1);

tiny32_v3::tiny32_v3()
{

  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SLID_SW, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_IO12, OUTPUT);
  pinMode(LED_IO4, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED_IO12, LOW);
  digitalWrite(LED_IO4, LOW);
  digitalWrite(BUZZER, LOW);
}

/***********************************************************************
 * FUNCTION:    library_version
 * DESCRIPTION: Print out library version
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void tiny32_v3::library_version(void)
{
  Serial.printf("library version: %s\r\n", version_c);
}

/***********************************************************************
 * FUNCTION:    Relay
 * DESCRIPTION: Control ON-OFF Relay[pin25]
 * PARAMETERS:  0 or 1
 * RETURNED:    nothing
 ***********************************************************************/
void tiny32_v3::Relay(bool state)
{
  digitalWrite(RELAY, state);
}

/***********************************************************************
 * FUNCTION:    RedLED
 * DESCRIPTION: ON-OFF Red LED[pin4]
 * PARAMETERS:  0 or 1
 * RETURNED:    nothing
 ***********************************************************************/
void tiny32_v3::BlueLED(bool state)
{
  digitalWrite(LED_IO4, state);
}

/***********************************************************************
 * FUNCTION:    BlueLED
 * DESCRIPTION: ON-OFF Blue LED[pin12]
 * PARAMETERS:  0 or 11
 * RETURNED:    nothing
 ***********************************************************************/
void tiny32_v3::RedLED(bool state)
{
  digitalWrite(LED_IO12, state);
}

/***********************************************************************
 * FUNCTION:    BlueinLED
 * DESCRIPTION: ON-OFF Bulidin LED[pin2]
 * PARAMETERS:  0 or 1
 * RETURNED:    nothing
 ***********************************************************************/
void tiny32_v3::BuildinLED(bool state)
{
  digitalWrite(LED_BUILTIN, state);
}

/***********************************************************************
 * FUNCTION:    buzzer_beep
 * DESCRIPTION: buzzer sound beep[pin13]
 * PARAMETERS:  times
 * RETURNED:    nothing
 ***********************************************************************/
void tiny32_v3::buzzer_beep(int times)
{
#define PLUSE_BUZZER
  // #define DC_BUZZER

  for (int _i = 0; _i < times; _i++)
  {
#ifdef PLUSE_BUZZER
#define dt 50 // 0.1sec

    int _j;
    for (_j = dt; _j > 0; _j--)
    {
      digitalWrite(BUZZER, HIGH);
      vTaskDelay(1);
      digitalWrite(BUZZER, LOW);
      vTaskDelay(1);
    }
    vTaskDelay(100);
#endif

#ifdef DC_BUZZER
    digitalWrite(BUZZER, HIGH);
    vTaskDelay(70);
    digitalWrite(BUZZER, LOW);
    vTaskDelay(70);
#endif
  }
}

/***********************************************************************
 * FUNCTION:    Sw1
 * DESCRIPTION: Read SW1[pin33]
 * PARAMETERS:  nothing
 * RETURNED:    0 or 1
 ***********************************************************************/
bool tiny32_v3::Sw1(void)
{
  bool _status = !digitalRead(SW1);
  return _status;
}

/***********************************************************************
 * FUNCTION:    Sw2
 * DESCRIPTION: Read SW2[pin14]
 * PARAMETERS:  nothing
 * RETURNED:    0 or 1
 ***********************************************************************/
bool tiny32_v3::Sw2(void)
{
  bool _status = !digitalRead(SW2);
  return _status;
}

/***********************************************************************
 * FUNCTION:    Slid_sw
 * DESCRIPTION: Read Slid Switch[15]
 * PARAMETERS:  nothing
 * RETURNED:    0 or 1
 ***********************************************************************/
bool tiny32_v3::Slid_sw(void)
{
  bool _status = !digitalRead(SLID_SW);
  return _status;
}

/***********************************************************************
 * FUNCTION:    TickBlueLED
 * DESCRIPTION: Blink BlueLED[pin4]
 * PARAMETERS:  nothing
 * RETURNED:    0 = Off, 1 < blink
 ***********************************************************************/
void tiny32_v3::TickBlueLED(float second)
{
  if (second <= 0)
  {
    tickerBlueLED.detach();
    BlueLED(0);
  }
  else
  {
    tickerBlueLED.attach(second, TickBlueLED_blink);
  }
}

/***********************************************************************
 * FUNCTION:    TickRedLED
 * DESCRIPTION: Blink RedLED[pin12]
 * PARAMETERS:  nothing
 * RETURNED:    0 = Off, 1 < blink
 ***********************************************************************/
void tiny32_v3::TickRedLED(float second)
{
  if (second <= 0)
  {
    tickerRedLED.detach();
    RedLED(0);
  }
  else
  {
    tickerRedLED.attach(second, TickRedLED_blink);
  }
}

/***********************************************************************
 * FUNCTION:    BuildinLED
 * DESCRIPTION: Blink BuildinLED[pin2]
 * PARAMETERS:  nothing
 * RETURNED:    0 = Off, 1 < blink
 ***********************************************************************/
void tiny32_v3::TickBuildinLED(float second)
{
  if (second <= 0)
  {
    tickerBuilinLED.detach();
    BuildinLED(0);
  }
  else
  {
    tickerBuilinLED.attach(second, TickBuildinLED_blink);
  }
}

/***********************************************************************
 * FUNCTION:    PWN_Setup
 * DESCRIPTION: Pulse Width Mod setting up
 * PARAMETERS:  channel[0-15], frequency(Hz), resolution[1-15], pin
 * RETURNED:    0 = error, 1 = pass
 ***********************************************************************/
bool tiny32_v3::PWM_Setup(uint8_t channel, double freq, uint8_t resolution_bit, uint8_t pin)
{
  //**** skip for support Aduino IDE *****/
  // if (channel > 15 || channel < 0 || resolution_bit > 15 || resolution_bit < 1)
  // {
  //   Serial.printf("Error: wrong parameter!!\r\n");
  //   return 0;
  // }
  // ledcSetup(channel, freq, resolution_bit);
  // ledcAttachPin(pin, channel);
  // _resolution_bit = resolution_bit;
  return 1;
}

/***********************************************************************
 * FUNCTION:    PWM_Drive
 * DESCRIPTION: Pulse Width Mod drive
 * PARAMETERS:  channel[0-15], percentage[0-100]
 * RETURNED:    0 = error, 1 = pass
 ***********************************************************************/
bool tiny32_v3::PWM_Drive(uint8_t channel, uint8_t percentage)
{
  double _duty = 0;

  if (percentage > 100 || percentage < 0)
  {
    Serial.printf("Error: Out of range parameter\r\n");
    return 0;
  }
  else
  {
    // Serial.printf("_resolution_bit = %d\r\n",_resolution_bit);
    // Serial.printf("percentage = %d\r\n",percentage);

    if (_resolution_bit == 1)
      _duty = (double)percentage * 0.02;
    else if (_resolution_bit == 2)
      _duty = (double)percentage * 0.04;
    else if (_resolution_bit == 3)
      _duty = (double)percentage * 0.08;
    else if (_resolution_bit == 4)
      _duty = (double)percentage * 0.16;
    else if (_resolution_bit == 5)
      _duty = (double)percentage * 0.32;
    else if (_resolution_bit == 6)
      _duty = (double)percentage * 0.64;
    else if (_resolution_bit == 7)
      _duty = (double)percentage * 1.28;
    else if (_resolution_bit == 8)
      _duty = (double)percentage * 2.56;
    else if (_resolution_bit == 9)
      _duty = (double)percentage * 5.12;
    else if (_resolution_bit == 10)
      _duty = (double)percentage * 10.24;
    else if (_resolution_bit == 11)
      _duty = (double)percentage * 20.48;
    else if (_resolution_bit == 12)
      _duty = (double)percentage * 40.96;
    else if (_resolution_bit == 13)
      _duty = (double)percentage * 81.92;
    else if (_resolution_bit == 14)
      _duty = (double)percentage * 163.84;
    else if (_resolution_bit == 15)
      _duty = (double)percentage * 327.68;

    ledcWrite(channel, _duty);
    // Serial.printf("Debug: duty = %f\r\n",_duty);
    return 1;
  }
}

/***********************************************************************
 * FUNCTION:    Frequency_Out
 * DESCRIPTION: Generate Frequency to pin 5,18,23,19 but else not allow
 * PARAMETERS:  pin=[5,18,23 and 19], freq=0-19500Hz
 * RETURNED:    0 = error, 1 = pass
 ***********************************************************************/
bool tiny32_v3::Frequency_Out(uint8_t pin, double freq)
{
  return 0;

   //**** skip for support Aduino IDE *****/

  // uint8_t _channel;

  // /* check pin */
  // if ((pin != 5) && (pin != 18) && (pin != 23) && (pin != 19))
  // {
  //   Serial.printf("Error: parameter input pin must be 5,18,23,19 but else is not allow\r\n");
  //   return 0;
  // }
  // else
  // {
  //   /* define channel */
  //   switch (pin)
  //   {
  //   case 5:
  //     _channel = 1;
  //     break;
  //   case 18:
  //     _channel = 3;
  //     break;
  //   case 23:
  //     _channel = 5;
  //     break;
  //   case 19:
  //     _channel = 7;
  //     break;
  //   default:
  //     break;
  //   }
  // }

  // /* check frequency */
  // if ((freq < 0) || (freq > 19500))
  // {
  //   Serial.printf("Error: Out of range frequency [0-19500Hz]\r\n");
  //   return 0;
  // }

  // /* set 0 Hz */
  // if (freq == 0)
  // {
  //   Serial.printf("Info: pin = %d, channel = %d, frequency = %.0fHz\r\n", pin, _channel, freq);
  //   ledcSetup(_channel, 1, 12);
  //   ledcAttachPin(pin, _channel);
  //   ledcWrite(pin, 0);
  //   vTaskDelay(300);
  //   return 1;
  // }
  // else
  // {
  //   Serial.printf("Info: pin = %d, channel = %d, frequency = %.0fHz\r\n", pin, _channel, freq);
  //   ledcSetup(_channel, freq, 12);
  //   ledcAttachPin(pin, _channel);
  //   ledcWrite(_channel, 4095 / 2);
  //   vTaskDelay(300);

  //   ledcSetup(_channel, freq, 12); //<- Fix bug by need to re-run command
  //   ledcAttachPin(pin, _channel);
  //   ledcWrite(_channel, 4095 / 2);
  //   vTaskDelay(300);
  //   return 1;
  // }
}

/***********************************************************************
 * FUNCTION:    TimeStamp_minute_encode
 * DESCRIPTION: number of days since 2000/01/01, valid for 2001..2099
 * PARAMETERS:  y, m, d, h, mi (Example: 2020,8,13,22,55)
 * RETURNED:    minute
 ***********************************************************************/
uint16_t tiny32_v3::TimeStamp_minute_encode(uint16_t y, uint8_t m, uint8_t d, uint8_t h, uint8_t mi)
{
  uint16_t _numberofdays;
  if (y >= 2000)
    y -= 2000;
  uint16_t days = d;
  for (uint8_t i = 1; i < m; ++i)
    days += pgm_read_byte(daysInMonth + i - 1);
  if (m > 2 && y % 4 == 0)
    ++days;
  _numberofdays = days + 365 * y + (y + 3) / 4 - 1;
  _numberofdays--;

  // Serial.printf("Debug: numberofminute = %d\r\n",(_numberofdays*24*60) + (h*60) + mi);
  return (_numberofdays * 24 * 60) + (h * 60) + mi;
}

/***********************************************************************
 * FUNCTION:    TimeStamp_24hr_encode
 * DESCRIPTION: Encoding time stamp
 * PARAMETERS:  h, mi (Example: 22,55)
 * RETURNED:    tempstamp
 ***********************************************************************/
uint16_t tiny32_v3::TimeStamp_24hr_encode(uint16_t h, uint16_t mi)
{
  return ((h * 60) + mi);
}

/***********************************************************************
 * FUNCTION:    TimeStamp_hour_minute_decode
 * DESCRIPTION: Decoding time stamp
 * PARAMETERS:  timestemp
 * RETURNED:    hour, minute
 ***********************************************************************/
void tiny32_v3::TimeStamp_hour_minute_decode(uint16_t timestemp, uint16_t &h, uint16_t &mi)
{
  h = timestemp / 60;
  mi = timestemp % 60;
}

/***********************************************************************
 * FUNCTION:    crc16_update
 * DESCRIPTION: CRC16 check
 * PARAMETERS:  uint16_t crc, uint8_t a
 * RETURNED:    uint16_t
 ***********************************************************************/
uint16_t tiny32_v3::crc16_update(uint16_t crc, uint8_t a)
{
  int i;

  crc ^= a;
  for (i = 0; i < 8; ++i)
  {
    if (crc & 1)
      crc = (crc >> 1) ^ 0xA001;
    else
      crc = (crc >> 1);
  }

  return crc;
}

/***********************************************************************
 * FUNCTION:    ec_modbusRTU
 * DESCRIPTION: EC sensor read
 * PARAMETERS:  address
 * RETURNED:    uS/cm
 ***********************************************************************/
uint16_t tiny32_v3::ec_modbusRTU(uint8_t id)
{
  // #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x01;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  if (_byte_cnt == 7)
  {
    _data_check[0] = _data_read[0];
    _data_check[1] = _data_read[1];
    _data_check[2] = _data_read[2];
    _data_check[3] = _data_read[3];
    _data_check[4] = _data_read[4];
    _data_check[5] = _data_read[5];
    _data_check[6] = _data_read[6];

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {
    _data_check[0] = _data_read[_byte_cnt - 7];
    _data_check[1] = _data_read[_byte_cnt - 6];
    _data_check[2] = _data_read[_byte_cnt - 5];
    _data_check[3] = _data_read[_byte_cnt - 4];
    _data_check[4] = _data_read[_byte_cnt - 3];
    _data_check[5] = _data_read[_byte_cnt - 2];
    _data_check[6] = _data_read[_byte_cnt - 1];

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
// Serial.printf("Debug: _crc = 0x%X\r\n",_crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {
    _temp_hex = _data_check[3];             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex = _temp_hex << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex = _temp_hex | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);

#ifdef modbusRTU_Debug
    Serial.printf("Debug: Return DATA => %.d\r\n", _temp_hex);
#endif

    return _temp_hex;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0xffff;
  }
}

/***********************************************************************
 * FUNCTION:    ec_modbusRTU_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::ec_modbusRTU_begin(uint8_t rx, uint8_t tx)
{
  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(9600, SERIAL_8N1, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_016
 * DESCRIPTION: Read value from PZEM-016 Modbus RTU power meter module
 * PARAMETERS:  address(id)
 * RETURNED:    true, false and reference parameter => volt, amp, power, energy, freq, pf
 ***********************************************************************/
bool tiny32_v3::PZEM_016(uint8_t id, float &volt, float &amp, float &power, uint32_t &energy, float &freq, float &pf)
{
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;
  uint32_t _temp_hex_32bit = 0x00000000;

  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[25];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x0A;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 25)
  {

    // Collect data
    for (int i = 0; i < 25; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 25)
  {

    uint8_t _addcnt = _byte_cnt - 25; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 25; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read volt ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    volt = (float)_temp_hex_16bit * 0.1;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: volt[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: volt[float] => %.1f\r\n", volt);
#endif

    //**** Read Current ****
    _temp_hex_32bit = 0x00000000; // clear buffer

    _temp_hex_16bit = _data_check[7];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[8]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _temp_hex_32bit = _temp_hex_32bit << 16;             // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);

    _temp_hex_16bit = _data_check[5];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[6]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit* = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    amp = (float)_temp_hex_32bit * 0.001;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: amp[hex] => %.d\r\n", _temp_hex_32bit);
    Serial.printf("Debug: amp[float] => %.1f\r\n", amp);
#endif

    //**** Read Power ****
    _temp_hex_32bit = 0x00000000; // clear buffer

    _temp_hex_16bit = _data_check[11];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[12]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _temp_hex_32bit = _temp_hex_32bit << 16;             // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);

    _temp_hex_16bit = _data_check[9];                    // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[10]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit* = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    power = (float)_temp_hex_32bit * 0.1;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: power[hex] => %.d\r\n", _temp_hex_32bit);
    Serial.printf("Debug: power[float] => %.1f\r\n", power);
#endif

    //**** Read Engergy ****
    _temp_hex_32bit = 0x00000000; // clear buffer

    _temp_hex_16bit = _data_check[15];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[16]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _temp_hex_32bit = _temp_hex_32bit << 16;             // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);

    _temp_hex_16bit = _data_check[13];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[14]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit* = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    energy = (float)_temp_hex_32bit;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: energy[hex] => %.d\r\n", _temp_hex_32bit);
    Serial.printf("Debug: energy[float] => %.1f\r\n", energy);
#endif

    //**** Read Frequency ****
    _temp_hex_16bit = _data_check[17];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[18]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    freq = (float)_temp_hex_16bit * 0.1;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: frequency[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: frequency[float] => %.1f\r\n", freq);
#endif

    //**** Read power factor ****
    _temp_hex_16bit = _data_check[19];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[20]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    pf = (float)_temp_hex_16bit * 0.01;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: Power factor[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: Power factor[float] => %.01f\r\n", pf);
#endif

    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_016_Volt
 * DESCRIPTION: Read value from PZEM-016 Modbus RTU power meter module
 * PARAMETERS:  address(id)
 * RETURNED:    volt
 ***********************************************************************/
float tiny32_v3::PZEM_016_Volt(uint8_t id)
{
  float _volt;
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[25];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x0A;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 25)
  {

    // Collect data
    for (int i = 0; i < 25; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 25)
  {

    uint8_t _addcnt = _byte_cnt - 25; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 25; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read volt ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    _volt = (float)_temp_hex_16bit * 0.1;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: volt[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: volt[float] => %.1f\r\n", _volt);
#endif

    return _volt;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_016_Amp
 * DESCRIPTION: Read value from PZEM-016 Modbus RTU power meter module
 * PARAMETERS:  address(id)
 * RETURNED:    amp
 ***********************************************************************/
float tiny32_v3::PZEM_016_Amp(uint8_t id)
{
  float _amp;
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;
  uint32_t _temp_hex_32bit = 0x00000000;

  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[25];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x0A;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 25)
  {

    // Collect data
    for (int i = 0; i < 25; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 25)
  {

    uint8_t _addcnt = _byte_cnt - 25; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 25; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read Current ****
    _temp_hex_32bit = 0x00000000; // clear buffer

    _temp_hex_16bit = _data_check[7];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[8]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _temp_hex_32bit = _temp_hex_32bit << 16;             // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);

    _temp_hex_16bit = _data_check[5];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[6]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit* = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _amp = (float)_temp_hex_32bit * 0.001;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: amp[hex] => %.d\r\n", _temp_hex_32bit);
    Serial.printf("Debug: amp[float] => %.1f\r\n", _amp);
#endif
    return _amp;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_016_Power
 * DESCRIPTION: Read value from PZEM-016 Modbus RTU power meter module
 * PARAMETERS:  address(id)
 * RETURNED:    power
 ***********************************************************************/
float tiny32_v3::PZEM_016_Power(uint8_t id)
{
  float _power;
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;
  uint32_t _temp_hex_32bit = 0x00000000;

  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[25];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x0A;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 25)
  {

    // Collect data
    for (int i = 0; i < 25; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 25)
  {

    uint8_t _addcnt = _byte_cnt - 25; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 25; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read Power ****
    _temp_hex_32bit = 0x00000000; // clear buffer

    _temp_hex_16bit = _data_check[11];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[12]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _temp_hex_32bit = _temp_hex_32bit << 16;             // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);

    _temp_hex_16bit = _data_check[9];                    // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[10]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit* = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _power = (float)_temp_hex_32bit * 0.1;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: power[hex] => %.d\r\n", _temp_hex_32bit);
    Serial.printf("Debug: power[float] => %.1f\r\n", _power);
#endif

    return _power;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_016_Energy
 * DESCRIPTION: Read value from PZEM-016 Modbus RTU power meter module
 * PARAMETERS:  address(id)
 * RETURNED:    energy
 ***********************************************************************/
int16_t tiny32_v3::PZEM_016_Energy(uint8_t id)
{

  uint16_t _energy;
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;
  uint32_t _temp_hex_32bit = 0x00000000;

  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[25];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x0A;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 25)
  {

    // Collect data
    for (int i = 0; i < 25; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 25)
  {

    uint8_t _addcnt = _byte_cnt - 25; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 25; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read Engergy ****
    _temp_hex_32bit = 0x00000000; // clear buffer

    _temp_hex_16bit = _data_check[15];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[16]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _temp_hex_32bit = _temp_hex_32bit << 16;             // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);

    _temp_hex_16bit = _data_check[13];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[14]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit* = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _energy = (float)_temp_hex_32bit * 1;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: energy[hex] => %.d\r\n", _temp_hex_32bit);
    Serial.printf("Debug: energy[float] => %.1f\r\n", _energy);
#endif

    return _energy;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_016_Freq
 * DESCRIPTION: Read value from PZEM-016 Modbus RTU power meter module
 * PARAMETERS:  address(id)
 * RETURNED:    freq
 ***********************************************************************/
float tiny32_v3::PZEM_016_Freq(uint8_t id)
{
  float _freq;
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[25];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x0A;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 25)
  {

    // Collect data
    for (int i = 0; i < 25; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 25)
  {

    uint8_t _addcnt = _byte_cnt - 25; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 25; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read Frequency ****
    _temp_hex_16bit = _data_check[17];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[18]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    _freq = (float)_temp_hex_16bit * 0.1;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: frequency[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: frequency[float] => %.1f\r\n", _freq);
#endif

    return _freq;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_016_PF
 * DESCRIPTION: Read value from PZEM-016 Modbus RTU power meter module
 * PARAMETERS:  address(id)
 * RETURNED:    pf
 ***********************************************************************/
float tiny32_v3::PZEM_016_PF(uint8_t id)
{
  float _pf;

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[25];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x0A;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 25)
  {

    // Collect data
    for (int i = 0; i < 25; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 25)
  {

    uint8_t _addcnt = _byte_cnt - 25; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 25; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read power factor ****
    _temp_hex_16bit = _data_check[19];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[20]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    _pf = (float)_temp_hex_16bit * 0.01;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: Power factor[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: Power factor[float] => %.01f\r\n", _pf);
#endif
    return _pf;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_016_ResetEnergy
 * DESCRIPTION: Reset Energy value for PZEM-016 Modbus RTU power meter module
 * PARAMETERS:  address(id)
 * RETURNED:    true, false
 ***********************************************************************/
bool tiny32_v3::PZEM_016_ResetEnergy(uint8_t id)
{
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;

  uint8_t _data_write[4];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[4];

  _data_write[0] = id;
  _data_write[1] = 0x42;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 4; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Byte count => %d\r\n", _byte_cnt);
#endif
  }

  if (_byte_cnt == 4)
  {

    /*header data*/
    _data_check[0] = _data_read[0];
    _data_check[1] = _data_read[1];
    _data_check[2] = _data_read[2];
    _data_check[3] = _data_read[3];

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  if (_byte_cnt > 4)
  {

    uint8_t _addcnt = _byte_cnt - 4;
    for (int i = 0; i < 4; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    Serial.printf("Info: PZEM-016 Reset Engergy Success\r\n");
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_016_SetAddress
 * DESCRIPTION: Reset Energy value for PZEM-016 Modbus RTU power meter module
 * PARAMETERS:  address id, new_id
 * RETURNED:   new_id
 ***********************************************************************/
int8_t tiny32_v3::PZEM_016_SetAddress(uint8_t id, uint8_t new_id)
{

  /*check parameter*/
  if (new_id >= 0x7F)
  {
    Serial.printf("Error: Address is out of the range[1-127]\r\n");
    return -1;
  }

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[8];

  _data_write[0] = id;
  _data_write[1] = 0x06;
  _data_write[2] = 0x00;
  _data_write[3] = 0x02;
  _data_write[4] = 0x00;
  _data_write[5] = new_id;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Byte Count = %d\r\n", _byte_cnt);
#endif
  }

  if (_byte_cnt == 8)
  {

    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 8)
  {

    uint8_t _addcnt = _byte_cnt - 8;
    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    Serial.printf("Info: Success to set new Address[%d]\r\n", new_id);
    return new_id;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_016_SearchAddress
 * DESCRIPTION: Search Address from PZEM-016 Modbus RTU power meter module
 * PARAMETERS:  nothing
 * RETURNED:    Address
 ***********************************************************************/
int8_t tiny32_v3::PZEM_016_SearchAddress(void)
{

  uint8_t _id;

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[25];

  /* Find ID from 1 to 127*/
  for (_id = 1; _id <= 127; _id++)
  {

    /*clear data*/
    _crc = 0xffff;
    _crc_r = 0xffff;
    _byte_cnt = 0;
    for (int i = 0; i < sizeof(_data_check); i++)
    {
      _data_read[i] = 0x00;
      _data_check[i] = 0x00;
    }

    _data_write[0] = _id;
    _data_write[1] = 0x04;
    _data_write[2] = 0x00;
    _data_write[3] = 0x00;
    _data_write[4] = 0x00;
    _data_write[5] = 0x0A;

    // Generate CRC16
    for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
    {
      _crc = crc16_update(_crc, _data_write[_i]);
    }

    // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
    Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
    _data_write[sizeof(_data_write) - 1] = _crc >> 8;
    _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data write(%d): [ ", sizeof(_data_write));
    for (byte _i = 0; _i < sizeof(_data_write); _i++)
    {
      if (_data_write[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_write[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_write[_i]);
      }
    }
    Serial.printf("]\r\n");
#endif
#pragma endregion

    /**** Write data ****/
    rs485.flush();
    for (int _i = 0; _i < 8; _i++)
      rs485.write(_data_write[_i]);

    vTaskDelay(300);

    /**** Read data ****/
    if (rs485.available())
    {

      for (byte _i = 0; _i < sizeof(_data_read); _i++)
        _data_read[_i] = 0x00; // clear buffer
      _byte_cnt = 0;

      // correct data
      do
      {
        _data_read[_byte_cnt++] = rs485.read();
        if (_data_read[0] == 0x00)
        { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
          _byte_cnt = 0;
        }
        // }while(rs485.available()>0);
      } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data read(%d): [ ", _byte_cnt);
      for (byte _i = 0; _i < _byte_cnt; _i++)
      {
        if (_data_read[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_read[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_read[_i]);
        }
      }
      Serial.println("]");
#endif
    }

    if (_byte_cnt == 25)
    {

      for (int i = 0; i < 25; i++)
      {
        _data_check[i] = _data_read[i];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this PZEM-016 => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
      }
    }

    else if (_byte_cnt > 25)
    {

      uint8_t _addcnt = _byte_cnt - 25; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง
      // Collect data
      for (int i = 0; i < 25; i++)
      {
        _data_check[i] = _data_read[i + _addcnt];
      }
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this PZEM-016 => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
      }
    }
    else
    {
      Serial.printf(".");
    }
  }

  Serial.printf("\r\nInfo: Finish searching .... Can't find PZEM-016 for this bus [fail]");
  return -1;
}

/***********************************************************************
 * FUNCTION:    PZEM_016_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::PZEM_016_begin(uint8_t rx, uint8_t tx)
{
  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(9600, SERIAL_8N1, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_003
 * DESCRIPTION: Read value from PZEM-003 Modbus RTU DC power meter module
 * PARAMETERS:  address(id)
 * RETURNED:    true, false and reference parameter => volt, amp, power, energy
 ***********************************************************************/
bool tiny32_v3::PZEM_003(uint8_t id, float &volt, float &amp, float &power, uint32_t &energy)
{
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;
  uint32_t _temp_hex_32bit = 0x00000000;

  uint8_t _data_write[8];
  // uint8_t _data_read[21];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[21];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x08;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485_2.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485_2.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485_2.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485_2.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485_2.available()>0);
    } while (rs485_2.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 21)
  {

    // Collect data
    for (int i = 0; i < 21; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 21)
  {

    uint8_t _addcnt = _byte_cnt - 21; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 21; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read volt ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    volt = (float)_temp_hex_16bit * 0.01;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: volt[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: volt[float] => %.1f\r\n", volt);
#endif

    //**** Read current ****
    _temp_hex_16bit = _data_check[5];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[6]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    amp = (float)_temp_hex_16bit * 0.01;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: amp[hex] => %.d\r\n", _temp_hex_32bit);
    Serial.printf("Debug: amp[float] => %.1fA\r\n", amp);
#endif

    //**** Read Power ****
    _temp_hex_32bit = 0x00000000; // clear buffer

    _temp_hex_16bit = _data_check[9];                    // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[10]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _temp_hex_32bit = _temp_hex_32bit << 16;             // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);

    _temp_hex_16bit = _data_check[7];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[8]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit* = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    power = (float)_temp_hex_32bit * 0.1;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: power[hex] => %.d\r\n", _temp_hex_32bit);
    Serial.printf("Debug: power[float] => %.1f\r\n", power);
#endif

    //**** Read Engergy ****
    _temp_hex_32bit = 0x00000000; // clear buffer

    _temp_hex_16bit = _data_check[13];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[14]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _temp_hex_32bit = _temp_hex_32bit << 16;             // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);

    _temp_hex_16bit = _data_check[11];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[12]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit* = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    energy = _temp_hex_32bit;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: energy[hex] => %.d\r\n", _temp_hex_32bit);
    Serial.printf("Debug: energy[float] => %d\r\n", energy);
#endif

    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_003_Volt
 * DESCRIPTION: Read value from PZEM-003 Modbus RTU DC power meter module
 * PARAMETERS:  address(id)
 * RETURNED:    volt
 ***********************************************************************/
float tiny32_v3::PZEM_003_Volt(uint8_t id)
{
  float _volt;
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;
  uint32_t _temp_hex_32bit = 0x00000000;

  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[21];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x08;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485_2.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485_2.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485_2.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485_2.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485_2.available()>0);
    } while (rs485_2.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 21)
  {

    // Collect data
    for (int i = 0; i < 21; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 21)
  {

    uint8_t _addcnt = _byte_cnt - 21; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 21; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read volt ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    _volt = (float)_temp_hex_16bit * 0.01;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: volt[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: volt[float] => %.1f\r\n", _volt);
#endif

    return _volt;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_003_Amp
 * DESCRIPTION: Read value from PZEM-003 Modbus RTU DC power meter module
 * PARAMETERS:  address(id)
 * RETURNED:    amp
 ***********************************************************************/
float tiny32_v3::PZEM_003_Amp(uint8_t id)
{
  float _amp;
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;
  uint32_t _temp_hex_32bit = 0x00000000;

  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[21];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x08;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485_2.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485_2.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485_2.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485_2.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485_2.available()>0);
    } while (rs485_2.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 21)
  {

    // Collect data
    for (int i = 0; i < 21; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 21)
  {

    uint8_t _addcnt = _byte_cnt - 21; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 21; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read current ****
    _temp_hex_16bit = _data_check[5];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[6]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    _amp = (float)_temp_hex_16bit * 0.01;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: amp[hex] => %.d\r\n", _temp_hex_32bit);
    Serial.printf("Debug: amp[float] => %.1fA\r\n", _amp);
#endif

    return _amp;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_003_Power
 * DESCRIPTION: Read value from PZEM-003 Modbus RTU DC power meter module
 * PARAMETERS:  address(id)
 * RETURNED:    power
 ***********************************************************************/
float tiny32_v3::PZEM_003_Power(uint8_t id)
{
  float _power;
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;
  uint32_t _temp_hex_32bit = 0x00000000;

  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[21];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x08;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485_2.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485_2.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485_2.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485_2.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485_2.available()>0);
    } while (rs485_2.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 21)
  {

    // Collect data
    for (int i = 0; i < 21; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 21)
  {

    uint8_t _addcnt = _byte_cnt - 21; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 21; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read Power ****
    _temp_hex_32bit = 0x00000000; // clear buffer

    _temp_hex_16bit = _data_check[9];                    // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[10]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _temp_hex_32bit = _temp_hex_32bit << 16;             // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);

    _temp_hex_16bit = _data_check[7];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[8]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit* = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _power = (float)_temp_hex_32bit * 0.1;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: power[hex] => %.d\r\n", _temp_hex_32bit);
    Serial.printf("Debug: power[float] => %.1f\r\n", _power);
#endif

    return _power;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_003_Energy
 * DESCRIPTION: Read value from PZEM-003 Modbus RTU DC power meter module
 * PARAMETERS:  address(id)
 * RETURNED:    energy
 ***********************************************************************/
int16_t tiny32_v3::PZEM_003_Energy(uint8_t id)
{
  uint16_t _energy;
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;
  uint32_t _temp_hex_32bit = 0x00000000;

  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[21];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x08;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485_2.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485_2.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485_2.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485_2.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485_2.available()>0);
    } while (rs485_2.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 21)
  {

    // Collect data
    for (int i = 0; i < 21; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 21)
  {

    uint8_t _addcnt = _byte_cnt - 21; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 21; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read Engergy ****
    _temp_hex_32bit = 0x00000000; // clear buffer

    _temp_hex_16bit = _data_check[13];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[14]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _temp_hex_32bit = _temp_hex_32bit << 16;             // Serial.printf("Debug: _temp_hex_32bit = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);

    _temp_hex_16bit = _data_check[11];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;              // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[12]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);

    _temp_hex_32bit = _temp_hex_32bit | _temp_hex_16bit; // Serial.printf("Debug: _temp_hex_32bit* = 0x%X(%d)\r\n",_temp_hex_32bit,_temp_hex_32bit);
    _energy = _temp_hex_32bit;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: energy[hex] => %.d\r\n", _temp_hex_32bit);
    Serial.printf("Debug: _energy[float] => %d\r\n", _energy);
#endif

    return _energy;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_003_ResetEnergy
 * DESCRIPTION: Reset Energy value for PZEM-003 Modbus RTU power meter module
 * PARAMETERS:  address(id)
 * RETURNED:    true, false
 ***********************************************************************/
bool tiny32_v3::PZEM_003_ResetEnergy(uint8_t id)
{
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;

  uint8_t _data_write[4];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[4];

  _data_write[0] = id;
  _data_write[1] = 0x42;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485_2.flush();
  for (int _i = 0; _i < 4; _i++)
    rs485_2.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485_2.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485_2.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485_2.available()>0);
    } while (rs485_2.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Byte Count => %d\r\n", _byte_cnt);
#endif
  }

  if (_byte_cnt == 4)
  {

    /*header data*/
    _data_check[0] = _data_read[0];
    _data_check[1] = _data_read[1];
    _data_check[2] = _data_read[2];
    _data_check[3] = _data_read[3];

    for (int i = 0; i < _byte_cnt; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 4)
  {
    uint8_t _addcnt = _byte_cnt - 4;
    for (int i = 0; i < 4; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    Serial.printf("Info: PZEM-003 Reset Engergy Success\r\n");
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_003_SetAddress
 * DESCRIPTION: Reset Energy value for PZEM-003 Modbus RTU power meter module
 * PARAMETERS:  address id, new_id
 * RETURNED:   new_id
 ***********************************************************************/
int8_t tiny32_v3::PZEM_003_SetAddress(uint8_t id, uint8_t new_id)
{

  /*check parameter*/
  if (new_id >= 0x7F)
  {
    Serial.printf("Error: Address is out of the range[1-127]\r\n");
    return -1;
  }

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[8];

  _data_write[0] = id;
  _data_write[1] = 0x06;
  _data_write[2] = 0x00;
  _data_write[3] = 0x02;
  _data_write[4] = 0x00;
  _data_write[5] = new_id;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485_2.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485_2.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485_2.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485_2.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485_2.available()>0);
    } while (rs485_2.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Byte count = %d\r\n", _byte_cnt);
#endif
  }

  if (_byte_cnt == 8)
  {

    _data_check[0] = _data_read[0];
    _data_check[1] = _data_read[1];
    _data_check[2] = _data_read[2];

    _data_check[3] = _data_read[3];
    _data_check[4] = _data_read[4];

    _data_check[5] = _data_read[5];
    _data_check[6] = _data_read[6];
    _data_check[7] = _data_read[7];

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 8)
  {
    uint8_t _addcnt = _byte_cnt - 8;
    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    Serial.printf("Info: Success to set new Address[%d]\r\n", new_id);
    return new_id;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PZEM_003_SearchAddress
 * DESCRIPTION: Search Address from PZEM-003 Modbus RTU power meter module
 * PARAMETERS:  nothing
 * RETURNED:    Address
 ***********************************************************************/

int8_t tiny32_v3::PZEM_003_SearchAddress(void)
{

  uint8_t _id;

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[21];

  /* Find ID from 1 to 127*/
  for (_id = 1; _id <= 127; _id++)
  {

    /*clear data*/
    _crc = 0xffff;
    _crc_r = 0xffff;
    _byte_cnt = 0;
    for (int i = 0; i < sizeof(_data_check); i++)
    {
      _data_read[i] = 0x00;
      _data_check[i] = 0x00;
    }

    _data_write[0] = _id;
    _data_write[1] = 0x04;
    _data_write[2] = 0x00;
    _data_write[3] = 0x00;
    _data_write[4] = 0x00;
    _data_write[5] = 0x08;

    // Generate CRC16
    for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
    {
      _crc = crc16_update(_crc, _data_write[_i]);
    }

    // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
    Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
    _data_write[sizeof(_data_write) - 1] = _crc >> 8;
    _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data write(%d): [ ", sizeof(_data_write));
    for (byte _i = 0; _i < sizeof(_data_write); _i++)
    {
      if (_data_write[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_write[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_write[_i]);
      }
    }
    Serial.printf("]\r\n");
#endif
#pragma endregion

    /**** Write data ****/
    rs485_2.flush();
    for (int _i = 0; _i < 8; _i++)
      rs485_2.write(_data_write[_i]);

    vTaskDelay(300);

    /**** Read data ****/
    if (rs485_2.available())
    {

      for (byte _i = 0; _i < sizeof(_data_read); _i++)
        _data_read[_i] = 0x00; // clear buffer
      _byte_cnt = 0;

      // correct data
      do
      {
        _data_read[_byte_cnt++] = rs485_2.read();
        if (_data_read[0] == 0x00)
        { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
          _byte_cnt = 0;
        }
        // }while(rs485_2.available()>0);
      } while (rs485_2.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data read(%d): [ ", _byte_cnt);
      for (byte _i = 0; _i < _byte_cnt; _i++)
      {
        if (_data_read[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_read[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_read[_i]);
        }
      }
      Serial.println("]");
#endif
    }

    /* Collect data to variable buffer */
    if (_byte_cnt == 21)
    {

      for (int i = 0; i < 21; i++)
      {
        _data_check[i] = _data_read[i];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this PZEM-003 => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }

    else if (_byte_cnt > 21)
    {

      uint8_t _addcnt = _byte_cnt - 21; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

      // Collect data
      for (int i = 0; i < 21; i++)
      {
        _data_check[i] = _data_read[i + _addcnt];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this PZEM-003 => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }
    else
    {
      Serial.printf(".");
    }
  }

  Serial.printf("\r\nInfo: Finish searching .... Can't find PZEM-003 for this bus [fail]");
}

/***********************************************************************
 * FUNCTION:    PZEM_003_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::PZEM_003_begin(uint8_t rx, uint8_t tx)
{
  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485_2.begin(9600, SERIAL_8N2, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    WTR10_E_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::WTR10_E_begin(uint8_t rx, uint8_t tx)
{
  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(9600, SERIAL_8N1, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    WTR10_E
 * DESCRIPTION: Read value from WTR10-E
 * PARAMETERS:  address(id)
 * RETURNED:    true, false and reference parameter => temp, humidity
 ***********************************************************************/
bool tiny32_v3::WTR10_E(uint8_t id, float &temp, float &humi)
{
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 9)
  {

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 9)
  {

    uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    temp = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temp[float] => %.1f\r\n", temp);
#endif

    //**** Read Humidity ****
    _temp_hex_16bit = _data_check[5];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[6]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    humi = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: humi[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: humi[float] => %.1f\r\n", humi);
#endif

    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    WTR10_E_tempeature
 * DESCRIPTION: Read tempeature from WTR10-E
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::WTR10_E_tempeature(uint8_t id)
{
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 9)
  {

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 9)
  {

    uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    WTR10_E_humidity
 * DESCRIPTION: Read humidity from WTR10-E
 * PARAMETERS:  address(id)
 * RETURNED:    _humidity
 ***********************************************************************/
float tiny32_v3::WTR10_E_humidity(uint8_t id)
{
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  float _humdity;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 9)
  {

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 9)
  {

    uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read Humidity ****
    _temp_hex_16bit = _data_check[5];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[6]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    _humdity = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: humi[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: humi[float] => %.1f\r\n", _humdity);
#endif

    return _humdity; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    XY_MD02_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::XY_MD02_begin(uint8_t rx, uint8_t tx)
{
  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(9600, SERIAL_8N2, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    XY_MD02
 * DESCRIPTION: Read value from XY-MD02
 * PARAMETERS:  address(id)
 * RETURNED:    true, false and reference parameter => temp, humidity
 ***********************************************************************/
bool tiny32_v3::XY_MD02(uint8_t id, float &temp, float &humi)
{
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x01;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 9)
  {

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 9)
  {

    uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    temp = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temp[float] => %.1f\r\n", temp);
#endif

    //**** Read Humidity ****
    _temp_hex_16bit = _data_check[5];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[6]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    humi = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: humi[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: humi[float] => %.1f\r\n", humi);
#endif

    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    XY_MD02_tempeature
 * DESCRIPTION: Read tempeature from XY-MD02
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::XY_MD02_tempeature(uint8_t id)
{
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x01;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 9)
  {

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 9)
  {

    uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    XY_MD02_humidity
 * DESCRIPTION: Read humidity from XY-MD02
 * PARAMETERS:  address(id)
 * RETURNED:    _humidity
 ***********************************************************************/
float tiny32_v3::XY_MD02_humidity(uint8_t id)
{
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x01;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  float _humdity;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 9)
  {

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 9)
  {

    uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read Humidity ****
    _temp_hex_16bit = _data_check[5];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[6]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    _humdity = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: humi[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: humi[float] => %.1f\r\n", _humdity);
#endif

    return _humdity; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    XY_MD02_searchAddress
 * DESCRIPTION: Search Address from XY-MD02 Module [1-247]
 * PARAMETERS:  nothing
 * RETURNED:    Address
 ***********************************************************************/

int8_t tiny32_v3::XY_MD02_searchAddress(void)
{

  uint8_t _id;

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[8];

  /* Find ID from 1 to 247*/
  for (_id = 1; _id <= 247; _id++)
  {

    /*clear data*/
    _crc = 0xffff;
    _crc_r = 0xffff;
    _byte_cnt = 0;
    for (int i = 0; i < sizeof(_data_check); i++)
    {
      _data_read[i] = 0x00;
      _data_check[i] = 0x00;
    }

    _data_write[0] = _id;
    _data_write[1] = 0x03;
    _data_write[2] = 0x01;
    _data_write[3] = 0x01;
    _data_write[4] = 0x00;
    _data_write[5] = 0x01;

    // Generate CRC16
    for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
    {
      _crc = crc16_update(_crc, _data_write[_i]);
    }

    // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
    Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
    _data_write[sizeof(_data_write) - 1] = _crc >> 8;
    _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data write(%d): [ ", sizeof(_data_write));
    for (byte _i = 0; _i < sizeof(_data_write); _i++)
    {
      if (_data_write[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_write[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_write[_i]);
      }
    }
    Serial.printf("]\r\n");
#endif
#pragma endregion

    /**** Write data ****/
    rs485.flush();
    for (int _i = 0; _i < 8; _i++)
      rs485.write(_data_write[_i]);

    vTaskDelay(300);

    /**** Read data ****/
    if (rs485.available())
    {

      for (byte _i = 0; _i < sizeof(_data_read); _i++)
        _data_read[_i] = 0x00; // clear buffer
      _byte_cnt = 0;

      // correct data
      do
      {
        _data_read[_byte_cnt++] = rs485.read();
        if (_data_read[0] == 0x00)
        { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
          _byte_cnt = 0;
        }
        // }while(rs485.available()>0);
      } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data read(%d): [ ", _byte_cnt);
      for (byte _i = 0; _i < _byte_cnt; _i++)
      {
        if (_data_read[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_read[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_read[_i]);
        }
      }
      Serial.println("]");
#endif
    }

    /* Collect data to variable buffer */
    if (_byte_cnt == 7)
    {

      for (int i = 0; i < 7; i++)
      {
        _data_check[i] = _data_read[i];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this XY-MD02 => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }

    else if (_byte_cnt > 7)
    {

      uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

      // Collect data
      for (int i = 0; i < 7; i++)
      {
        _data_check[i] = _data_read[i + _addcnt];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this XY-MD02 => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }
    else
    {
      Serial.printf(".");
    }
  }

  Serial.printf("\r\nInfo: Finish searching .... Can't find XY-MD02 for this bus [fail]");
}

/***********************************************************************
 * FUNCTION:    XY_MD02_SetAddress
 * DESCRIPTION: Setting new address to XY-MD02 Module
 * PARAMETERS:  address id, new_id
 * RETURNED:   new_id
 ***********************************************************************/
int8_t tiny32_v3::XY_MD02_SetAddress(uint8_t id, uint8_t new_id)
{

  /*check parameter*/
  if ((new_id < 1) || (new_id >= 247))
  {
    Serial.printf("Error: Address is out of the range[1-247]\r\n");
    return -1;
  }

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[8];

  _data_write[0] = id;
  _data_write[1] = 0x06;
  _data_write[2] = 0x01;
  _data_write[3] = 0x01;
  _data_write[4] = 0x00;
  _data_write[5] = new_id;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Byte Count = %d\r\n", _byte_cnt);
#endif
  }

  if (_byte_cnt == 8)
  {

    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 8)
  {

    uint8_t _addcnt = _byte_cnt - 8;
    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    Serial.printf("Info: Success to set new Address[%d]\r\n", new_id);
    return new_id;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PR3000_H_N01_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::PR3000_H_N01_begin(uint8_t rx, uint8_t tx)
{
  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(4800, SERIAL_8N1, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    PR3000_H_N01
 * DESCRIPTION: Read Temperature and Humidity soil
 * PARAMETERS:  nothing
 * RETURNED:    true, false and reference parameter => temp, humidity
 ***********************************************************************/
bool tiny32_v3::PR3000_H_N01(float &temp, float &humi)
{

  uint8_t id = 1; // fix id

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 9)
  {

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 9)
  {

    uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read Humidity ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    humi = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temp[float] => %.1f\r\n", temp);
#endif

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[5];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[6]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    temp = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: humi[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: humi[float] => %.1f\r\n", humi);
#endif

    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    PR3000_H_N01_tempeature
 * DESCRIPTION: Read Humidity soil
 * PARAMETERS:  nothing
 * RETURNED:    Humidity
 ***********************************************************************/
float tiny32_v3::PR3000_H_N01_tempeature()
{
  uint8_t id = 1;
  float _temp, _humi;
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 9)
  {

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 9)
  {

    uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read Humidity ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _humi = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temp[float] => %.1f\r\n", temp);
#endif

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[5];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[6]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    _temp = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: humi[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: humi[float] => %.1f\r\n", humi);
#endif

    return _temp;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PR3000_H_N01_humidity
 * DESCRIPTION: Read Humidity soil
 * PARAMETERS:  nothing
 * RETURNED:    humidity
 ***********************************************************************/
float tiny32_v3::PR3000_H_N01_humidity()
{
  uint8_t id = 1;
  float _temp, _humi;
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 9)
  {

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 9)
  {

    uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read Humidity ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _humi = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temp[float] => %.1f\r\n", temp);
#endif

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[5];                   // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex_16bit = 0x%X\r\n",_temp_hex_16bit);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[6]; // Serial.printf("Debug: _temp_hex_16bit = 0x%X(%d)\r\n",_temp_hex_16bit,_temp_hex_16bit);
    _temp = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: humi[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: humi[float] => %.1f\r\n", humi);
#endif

    return _humi;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    WATER_FLOW_METER_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::WATER_FLOW_METER_begin(uint8_t rx, uint8_t tx)
{

  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(9600, SERIAL_8N1, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    WATER_FLOW_METER_searchAddress
 * DESCRIPTION: Search Address from WATER_FLOW_METER Module [1-252]
 * PARAMETERS:  nothing
 * RETURNED:    Address
 ***********************************************************************/
int8_t tiny32_v3::WATER_FLOW_METER_searchAddress(void)
{
  uint8_t _id;

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[8];

  /* Find ID from 1 to 252*/
  for (_id = 1; _id <= 252; _id++)
  {

    /*clear data*/
    _crc = 0xffff;
    _crc_r = 0xffff;
    _byte_cnt = 0;
    for (int i = 0; i < sizeof(_data_check); i++)
    {
      _data_read[i] = 0x00;
      _data_check[i] = 0x00;
    }

    _data_write[0] = _id;
    _data_write[1] = 0x03;
    _data_write[2] = 0x00;
    _data_write[3] = 0x00;
    _data_write[4] = 0x00;
    _data_write[5] = 0x01;

    // Generate CRC16
    for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
    {
      _crc = crc16_update(_crc, _data_write[_i]);
    }

    // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
    Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
    _data_write[sizeof(_data_write) - 1] = _crc >> 8;
    _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data write(%d): [ ", sizeof(_data_write));
    for (byte _i = 0; _i < sizeof(_data_write); _i++)
    {
      if (_data_write[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_write[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_write[_i]);
      }
    }
    Serial.printf("]\r\n");
#endif
#pragma endregion

    /**** Write data ****/
    rs485.flush();
    for (int _i = 0; _i < 8; _i++)
      rs485.write(_data_write[_i]);

    vTaskDelay(300);

    /**** Read data ****/
    if (rs485.available())
    {

      for (byte _i = 0; _i < sizeof(_data_read); _i++)
        _data_read[_i] = 0x00; // clear buffer
      _byte_cnt = 0;

      // correct data
      do
      {
        _data_read[_byte_cnt++] = rs485.read();
        if (_data_read[0] == 0x00)
        { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
          _byte_cnt = 0;
        }
        // }while(rs485.available()>0);
      } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data read(%d): [ ", _byte_cnt);
      for (byte _i = 0; _i < _byte_cnt; _i++)
      {
        if (_data_read[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_read[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_read[_i]);
        }
      }
      Serial.println("]");
#endif
    }

    /* Collect data to variable buffer */
    if (_byte_cnt == 7)
    {

      for (int i = 0; i < 7; i++)
      {
        _data_check[i] = _data_read[i];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this WATER-FLOW-METER => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }

    else if (_byte_cnt > 7)
    {

      uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

      // Collect data
      for (int i = 0; i < 7; i++)
      {
        _data_check[i] = _data_read[i + _addcnt];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this WATER-FLOW-METER => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }
    else
    {
      Serial.printf(".");
    }
  }

  Serial.printf("\r\nInfo: Finish searching .... Can't find WATER-FLOW-METER for this bus [fail]");
}

/***********************************************************************
 * FUNCTION:    WATER_FLOW_METER_setAddress
 * DESCRIPTION: Set Address for WATER_FLOW_METER Module [1-252]
 * PARAMETERS:  id, new_id
 * RETURNED:    Address
 ***********************************************************************/
int8_t tiny32_v3::WATER_FLOW_METER_SetAddress(uint8_t id, uint8_t new_id)
{

  /*check parameter*/
  if ((new_id < 1) || (new_id >= 252))
  {
    Serial.printf("Error: Address is out of the range[1-252]\r\n");
    return -1;
  }

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[8];

  _data_write[0] = id;
  _data_write[1] = 0x06;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = new_id;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Byte Count = %d\r\n", _byte_cnt);
#endif
  }

  if (_byte_cnt == 8)
  {

    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 8)
  {

    uint8_t _addcnt = _byte_cnt - 8;
    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    Serial.printf("Info: Success to set new Address[%d]\r\n", new_id);
    return new_id;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    WATER_FLOW_METER
 * DESCRIPTION: get value from water flow meter (0.01m^2)
 * PARAMETERS:  id
 * RETURNED:    Flow water(m^3) cubic meters
 ***********************************************************************/
float tiny32_v3::WATER_FLOW_METER(uint8_t id)
{
  // #define modbusRTU_Debug
  float _flowrate;
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[11];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x03;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 11)
  {

    // Collect data
    for (int i = 0; i < 11; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 11)
  {

    uint8_t _addcnt = _byte_cnt - 11; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read Humidity ****
    _temp_hex_16bit = _data_check[7];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[8]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _flowrate = (float)_temp_hex_16bit / 100;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp => %d\r\n", _temp_hex_16bit);
#endif

    return _flowrate;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PYR20_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::PYR20_begin(uint8_t rx, uint8_t tx)
{

  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(9600, SERIAL_8N1, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    PYR20_searchAddress
 * DESCRIPTION: Search Address from PYR20 Module [1-255]
 * PARAMETERS:  nothing
 * RETURNED:    Address
 ***********************************************************************/
int8_t tiny32_v3::PYR20_searchAddress(void)
{
  uint8_t _id;

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[8];

  /* Find ID from 1 to 252*/
  for (_id = 1; _id <= 255; _id++)
  {

    /*clear data*/
    _crc = 0xffff;
    _crc_r = 0xffff;
    _byte_cnt = 0;
    for (int i = 0; i < sizeof(_data_check); i++)
    {
      _data_read[i] = 0x00;
      _data_check[i] = 0x00;
    }

    _data_write[0] = _id;
    _data_write[1] = 0x03;
    _data_write[2] = 0x02;
    _data_write[3] = 0x00;
    _data_write[4] = 0x00;
    _data_write[5] = 0x01;

    // Generate CRC16
    for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
    {
      _crc = crc16_update(_crc, _data_write[_i]);
    }

    // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
    Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
    _data_write[sizeof(_data_write) - 1] = _crc >> 8;
    _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data write(%d): [ ", sizeof(_data_write));
    for (byte _i = 0; _i < sizeof(_data_write); _i++)
    {
      if (_data_write[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_write[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_write[_i]);
      }
    }
    Serial.printf("]\r\n");
#endif
#pragma endregion

    /**** Write data ****/
    rs485.flush();
    for (int _i = 0; _i < 8; _i++)
      rs485.write(_data_write[_i]);

    vTaskDelay(300);

    /**** Read data ****/
    if (rs485.available())
    {

      for (byte _i = 0; _i < sizeof(_data_read); _i++)
        _data_read[_i] = 0x00; // clear buffer
      _byte_cnt = 0;

      // correct data
      do
      {
        _data_read[_byte_cnt++] = rs485.read();
        if (_data_read[0] == 0x00)
        { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
          _byte_cnt = 0;
        }
        // }while(rs485.available()>0);
      } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data read(%d): [ ", _byte_cnt);
      for (byte _i = 0; _i < _byte_cnt; _i++)
      {
        if (_data_read[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_read[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_read[_i]);
        }
      }
      Serial.println("]");
#endif
    }

    /* Collect data to variable buffer */
    if (_byte_cnt == 7)
    {

      for (int i = 0; i < 7; i++)
      {
        _data_check[i] = _data_read[i];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this WATER-FLOW-METER => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }

    else if (_byte_cnt > 7)
    {

      uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

      // Collect data
      for (int i = 0; i < 7; i++)
      {
        _data_check[i] = _data_read[i + _addcnt];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this WATER-FLOW-METER => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }
    else
    {
      Serial.printf(".");
    }
  }

  Serial.printf("\r\nInfo: Finish searching .... Can't find WATER-FLOW-METER for this bus [fail]");
}

/***********************************************************************
 * FUNCTION:    PYR20_setAddress
 * DESCRIPTION: Set Address for PYR20 Module [1-252]
 * PARAMETERS:  id, new_id
 * RETURNED:    Address
 ***********************************************************************/
int8_t tiny32_v3::PYR20_SetAddress(uint8_t id, uint8_t new_id)
{

  /*check parameter*/
  if ((new_id < 1) || (new_id >= 252))
  {
    Serial.printf("Error: Address is out of the range[1-252]\r\n");
    return -1;
  }

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[8];

  _data_write[0] = id;
  _data_write[1] = 0x06;
  _data_write[2] = 0x02;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = new_id;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Byte Count = %d\r\n", _byte_cnt);
#endif
  }

  if (_byte_cnt == 8)
  {

    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 8)
  {

    uint8_t _addcnt = _byte_cnt - 8;
    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    Serial.printf("Info: Success to set new Address[%d]\r\n", new_id);
    return new_id;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    PYR20_read
 * DESCRIPTION: read value from PYR20
 * PARAMETERS:  id
 * RETURNED:    W/m^2
 ***********************************************************************/
int16_t tiny32_v3::PYR20_read(uint8_t id)
{
  // #define modbusRTU_Debug
  uint16_t _pyranormeter;
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[10];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _pyranormeter = _temp_hex_16bit;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp => %d\r\n", _temp_hex_16bit);
#endif

    return _pyranormeter;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_ModbusRTU_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::tiny32_ModbusRTU_begin(uint8_t rx, uint8_t tx)
{
  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(9600, SERIAL_8N1, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_ModbusRTU
 * DESCRIPTION: tiny32 sensor read
 * PARAMETERS:  address
 * RETURNED:    referance variable [1-10]
 ***********************************************************************/
bool tiny32_v3::tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8, float &val9, float &val10)
{
  // #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[45];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x14;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 45)
  {

    // Collect data
    for (int i = 0; i <= 44; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 45)
  {

    uint8_t _addcnt = _byte_cnt - 45; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
// Serial.printf("Debug: _crc = 0x%X\r\n",_crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* val1 process */
    _sResult = _data_check[5];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[3]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val1 = (*(float *)&_sResult);         //**Floating point 16bit convert

    /* val2 process */
    _sResult = _data_check[9];             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[10]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[7];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[8];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    val2 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val3 process */
    _sResult = _data_check[13];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[14]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[11]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[12]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val3 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val4 process */
    _sResult = _data_check[17];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[18]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[15]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[16]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val4 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val5 process */
    _sResult = _data_check[21];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[22]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[19]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[20]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val5 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val6 process */
    _sResult = _data_check[25];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[26]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[23]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[24]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val6 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val7 process */
    _sResult = _data_check[29];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[30]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[27]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[28]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val7 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val8 process */
    _sResult = _data_check[33];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[34]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[31]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[32]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val8 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val9 process */
    _sResult = _data_check[37];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[38]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[35]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[36]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val9 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val10 process */
    _sResult = _data_check[41];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[42]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[39]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[40]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val10 = (*(float *)&_sResult);         //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", val1);
    Serial.printf("Debug: val2 => %.2f\r\n", val2);
    Serial.printf("Debug: val3 => %.2f\r\n", val3);
    Serial.printf("Debug: val4 => %.2f\r\n", val4);
    Serial.printf("Debug: val5 => %.2f\r\n", val5);
    Serial.printf("Debug: val6 => %.2f\r\n", val6);
    Serial.printf("Debug: val7 => %.2f\r\n", val7);
    Serial.printf("Debug: val8 => %.2f\r\n", val8);
    Serial.printf("Debug: val9 => %.2f\r\n", val9);
    Serial.printf("Debug: val10 => %.2f\r\n", val10);
#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_ModbusRTU
 * DESCRIPTION: tiny32 sensor read
 * PARAMETERS:  address
 * RETURNED:    referance variable [1-9]
 ***********************************************************************/
bool tiny32_v3::tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8, float &val9)
{
  // #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[41];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x12;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 41)
  {

    // Collect data
    for (int i = 0; i <= 44; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 41)
  {

    uint8_t _addcnt = _byte_cnt - 41; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
// Serial.printf("Debug: _crc = 0x%X\r\n",_crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* val1 process */
    _sResult = _data_check[5];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[3]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val1 = (*(float *)&_sResult);         //**Floating point 16bit convert

    /* val2 process */
    _sResult = _data_check[9];             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[10]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[7];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[8];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    val2 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val3 process */
    _sResult = _data_check[13];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[14]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[11]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[12]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val3 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val4 process */
    _sResult = _data_check[17];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[18]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[15]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[16]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val4 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val5 process */
    _sResult = _data_check[21];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[22]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[19]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[20]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val5 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val6 process */
    _sResult = _data_check[25];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[26]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[23]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[24]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val6 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val7 process */
    _sResult = _data_check[29];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[30]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[27]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[28]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val7 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val8 process */
    _sResult = _data_check[33];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[34]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[31]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[32]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val8 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val9 process */
    _sResult = _data_check[37];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[38]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[35]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[36]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val9 = (*(float *)&_sResult);          //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", val1);
    Serial.printf("Debug: val2 => %.2f\r\n", val2);
    Serial.printf("Debug: val3 => %.2f\r\n", val3);
    Serial.printf("Debug: val4 => %.2f\r\n", val4);
    Serial.printf("Debug: val5 => %.2f\r\n", val5);
    Serial.printf("Debug: val6 => %.2f\r\n", val6);
    Serial.printf("Debug: val7 => %.2f\r\n", val7);
    Serial.printf("Debug: val8 => %.2f\r\n", val8);
    Serial.printf("Debug: val9 => %.2f\r\n", val9);
#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_ModbusRTU
 * DESCRIPTION: tiny32 sensor read
 * PARAMETERS:  address
 * RETURNED:    referance variable [1-8]
 ***********************************************************************/
bool tiny32_v3::tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8)
{
  // #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[37];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x10;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 37)
  {

    // Collect data
    for (int i = 0; i <= 44; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 37)
  {

    uint8_t _addcnt = _byte_cnt - 37; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
// Serial.printf("Debug: _crc = 0x%X\r\n",_crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* val1 process */
    _sResult = _data_check[5];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[3]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val1 = (*(float *)&_sResult);         //**Floating point 16bit convert

    /* val2 process */
    _sResult = _data_check[9];             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[10]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[7];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[8];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    val2 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val3 process */
    _sResult = _data_check[13];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[14]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[11]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[12]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val3 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val4 process */
    _sResult = _data_check[17];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[18]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[15]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[16]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val4 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val5 process */
    _sResult = _data_check[21];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[22]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[19]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[20]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val5 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val6 process */
    _sResult = _data_check[25];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[26]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[23]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[24]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val6 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val7 process */
    _sResult = _data_check[29];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[30]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[27]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[28]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val7 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val8 process */
    _sResult = _data_check[33];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[34]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[31]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[32]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val8 = (*(float *)&_sResult);          //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", val1);
    Serial.printf("Debug: val2 => %.2f\r\n", val2);
    Serial.printf("Debug: val3 => %.2f\r\n", val3);
    Serial.printf("Debug: val4 => %.2f\r\n", val4);
    Serial.printf("Debug: val5 => %.2f\r\n", val5);
    Serial.printf("Debug: val6 => %.2f\r\n", val6);
    Serial.printf("Debug: val7 => %.2f\r\n", val7);
    Serial.printf("Debug: val8 => %.2f\r\n", val8);
#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_ModbusRTU
 * DESCRIPTION: tiny32 sensor read
 * PARAMETERS:  address
 * RETURNED:    referance variable [1-7]
 ***********************************************************************/
bool tiny32_v3::tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7)
{
  // #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[33];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x0E;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 33)
  {

    // Collect data
    for (int i = 0; i <= 44; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 33)
  {

    uint8_t _addcnt = _byte_cnt - 33; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
// Serial.printf("Debug: _crc = 0x%X\r\n",_crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* val1 process */
    _sResult = _data_check[5];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[3]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val1 = (*(float *)&_sResult);         //**Floating point 16bit convert

    /* val2 process */
    _sResult = _data_check[9];             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[10]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[7];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[8];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    val2 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val3 process */
    _sResult = _data_check[13];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[14]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[11]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[12]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val3 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val4 process */
    _sResult = _data_check[17];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[18]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[15]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[16]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val4 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val5 process */
    _sResult = _data_check[21];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[22]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[19]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[20]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val5 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val6 process */
    _sResult = _data_check[25];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[26]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[23]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[24]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val6 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val7 process */
    _sResult = _data_check[29];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[30]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[27]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[28]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val7 = (*(float *)&_sResult);          //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", val1);
    Serial.printf("Debug: val2 => %.2f\r\n", val2);
    Serial.printf("Debug: val3 => %.2f\r\n", val3);
    Serial.printf("Debug: val4 => %.2f\r\n", val4);
    Serial.printf("Debug: val5 => %.2f\r\n", val5);
    Serial.printf("Debug: val6 => %.2f\r\n", val6);
    Serial.printf("Debug: val7 => %.2f\r\n", val7);
#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_ModbusRTU
 * DESCRIPTION: tiny32 sensor read
 * PARAMETERS:  address
 * RETURNED:    referance variable [1-6]
 ***********************************************************************/
bool tiny32_v3::tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6)
{
  // #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[29];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x0C;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 29)
  {

    // Collect data
    for (int i = 0; i <= 44; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 29)
  {

    uint8_t _addcnt = _byte_cnt - 29; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
// Serial.printf("Debug: _crc = 0x%X\r\n",_crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* val1 process */
    _sResult = _data_check[5];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[3]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val1 = (*(float *)&_sResult);         //**Floating point 16bit convert

    /* val2 process */
    _sResult = _data_check[9];             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[10]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[7];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[8];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    val2 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val3 process */
    _sResult = _data_check[13];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[14]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[11]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[12]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val3 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val4 process */
    _sResult = _data_check[17];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[18]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[15]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[16]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val4 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val5 process */
    _sResult = _data_check[21];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[22]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[19]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[20]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val5 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val6 process */
    _sResult = _data_check[25];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[26]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[23]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[24]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val6 = (*(float *)&_sResult);          //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", val1);
    Serial.printf("Debug: val2 => %.2f\r\n", val2);
    Serial.printf("Debug: val3 => %.2f\r\n", val3);
    Serial.printf("Debug: val4 => %.2f\r\n", val4);
    Serial.printf("Debug: val5 => %.2f\r\n", val5);
    Serial.printf("Debug: val6 => %.2f\r\n", val6);

#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_ModbusRTU
 * DESCRIPTION: tiny32 sensor read
 * PARAMETERS:  address
 * RETURNED:    referance variable [1-5]
 ***********************************************************************/
bool tiny32_v3::tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5)
{
  // #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[25];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x0A;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 25)
  {

    // Collect data
    for (int i = 0; i <= 44; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 25)
  {

    uint8_t _addcnt = _byte_cnt - 25; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
// Serial.printf("Debug: _crc = 0x%X\r\n",_crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* val1 process */
    _sResult = _data_check[5];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[3]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val1 = (*(float *)&_sResult);         //**Floating point 16bit convert

    /* val2 process */
    _sResult = _data_check[9];             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[10]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[7];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[8];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    val2 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val3 process */
    _sResult = _data_check[13];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[14]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[11]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[12]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val3 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val4 process */
    _sResult = _data_check[17];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[18]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[15]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[16]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val4 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val5 process */
    _sResult = _data_check[21];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[22]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[19]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[20]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val5 = (*(float *)&_sResult);          //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", val1);
    Serial.printf("Debug: val2 => %.2f\r\n", val2);
    Serial.printf("Debug: val3 => %.2f\r\n", val3);
    Serial.printf("Debug: val4 => %.2f\r\n", val4);
    Serial.printf("Debug: val5 => %.2f\r\n", val5);

#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_ModbusRTU
 * DESCRIPTION: tiny32 sensor read
 * PARAMETERS:  address
 * RETURNED:    referance variable [1-4]
 ***********************************************************************/
bool tiny32_v3::tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4)
{
  // #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[21];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x08;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 21)
  {

    // Collect data
    for (int i = 0; i <= 44; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 21)
  {

    uint8_t _addcnt = _byte_cnt - 21; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
// Serial.printf("Debug: _crc = 0x%X\r\n",_crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* val1 process */
    _sResult = _data_check[5];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[3]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val1 = (*(float *)&_sResult);         //**Floating point 16bit convert

    /* val2 process */
    _sResult = _data_check[9];             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[10]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[7];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[8];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    val2 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val3 process */
    _sResult = _data_check[13];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[14]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[11]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[12]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val3 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val4 process */
    _sResult = _data_check[17];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[18]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[15]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[16]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val4 = (*(float *)&_sResult);          //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", val1);
    Serial.printf("Debug: val2 => %.2f\r\n", val2);
    Serial.printf("Debug: val3 => %.2f\r\n", val3);
    Serial.printf("Debug: val4 => %.2f\r\n", val4);

#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_ModbusRTU
 * DESCRIPTION: tiny32 sensor read
 * PARAMETERS:  address
 * RETURNED:    referance variable [1-3]
 ***********************************************************************/
bool tiny32_v3::tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3)
{
  // #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[17];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x06;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 17)
  {

    // Collect data
    for (int i = 0; i <= 44; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 17)
  {

    uint8_t _addcnt = _byte_cnt - 17; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
// Serial.printf("Debug: _crc = 0x%X\r\n",_crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* val1 process */
    _sResult = _data_check[5];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[3]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val1 = (*(float *)&_sResult);         //**Floating point 16bit convert

    /* val2 process */
    _sResult = _data_check[9];             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[10]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[7];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[8];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    val2 = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* val3 process */
    _sResult = _data_check[13];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[14]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[11]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[12]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val3 = (*(float *)&_sResult);          //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", val1);
    Serial.printf("Debug: val2 => %.2f\r\n", val2);
    Serial.printf("Debug: val3 => %.2f\r\n", val3);

#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_ModbusRTU
 * DESCRIPTION: tiny32 sensor read
 * PARAMETERS:  address
 * RETURNED:    referance variable [1-2]
 ***********************************************************************/
bool tiny32_v3::tiny32_ModbusRTU(uint8_t id, float &val1, float &val2)
{
  // #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[13];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x04;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 13)
  {

    // Collect data
    for (int i = 0; i <= 44; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 13)
  {

    uint8_t _addcnt = _byte_cnt - 13; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
// Serial.printf("Debug: _crc = 0x%X\r\n",_crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* val1 process */
    _sResult = _data_check[5];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[3]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val1 = (*(float *)&_sResult);         //**Floating point 16bit convert

    /* val2 process */
    _sResult = _data_check[9];             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[10]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[7];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[8];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    val2 = (*(float *)&_sResult);          //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", val1);
    Serial.printf("Debug: val2 => %.2f\r\n", val2);

#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_ModbusRTU
 * DESCRIPTION: tiny32 sensor read
 * PARAMETERS:  address
 * RETURNED:    referance variable [1]
 ***********************************************************************/
bool tiny32_v3::tiny32_ModbusRTU(uint8_t id, float &val1)
{
  // #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 9)
  {

    // Collect data
    for (int i = 0; i <= 44; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 9)
  {

    uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
// Serial.printf("Debug: _crc = 0x%X\r\n",_crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* val1 process */
    _sResult = _data_check[5];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[3]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    val1 = (*(float *)&_sResult);         //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", val1);
#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_ModbusRTU_searchAddress
 * DESCRIPTION: Search Address from ModbusRTU Module [1-253]
 * PARAMETERS:  nothing
 * RETURNED:    Address
 ***********************************************************************/
int8_t tiny32_v3::tiny32_ModbusRTU_searchAddress(void)
{
  uint8_t _id;

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  /* Find ID from 1 to 253*/
  for (_id = 1; _id <= 253; _id++)
  {

    /*clear data*/
    _crc = 0xffff;
    _crc_r = 0xffff;
    _byte_cnt = 0;
    for (int i = 0; i < sizeof(_data_check); i++)
    {
      _data_read[i] = 0x00;
      _data_check[i] = 0x00;
    }

    _data_write[0] = _id;
    _data_write[1] = 0x04;
    _data_write[2] = 0x00;
    _data_write[3] = 0x20;
    _data_write[4] = 0x00;
    _data_write[5] = 0x02;

    // Generate CRC16
    for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
    {
      _crc = crc16_update(_crc, _data_write[_i]);
    }

    // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
    Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
    _data_write[sizeof(_data_write) - 1] = _crc >> 8;
    _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data write(%d): [ ", sizeof(_data_write));
    for (byte _i = 0; _i < sizeof(_data_write); _i++)
    {
      if (_data_write[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_write[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_write[_i]);
      }
    }
    Serial.printf("]\r\n");
#endif
#pragma endregion

    /**** Write data ****/
    rs485.flush();
    for (int _i = 0; _i < 8; _i++)
      rs485.write(_data_write[_i]);

    vTaskDelay(300);

    /**** Read data ****/
    if (rs485.available())
    {

      for (byte _i = 0; _i < sizeof(_data_read); _i++)
        _data_read[_i] = 0x00; // clear buffer
      _byte_cnt = 0;

      // correct data
      do
      {
        _data_read[_byte_cnt++] = rs485.read();
        if (_data_read[0] == 0x00)
        { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
          _byte_cnt = 0;
        }
        // }while(rs485.available()>0);
      } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data read(%d): [ ", _byte_cnt);
      for (byte _i = 0; _i < _byte_cnt; _i++)
      {
        if (_data_read[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_read[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_read[_i]);
        }
      }
      Serial.println("]");
#endif
    }

    /* Collect data to variable buffer */
    if (_byte_cnt == 9)
    {

      for (int i = 0; i < 9; i++)
      {
        _data_check[i] = _data_read[i];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this tiny32_MobusRTU_client => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }

    else if (_byte_cnt > 9)
    {

      uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

      // Collect data
      for (int i = 0; i < 9; i++)
      {
        _data_check[i] = _data_read[i + _addcnt];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this tiny32_MobusRTU_client => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }
    else
    {
      Serial.printf(".");
    }
  }

  Serial.printf("\r\nInfo: Finish searching .... Can't find tiny32_MobusRTU_client for this bus [fail]");
}

/***********************************************************************
 * FUNCTION:    tiny32_ModbusRTU_setAddress
 * DESCRIPTION: Set Address for tiny32_ModbusRTU Module [1-252]
 * PARAMETERS:  id, new_id
 * RETURNED:    Address
 ***********************************************************************/
int8_t tiny32_v3::tiny32_ModbusRTU_setAddress(uint8_t id, uint8_t new_id)
{

  /*check parameter*/
  if ((new_id < 1) || (new_id >= 253))
  {
    Serial.printf("Error: Address is out of the range[1-253]\r\n");
    return -1;
  }

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[8];

  _data_write[0] = id;
  _data_write[1] = 0x06;
  _data_write[2] = 0x00;
  _data_write[3] = 0x20;
  _data_write[4] = 0x00;
  _data_write[5] = new_id;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Byte Count = %d\r\n", _byte_cnt);
#endif
  }

  if (_byte_cnt == 8)
  {

    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 8)
  {

    uint8_t _addcnt = _byte_cnt - 8;
    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    Serial.printf("Info: Success to set new Address[%d]\r\n", new_id);
    return new_id;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    ENenergic_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::ENenergic_begin(uint8_t rx, uint8_t tx)
{
  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(9600, SERIAL_8N1, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    ENenergic_searchAddress
 * DESCRIPTION: Search Address from ENenergic Power Meter [1-247]
 * PARAMETERS:  nothing
 * RETURNED:    Address
 ***********************************************************************/
int8_t tiny32_v3::ENenergic_searchAddress(void)
{
  uint8_t _id;

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  /* Find ID from 1 to 253*/
  for (_id = 1; _id <= 247; _id++)
  {

    /*clear data*/
    _crc = 0xffff;
    _crc_r = 0xffff;
    _byte_cnt = 0;
    for (int i = 0; i < sizeof(_data_check); i++)
    {
      _data_read[i] = 0x00;
      _data_check[i] = 0x00;
    }

    _data_write[0] = _id;
    _data_write[1] = 0x03;
    _data_write[2] = 0x43;
    _data_write[3] = 0xCC;
    _data_write[4] = 0x00;
    _data_write[5] = 0x02;

    // Generate CRC16
    for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
    {
      _crc = crc16_update(_crc, _data_write[_i]);
    }

    // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
    Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
    _data_write[sizeof(_data_write) - 1] = _crc >> 8;
    _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data write(%d): [ ", sizeof(_data_write));
    for (byte _i = 0; _i < sizeof(_data_write); _i++)
    {
      if (_data_write[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_write[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_write[_i]);
      }
    }
    Serial.printf("]\r\n");
#endif
#pragma endregion

    /**** Write data ****/
    rs485.flush();
    for (int _i = 0; _i < 8; _i++)
      rs485.write(_data_write[_i]);

    vTaskDelay(300);

    /**** Read data ****/
    if (rs485.available())
    {

      for (byte _i = 0; _i < sizeof(_data_read); _i++)
        _data_read[_i] = 0x00; // clear buffer
      _byte_cnt = 0;

      // correct data
      do
      {
        _data_read[_byte_cnt++] = rs485.read();
        if (_data_read[0] == 0x00)
        { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
          _byte_cnt = 0;
        }
        // }while(rs485.available()>0);
      } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data read(%d): [ ", _byte_cnt);
      for (byte _i = 0; _i < _byte_cnt; _i++)
      {
        if (_data_read[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_read[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_read[_i]);
        }
      }
      Serial.println("]");
#endif
    }

    /* Collect data to variable buffer */
    if (_byte_cnt == 9)
    {

      for (int i = 0; i < 9; i++)
      {
        _data_check[i] = _data_read[i];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this ENenergic Power Meter => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }

    else if (_byte_cnt > 9)
    {

      uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

      // Collect data
      for (int i = 0; i < 9; i++)
      {
        _data_check[i] = _data_read[i + _addcnt];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this ENenergic Power Meter => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }
    else
    {
      Serial.printf(".");
    }
  }

  Serial.printf("\r\nInfo: Finish searching .... Can't find ENenergic Power Meter for this bus [fail]");
}

/***********************************************************************
 * FUNCTION:    ENenergic_setAddress
 * DESCRIPTION: Set Address for ENenergic Power Meter [1-247]
 * PARAMETERS:  id, new_id
 * RETURNED:    Address
 ***********************************************************************/
int8_t tiny32_v3::ENenergic_setAddress(uint8_t id, uint8_t new_id)
{

  /*check parameter*/
  if ((new_id < 1) || (new_id >= 253))
  {
    Serial.printf("Error: Address is out of the range[1-247]\r\n");
    return -1;
  }

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[8];

  _data_write[0] = id;
  _data_write[1] = 0x06;
  _data_write[2] = 0x43;
  _data_write[3] = 0xCD;
  _data_write[4] = 0x00;
  _data_write[5] = new_id;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Byte Count = %d\r\n", _byte_cnt);
#endif
  }

  if (_byte_cnt == 8)
  {

    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 8)
  {

    uint8_t _addcnt = _byte_cnt - 8;
    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    Serial.printf("Info: Success to set new Address[%d]\r\n", new_id);
    return new_id;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    ENenergic_getTemperature
 * DESCRIPTION: get internal temperature (C)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::ENenergic_getTemperature(uint8_t id)
{
  float _floatTemp;
  // #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x80;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 9)
  {

    // Collect data
    for (int i = 0; i <= 9; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 9)
  {

    uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 9; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
// Serial.printf("Debug: _crc = 0x%X\r\n",_crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* val1 process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _floatTemp = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: _floatTemp => %.4f\r\n", _floatTemp);
#endif
    return _floatTemp;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    ENenergic_Volt_L_N
 * DESCRIPTION: get Voltage L1-N, Voltage L2-N, Voltage L3-N (V)
 * PARAMETERS:  address
 * RETURNED:    referance variable [3]
 ***********************************************************************/
bool tiny32_v3::ENenergic_Volt_L_N(uint8_t id, float &L1_N, float &L2_N, float &L3_N)
{

  const byte _byte_len = 17; // จำนวน byte ที่อ่านได้
                             //  #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[17];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x06;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* L1_N process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L1_N = (*(float *)&_sResult);         //**Floating point 16bit convert

    /* L2_N process */
    _sResult = _data_check[7];             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[8];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[9];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[10]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L2_N = (*(float *)&_sResult);          //**Floating point 16bit convert

    /* L3_N process */
    _sResult = _data_check[11];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[12]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[13]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[14]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L3_N = (*(float *)&_sResult);          //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", L1_N);
    Serial.printf("Debug: val2 => %.2f\r\n", L2_N);
    Serial.printf("Debug: val3 => %.2f\r\n", L3_N);

#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    ENenergic_Volt_L_L
 * DESCRIPTION: get Voltage L1-L2, Voltage L2-L3, Voltage L3-L1 (V)
 * PARAMETERS:  address
 * RETURNED:    referance variable [3]
 ***********************************************************************/
bool tiny32_v3::ENenergic_Volt_L_L(uint8_t id, float &L1_L2, float &L2_L3, float &L3_L1)
{

  const byte _byte_len = 17; // จำนวน byte ที่อ่านได้
                             //  #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[17];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x08;
  _data_write[4] = 0x00;
  _data_write[5] = 0x06;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* L1_L2 process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L1_L2 = (*(float *)&_sResult);        //**Floating point 16bit convert

    /* L2_L3 process */
    _sResult = _data_check[7];             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[8];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[9];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[10]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L2_L3 = (*(float *)&_sResult);         //**Floating point 16bit convert

    /* L3_L1 process */
    _sResult = _data_check[11];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[12]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[13]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[14]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L3_L1 = (*(float *)&_sResult);         //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", L1_L2);
    Serial.printf("Debug: val2 => %.2f\r\n", L2_L3);
    Serial.printf("Debug: val3 => %.2f\r\n", L3_L1);

#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    ENenergic_Current_L
 * DESCRIPTION: get Current L1,Current L2,Current L3
 * PARAMETERS:  address
 * RETURNED:    referance variable [3]
 ***********************************************************************/
bool tiny32_v3::ENenergic_Current_L(uint8_t id, float &L1, float &L2, float &L3)
{

  const byte _byte_len = 17; // จำนวน byte ที่อ่านได้
                             //  #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x0E;
  _data_write[4] = 0x00;
  _data_write[5] = 0x06;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* L1 process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L1 = (*(float *)&_sResult);           //**Floating point 16bit convert

    /* L2 process */
    _sResult = _data_check[7];             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[8];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[9];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[10]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L2 = (*(float *)&_sResult);            //**Floating point 16bit convert

    /* L3 process */
    _sResult = _data_check[11];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[12]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[13]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[14]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L3 = (*(float *)&_sResult);            //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", L1);
    Serial.printf("Debug: val2 => %.2f\r\n", L2);
    Serial.printf("Debug: val3 => %.2f\r\n", L3);

#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    ENenergic_NeutralCurrent
 * DESCRIPTION: get NeuralCurrent IL1+IL2+IL3 (A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::ENenergic_NeutralCurrent(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x16;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    ENenergic_Freq
 * DESCRIPTION: get Frequency (Hz)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::ENenergic_Freq(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x18;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    ENenergic_PhaseVolt_Angle
 * DESCRIPTION: get Phase Voltage Angle L1, Phase Voltage Angle L2, Phase Voltage Angle L3 (Degree)
 * PARAMETERS:  address
 * RETURNED:    referance variable [3]
 ***********************************************************************/
bool tiny32_v3::ENenergic_PhaseVolt_Angle(uint8_t id, float &L1, float &L2, float &L3)
{

  const byte _byte_len = 17; // จำนวน byte ที่อ่านได้
                             //  #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[17];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x6A;
  _data_write[4] = 0x00;
  _data_write[5] = 0x06;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* L1 process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L1 = (*(float *)&_sResult);           //**Floating point 16bit convert

    /* L2 process */
    _sResult = _data_check[7];             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[8];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[9];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[10]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L2 = (*(float *)&_sResult);            //**Floating point 16bit convert

    /* L3 process */
    _sResult = _data_check[11];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[12]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[13]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[14]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L3 = (*(float *)&_sResult);            //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", L1);
    Serial.printf("Debug: val2 => %.2f\r\n", L2);
    Serial.printf("Debug: val3 => %.2f\r\n", L3);

#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    ENenergic_PhaseCurrent_Angle
 * DESCRIPTION: get Phase Current Angle L1, Phase Current Angle L2, Phase Current Angle L3 (Degree)
 * PARAMETERS:  address
 * RETURNED:    referance variable [3]
 ***********************************************************************/
bool tiny32_v3::ENenergic_PhaseCurrent_Angle(uint8_t id, float &L1, float &L2, float &L3)
{

  const byte _byte_len = 17; // จำนวน byte ที่อ่านได้
                             //  #define modbusRTU_Debug
  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[17];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x72;
  _data_write[4] = 0x00;
  _data_write[5] = 0x06;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return 0;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* L1 process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L1 = (*(float *)&_sResult);           //**Floating point 16bit convert

    /* L2 process */
    _sResult = _data_check[7];             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[8];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[9];  // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[10]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L2 = (*(float *)&_sResult);            //**Floating point 16bit convert

    /* L3 process */
    _sResult = _data_check[11];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[12]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[13]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;              // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[14]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    L3 = (*(float *)&_sResult);            //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", L1);
    Serial.printf("Debug: val2 => %.2f\r\n", L2);
    Serial.printf("Debug: val3 => %.2f\r\n", L3);

#endif
    return 1;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::SchneiderPM2xxx_begin(uint8_t rx, uint8_t tx)
{
  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(9600, SERIAL_8N1, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_searchAddress
 * DESCRIPTION: Search Address from Schneider Digital Power Meter [1-255]
 * PARAMETERS:  nothing
 * RETURNED:    Address
 ***********************************************************************/
int8_t tiny32_v3::SchneiderPM2xxx_searchAddress(void)
{
  uint8_t _id;
  const byte _byte_len = 7; // จำนวน byte ที่อ่านได้
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  /* Find ID from 1 to 253*/
  for (_id = 1; _id <= 255; _id++)
  {

    /*clear data*/
    _crc = 0xffff;
    _crc_r = 0xffff;
    _byte_cnt = 0;
    for (int i = 0; i < sizeof(_data_check); i++)
    {
      _data_read[i] = 0x00;
      _data_check[i] = 0x00;
    }

    _data_write[0] = _id;
    _data_write[1] = 0x03;
    _data_write[2] = 0x19;
    _data_write[3] = 0x64;
    _data_write[4] = 0x00;
    _data_write[5] = 0x01;

    // Generate CRC16
    for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
    {
      _crc = crc16_update(_crc, _data_write[_i]);
    }

    // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
    Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
    _data_write[sizeof(_data_write) - 1] = _crc >> 8;
    _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data write(%d): [ ", sizeof(_data_write));
    for (byte _i = 0; _i < sizeof(_data_write); _i++)
    {
      if (_data_write[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_write[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_write[_i]);
      }
    }
    Serial.printf("]\r\n");
#endif
#pragma endregion

    /**** Write data ****/
    rs485.flush();
    for (int _i = 0; _i < 8; _i++)
      rs485.write(_data_write[_i]);

    vTaskDelay(300);

    /**** Read data ****/
    if (rs485.available())
    {

      for (byte _i = 0; _i < sizeof(_data_read); _i++)
        _data_read[_i] = 0x00; // clear buffer
      _byte_cnt = 0;

      // correct data
      do
      {
        _data_read[_byte_cnt++] = rs485.read();
        if (_data_read[0] == 0x00)
        { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
          _byte_cnt = 0;
        }
        // }while(rs485.available()>0);
      } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data read(%d): [ ", _byte_cnt);
      for (byte _i = 0; _i < _byte_cnt; _i++)
      {
        if (_data_read[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_read[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_read[_i]);
        }
      }
      Serial.println("]");
#endif
    }

    /* Collect data to variable buffer */
    if (_byte_cnt == _byte_len)
    {

      for (int i = 0; i < _byte_len; i++)
      {
        _data_check[i] = _data_read[i];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this Schneider Digital Power Meter => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }

    else if (_byte_cnt > _byte_len)
    {

      uint8_t _addcnt = _byte_cnt - _byte_len; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

      // Collect data
      for (int i = 0; i < _byte_len; i++)
      {
        _data_check[i] = _data_read[i + _addcnt];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this Schneider Digital Power Meter => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }
    else
    {
      Serial.printf(".");
    }
  }

  Serial.printf("\r\nInfo: Finish searching .... Can't find Schneider Digital Power Meter for this bus [fail]");
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_Voltage_AB
 * DESCRIPTION: Voltage A-B (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_Voltage_AB(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xCB;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_Voltage_BC
 * DESCRIPTION: Voltage B-C (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_Voltage_BC(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xCD;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_Voltage_CA
 * DESCRIPTION: Voltage C-A (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_Voltage_CA(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xCF;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_Voltage_LL_Avg
 * DESCRIPTION: Voltage L-L Avg (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_Voltage_LL_Avg(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xD1;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_Voltage_AN
 * DESCRIPTION: Voltage A-N (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_Voltage_AN(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xD3;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_Voltage_BN
 * DESCRIPTION: Voltage B-N (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_Voltage_BN(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xD5;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_Voltage_CN
 * DESCRIPTION: Voltage C-N (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_Voltage_CN(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xD7;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_Voltage_LN_Avg
 * DESCRIPTION: get Voltage L-N Avg (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_Voltage_LN_Avg(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xDB;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_VoltageUnblance_AB
 * DESCRIPTION: Voltage UnbalanceA-B (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_VoltageUnblance_AB(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xDD;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_VoltageUnblance_BC
 * DESCRIPTION: Voltage UnbalanceB-C (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_VoltageUnblance_BC(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xDF;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_VoltageUnblance_CA
 * DESCRIPTION: Voltage UnbalanceC-A (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_VoltageUnblance_CA(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xE1;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_VoltageUnblance_LL_Worst
 * DESCRIPTION: Voltage UnbalanceL-L Worst (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_VoltageUnblance_LL_Worst(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xE3;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_VoltageUnblance_AN
 * DESCRIPTION: Voltage UnbalanceA-N (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_VoltageUnblance_AN(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xE5;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_VoltageUnblance_BN
 * DESCRIPTION: Voltage UnbalanceB-N (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_VoltageUnblance_BN(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xE7;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_VoltageUnblance_CN
 * DESCRIPTION: Voltage UnbalanceC-N (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_VoltageUnblance_CN(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xE9;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_VoltageUnblance_LN_Worst
 * DESCRIPTION: get Voltage L-N Worst (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_VoltageUnblance_LN_Worst(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xEB;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_CurrentA
 * DESCRIPTION: Current A (A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_CurrentA(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xB7;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_CurrentB
 * DESCRIPTION: Current B (A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_CurrentB(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xB9;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_CurrentC
 * DESCRIPTION: Current C (A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_CurrentC(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xBB;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_CurrentN
 * DESCRIPTION: Current N (A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_CurrentN(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xBD;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_CurrentG
 * DESCRIPTION: Current G (A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_CurrentG(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xBF;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_CurrentAvg
 * DESCRIPTION: Current Avg (A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_CurrentAvg(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xC1;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_CurrentUnblanceA
 * DESCRIPTION: Current Unbalance A (A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_CurrentUnblanceA(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xC3;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_CurrentUnblanceB
 * DESCRIPTION: Current Unbalance B (A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_CurrentUnblanceB(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xC5;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_CurrentUnblanceC
 * DESCRIPTION: Current Unbalance C (A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_CurrentUnblanceC(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xC7;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_CurrentUnblanceWorst
 * DESCRIPTION: get Current Unblance Worst (A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_CurrentUnblanceWorst(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xC9;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_ActivePowerA
 * DESCRIPTION: ActivePower A (kW)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_ActivePowerA(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xED;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_ActivePowerB
 * DESCRIPTION: ActivePower B (kW)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_ActivePowerB(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xEF;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_ActivePowerC
 * DESCRIPTION: ActivePower C (kW)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_ActivePowerC(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xF1;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_ActivePowerTotal
 * DESCRIPTION: Active Power Total (kW)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_ActivePowerTotal(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xF3;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_ReactivePowerA
 * DESCRIPTION: ReactivePower A (kVAR)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_ReactivePowerA(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xF5;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_ReactivePowerB
 * DESCRIPTION: ReactivePower B (kVAR)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_ReactivePowerB(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xF7;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_ReactivePowerC
 * DESCRIPTION: ReactivePower C (kVAR)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_ReactivePowerC(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xF9;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_ReactivePowerTotal
 * DESCRIPTION: Active Power Total (kVAR)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_ReactivePowerTotal(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xFB;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_ApparentPowerA
 * DESCRIPTION: ApparentPower A (kVA)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_ApparentPowerA(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xFD;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_ApparentPowerB
 * DESCRIPTION: ApparentPower B (kVA)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_ApparentPowerB(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0B;
  _data_write[3] = 0xFF;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_ApparentPowerC
 * DESCRIPTION: ApparentPower C (kVA)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_ApparentPowerC(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0C;
  _data_write[3] = 0x01;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_ApparentPowerTotal
 * DESCRIPTION: Active Power Total (kVA)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_ApparentPowerTotal(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0C;
  _data_write[3] = 0x03;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_PowerFactorA
 * DESCRIPTION: PowerFactor A
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_PowerFactorA(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0C;
  _data_write[3] = 0x05;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_PowerFactorB
 * DESCRIPTION: PowerFactor B
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_PowerFactorB(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0C;
  _data_write[3] = 0x07;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_PowerFactorC
 * DESCRIPTION: PowerFactor C
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_PowerFactorC(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0C;
  _data_write[3] = 0x09;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_PowerFactorTotal
 * DESCRIPTION: Active Power Total
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_PowerFactorTotal(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0C;
  _data_write[3] = 0x0B;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SchneiderPM2xxx_Freq
 * DESCRIPTION: Frequency (Hz)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SchneiderPM2xxx_Freq(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x0C;
  _data_write[3] = 0x25;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM120CT_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::SDM120CT_begin(uint8_t rx, uint8_t tx)
{
  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(9600, SERIAL_8N1, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    SDM120CT_searchAddress
 * DESCRIPTION: Search Address from SDM120CT Powermeter [1-247]
 * PARAMETERS:  nothing
 * RETURNED:    Address
 ***********************************************************************/
int8_t tiny32_v3::SDM120CT_searchAddress(void)
{
  uint8_t _id;

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  /* Find ID from 1 to 253*/
  for (_id = 1; _id <= 247; _id++)
  {

    /*clear data*/
    _crc = 0xffff;
    _crc_r = 0xffff;
    _byte_cnt = 0;
    for (int i = 0; i < sizeof(_data_check); i++)
    {
      _data_read[i] = 0x00;
      _data_check[i] = 0x00;
    }

    _data_write[0] = _id;
    _data_write[1] = 0x03;
    _data_write[2] = 0x00;
    _data_write[3] = 0x14;
    _data_write[4] = 0x00;
    _data_write[5] = 0x02;

    // Generate CRC16
    for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
    {
      _crc = crc16_update(_crc, _data_write[_i]);
    }

    // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
    Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
    _data_write[sizeof(_data_write) - 1] = _crc >> 8;
    _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data write(%d): [ ", sizeof(_data_write));
    for (byte _i = 0; _i < sizeof(_data_write); _i++)
    {
      if (_data_write[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_write[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_write[_i]);
      }
    }
    Serial.printf("]\r\n");
#endif
#pragma endregion

    /**** Write data ****/
    rs485.flush();
    for (int _i = 0; _i < 8; _i++)
      rs485.write(_data_write[_i]);

    vTaskDelay(300);

    /**** Read data ****/
    if (rs485.available())
    {

      for (byte _i = 0; _i < sizeof(_data_read); _i++)
        _data_read[_i] = 0x00; // clear buffer
      _byte_cnt = 0;

      // correct data
      do
      {
        _data_read[_byte_cnt++] = rs485.read();
        if (_data_read[0] == 0x00)
        { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
          _byte_cnt = 0;
        }
        // }while(rs485.available()>0);
      } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data read(%d): [ ", _byte_cnt);
      for (byte _i = 0; _i < _byte_cnt; _i++)
      {
        if (_data_read[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_read[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_read[_i]);
        }
      }
      Serial.println("]");
#endif
    }

    /* Collect data to variable buffer */
    if (_byte_cnt == 9)
    {

      for (int i = 0; i < 9; i++)
      {
        _data_check[i] = _data_read[i];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this SDM120CT Power Meter => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }

    else if (_byte_cnt > 9)
    {

      uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

      // Collect data
      for (int i = 0; i < 9; i++)
      {
        _data_check[i] = _data_read[i + _addcnt];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this SDM120CT Power Meter => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }
    else
    {
      Serial.printf(".");
    }
  }

  Serial.printf("\r\nInfo: Finish searching .... Can't find SDM120CT Power Meter for this bus [fail]");
}

/***********************************************************************
 * FUNCTION:    SDM120CT_Volt
 * DESCRIPTION: get Voltage (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM120CT_Volt(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM120CT_Power
 * DESCRIPTION: get Power (W)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM120CT_Power(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x0C;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM120CT_Current
 * DESCRIPTION: get Current (A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM120CT_Current(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x06;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM120CT_Total_Energy
 * DESCRIPTION: get Total Energy (kWh)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM120CT_Total_Energy(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x01;
  _data_write[3] = 0x56;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM120CT_Freq
 * DESCRIPTION: get Frequency (Hz)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM120CT_Freq(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x46;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif

  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM120CT_POWER_FACTOR
 * DESCRIPTION: get Power Factor(W)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM120CT_POWER_FACTOR(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x1E;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_WIND_RSFSN01_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::tiny32_WIND_RSFSN01_begin(uint8_t rx, uint8_t tx)
{
  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(9600, SERIAL_8N1, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_WIND_RSFSN01_searchAddress
 * DESCRIPTION: Search Address from Wind speed sensor [1-255]
 * PARAMETERS:  nothing
 * RETURNED:    Address
 ***********************************************************************/
int8_t tiny32_v3::tiny32_WIND_RSFSN01_searchAddress(void)
{
  uint8_t _id;
  const byte _byte_len = 7; // จำนวน byte ที่อ่านได้
  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  /* Find ID from 1 to 253*/
  for (_id = 1; _id <= 255; _id++)
  {

    /*clear data*/
    _crc = 0xffff;
    _crc_r = 0xffff;
    _byte_cnt = 0;
    for (int i = 0; i < sizeof(_data_check); i++)
    {
      _data_read[i] = 0x00;
      _data_check[i] = 0x00;
    }

    _data_write[0] = _id;
    _data_write[1] = 0x03;
    _data_write[2] = 0x07;
    _data_write[3] = 0xD0;
    _data_write[4] = 0x00;
    _data_write[5] = 0x01;

    // Generate CRC16
    for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
    {
      _crc = crc16_update(_crc, _data_write[_i]);
    }

    // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
    Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
    _data_write[sizeof(_data_write) - 1] = _crc >> 8;
    _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data write(%d): [ ", sizeof(_data_write));
    for (byte _i = 0; _i < sizeof(_data_write); _i++)
    {
      if (_data_write[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_write[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_write[_i]);
      }
    }
    Serial.printf("]\r\n");
#endif
#pragma endregion

    /**** Write data ****/
    rs485.flush();
    for (int _i = 0; _i < 8; _i++)
      rs485.write(_data_write[_i]);

    vTaskDelay(300);

    /**** Read data ****/
    if (rs485.available())
    {

      for (byte _i = 0; _i < sizeof(_data_read); _i++)
        _data_read[_i] = 0x00; // clear buffer
      _byte_cnt = 0;

      // correct data
      do
      {
        _data_read[_byte_cnt++] = rs485.read();
        if (_data_read[0] == 0x00)
        { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
          _byte_cnt = 0;
        }
        // }while(rs485.available()>0);
      } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data read(%d): [ ", _byte_cnt);
      for (byte _i = 0; _i < _byte_cnt; _i++)
      {
        if (_data_read[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_read[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_read[_i]);
        }
      }
      Serial.println("]");
#endif
    }

    /* Collect data to variable buffer */
    if (_byte_cnt == _byte_len)
    {

      for (int i = 0; i < _byte_len; i++)
      {
        _data_check[i] = _data_read[i];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this Wind speed sensor => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }

    else if (_byte_cnt > _byte_len)
    {

      uint8_t _addcnt = _byte_cnt - _byte_len; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

      // Collect data
      for (int i = 0; i < _byte_len; i++)
      {
        _data_check[i] = _data_read[i + _addcnt];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this Wind speed sensor => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }
    else
    {
      Serial.printf(".");
    }
  }

  Serial.printf("\r\nInfo: Finish searching .... Can't find Wind speed sensor for this bus [fail]");
}

/***********************************************************************
 * FUNCTION:    tiny32_WIND_RSFSN01_setAddress
 * DESCRIPTION: Set Address for Wind speed sensor [1-247]
 * PARAMETERS:  id, new_id
 * RETURNED:    Address
 ***********************************************************************/
int8_t tiny32_v3::tiny32_WIND_RSFSN01_setAddress(uint8_t id, uint8_t new_id)
{

  /*check parameter*/
  if ((new_id < 1) || (new_id >= 253))
  {
    Serial.printf("Error: Address is out of the range[1-247]\r\n");
    return -1;
  }

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[40];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[8];

  _data_write[0] = id;
  _data_write[1] = 0x06;
  _data_write[2] = 0x07;
  _data_write[3] = 0xD0;
  _data_write[4] = 0x00;
  _data_write[5] = new_id;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Byte Count = %d\r\n", _byte_cnt);
#endif
  }

  if (_byte_cnt == 8)
  {

    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 8)
  {

    uint8_t _addcnt = _byte_cnt - 8;
    for (int i = 0; i < 8; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    Serial.printf("Info: Success to set new Address[%d]\r\n", new_id);
    return new_id;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    tiny32_WIND_RSFSN01_SPEED
 * DESCRIPTION: get wind speed vlaue (m/s)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::tiny32_WIND_RSFSN01_SPEED(uint8_t id)
{
  // #define modbusRTU_Debug
  float _tempFloat;
  int _speed;
  const byte _byte_len = 7; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[50];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x03;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {
    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    // _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    // _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    // _sResult = _sResult << 8;              Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(int *)&_sResult) / 10.0; //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f \r\n", _tempFloat);
    Serial.printf("--------------------------------\r\n");
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::SDM630MCT_begin(uint8_t rx, uint8_t tx)
{
  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(9600, SERIAL_8N1, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_searchAddress
 * DESCRIPTION: Search Address from SDM120CT Powermeter [1-247]
 * PARAMETERS:  nothing
 * RETURNED:    Address
 ***********************************************************************/
int8_t tiny32_v3::SDM630MCT_searchAddress(void)
{
  uint8_t _id;

  // #define modbusRTU_Debug

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[9];

  /* Find ID from 1 to 257*/
  for (_id = 1; _id <= 247; _id++)
  {

    /*clear data*/
    _crc = 0xffff;
    _crc_r = 0xffff;
    _byte_cnt = 0;
    for (int i = 0; i < sizeof(_data_check); i++)
    {
      _data_read[i] = 0x00;
      _data_check[i] = 0x00;
    }

    _data_write[0] = _id;
    _data_write[1] = 0x03;
    _data_write[2] = 0x00;
    _data_write[3] = 0x14;
    _data_write[4] = 0x00;
    _data_write[5] = 0x02;

    // Generate CRC16
    for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
    {
      _crc = crc16_update(_crc, _data_write[_i]);
    }

    // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
    Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
    _data_write[sizeof(_data_write) - 1] = _crc >> 8;
    _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data write(%d): [ ", sizeof(_data_write));
    for (byte _i = 0; _i < sizeof(_data_write); _i++)
    {
      if (_data_write[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_write[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_write[_i]);
      }
    }
    Serial.printf("]\r\n");
#endif
#pragma endregion

    /**** Write data ****/
    rs485.flush();
    for (int _i = 0; _i < 8; _i++)
      rs485.write(_data_write[_i]);

    vTaskDelay(300);

    /**** Read data ****/
    if (rs485.available())
    {

      for (byte _i = 0; _i < sizeof(_data_read); _i++)
        _data_read[_i] = 0x00; // clear buffer
      _byte_cnt = 0;

      // correct data
      do
      {
        _data_read[_byte_cnt++] = rs485.read();
        if (_data_read[0] == 0x00)
        { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
          _byte_cnt = 0;
        }
        // }while(rs485.available()>0);
      } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data read(%d): [ ", _byte_cnt);
      for (byte _i = 0; _i < _byte_cnt; _i++)
      {
        if (_data_read[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_read[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_read[_i]);
        }
      }
      Serial.println("]");
#endif
    }

    /* Collect data to variable buffer */
    if (_byte_cnt == 9)
    {

      for (int i = 0; i < 9; i++)
      {
        _data_check[i] = _data_read[i];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this SDM120CT Power Meter => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }

    else if (_byte_cnt > 9)
    {

      uint8_t _addcnt = _byte_cnt - 9; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

      // Collect data
      for (int i = 0; i < 9; i++)
      {
        _data_check[i] = _data_read[i + _addcnt];
      }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
      Serial.printf("Data check(%d): [ ", sizeof(_data_check));
      for (byte _i = 0; _i < sizeof(_data_check); _i++)
      {
        if (_data_check[_i] > 0x0F)
        {
          Serial.printf("0x%X ", _data_check[_i]);
        }
        else
        {
          Serial.printf("0x0%X ", _data_check[_i]);
        }
      }
      Serial.println("]");
#endif

      /*** crc check for data read ***/
      _crc = 0xffff;
      _crc_r = 0xffff;

      // Generate CRC16
      for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
      {
        _crc = crc16_update(_crc, _data_check[_i]);
      }
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

      // read crc byte from data_check
      _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
      _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
      Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

      // return ON/OFF status
      if (_crc_r == _crc)
      {

        Serial.printf("\r\nInfo: the Address of this SDM120CT Power Meter => %d [Success]\r\n", _id);
        return _id;
      }
      else
      {
        // Serial.printf("Error: crc16\r\n");
        return -1;
      }
    }
    else
    {
      Serial.printf(".");
    }
  }

  Serial.printf("\r\nInfo: Finish searching .... Can't find SDM120CT Power Meter for this bus [fail]");
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P1_Volt
 * DESCRIPTION: get Phase 1 line to neutral volts. (V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P1_Volt(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x00;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P2_Volt
 * DESCRIPTION: get Phase 2 line to neutral volts.(V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P2_Volt(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x02;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P3_Volt
 * DESCRIPTION: get Phase 3 line to neutral volts.(V)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P3_Volt(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x04;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P1_Current
 * DESCRIPTION: get Phase 1 Current.(A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P1_Current(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x06;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P2_Current
 * DESCRIPTION: get Phase 2 Current. (A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P2_Current(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x08;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P3_Current
 * DESCRIPTION: get Phase 3 Current. (A)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P3_Current(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x0A;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P1_Watt
 * DESCRIPTION: get Phase 1 active power.(W)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P1_Watt(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x0C;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P2_Watt
 * DESCRIPTION: get Phase 2 active power.(W)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P2_Watt(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x0E;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P3_Watt
 * DESCRIPTION: get Phase 3 active power.(W)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P3_Watt(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x10;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P1_VA
 * DESCRIPTION: get Phase 1  apparent power.(VA)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P1_VA(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x12;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P2_VA
 * DESCRIPTION: get Phase 2  apparent power.(VA)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P2_VA(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x14;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P3_VA
 * DESCRIPTION: get Phase 3  apparent power.(VA)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P3_VA(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x16;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P1_VAr
 * DESCRIPTION: get Phase 1  reactive power.(VAr)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P1_VAr(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x18;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P2_VAr
 * DESCRIPTION: get Phase 2  reactive power.(VAr)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P2_VAr(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x1A;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P3_VAr
 * DESCRIPTION: get Phase 3  reactive power.(VAr)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P3_VAr(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x1C;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P1_PF
 * DESCRIPTION: get Phase 1 power factor
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P1_PF(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x1E;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P2_PF
 * DESCRIPTION: get Phase 2 power factor
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P2_PF(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x20;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_P3_PF
 * DESCRIPTION: get Phase 3 power factor
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_P3_PF(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x22;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_Freq
 * DESCRIPTION: get Frequency (Hz)
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_Freq(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x46;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_Sum_Current
 * DESCRIPTION: Sum of line currents.
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_Sum_Current(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x30;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_Total_Watt
 * DESCRIPTION: Total system power.
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_Total_Watt(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x34;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_Total_VA
 * DESCRIPTION: Total system volt amps.
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_Total_VA(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x38;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    SDM630MCT_Total_VAr
 * DESCRIPTION: Total system VAr.
 * PARAMETERS:  address
 * RETURNED:    float
 ***********************************************************************/
float tiny32_v3::SDM630MCT_Total_VAr(uint8_t id)
{
  // #define modbusRTU_Debug

  float _tempFloat;
  const byte _byte_len = 9; // จำนวน byte ที่อ่านได้

  uint16_t _crc = 0xffff;
  uint16_t _crc_r = 0xffff;
  uint16_t _temp_hex = 0xffff;
  unsigned long _sResult;
  // float _floatResult;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[_byte_len];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x3C;
  _data_write[4] = 0x00;
  _data_write[5] = 0x02;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

  // Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

#pragma region
/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif
#pragma endregion

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < sizeof(_data_write); _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if ((_data_read[0] == 0x00) || (_data_read[0] == 0xFF))
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00 หรือ 0xFF
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == _byte_len)
  {

    // Collect data
    for (int i = 0; i <= _byte_len; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    /* Value process */
    _sResult = _data_check[3];            // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[4]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[5]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult << 8;             // Serial.print(">>"); Serial.println(_sResult,HEX);
    _sResult = _sResult + _data_check[6]; // Serial.print(">>"); Serial.println(_sResult,HEX);
    _tempFloat = (*(float *)&_sResult);   //**Floating point 16bit convert

#ifdef modbusRTU_Debug
    Serial.printf("Debug: val1 => %.2f\r\n", _tempFloat);
#endif
    return _tempFloat;
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::CHILLER_R717_begin(uint8_t rx, uint8_t tx)
{
  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(9600, SERIAL_8N1, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_AI01_CHILLED_IN
 * DESCRIPTION: Chilled water Temp Inlet
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_AI01_CHILLED_IN(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x01;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_AI02_CHILLED_OUT
 * DESCRIPTION: Chilled water Temp Outlet
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_AI02_CHILLED_OUT(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x02;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_AI03_COOLED_IN
 * DESCRIPTION: Cooled water Temp Inlet
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_AI03_COOLED_IN(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x03;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_AI04_COOLED_OUT
 * DESCRIPTION: Cooled water Temp Outlet
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_AI04_COOLED_OUT(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x04;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_AI05_SUCTION_TEMP
 * DESCRIPTION: Suction Temp Compressor
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_AI05_SUCTION_TEMP(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x05;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_AI06_DISCHARGE_TEMP
 * DESCRIPTION: Discharge Temp Compressor
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_AI06_DISCHARGE_TEMP(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x06;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_AI08_COND_PRESS
 * DESCRIPTION: Condenser Temp
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_AI08_COND_PRESS(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x08;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_AI10_EVAP_PRESS
 * DESCRIPTION: Evap Pressure
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_AI10_EVAP_PRESS(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x0A;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_Slurry1_Temp
 * DESCRIPTION: Slurry 1 Temp
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_Slurry1_Temp(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x0B;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_Slurry2_Temp
 * DESCRIPTION: Slurry 2 Temp
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_Slurry2_Temp(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x0C;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_Slurry3_Temp
 * DESCRIPTION: Slurry 3 Temp
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_Slurry3_Temp(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x0D;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_Slurry4_Temp
 * DESCRIPTION: Slurry 4 Temp
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_Slurry4_Temp(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x0E;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_Coil_Temp
 * DESCRIPTION: Fan Coil Temp
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_Coil_Temp(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x0F;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_Room_Temp
 * DESCRIPTION: Room Temp
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_Room_Temp(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x10;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_CURRENT_COMP
 * DESCRIPTION: Current Compressor (A)
 * PARAMETERS:  address(id)
 * RETURNED:    _temperture
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_CURRENT_COMP(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x14;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_VOLT_COMP
 * DESCRIPTION: Voltage Compressor (V)
 * PARAMETERS:  address(id)
 * RETURNED:    _volt
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_VOLT_COMP(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x15;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_FREQ_COMP
 * DESCRIPTION: Frequency Compressor (Hz)
 * PARAMETERS:  address(id)
 * RETURNED:    _Hz
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_FREQ_COMP(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x16;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_POWER_COMP
 * DESCRIPTION: Power Compressor (kW)
 * PARAMETERS:  address(id)
 * RETURNED:    _kW
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_POWER_COMP(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x17;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_PER_COMP
 * DESCRIPTION: % Compressor
 * PARAMETERS:  address(id)
 * RETURNED:    %
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_PER_COMP(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x33;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_HOUR_CHILLED_PUMP
 * DESCRIPTION: Hour of Chilled Pump (hr)
 * PARAMETERS:  address(id)
 * RETURNED:    Hour
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_HOUR_CHILLED_PUMP(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x9D;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_HOUR_COMP
 * DESCRIPTION: Hour of Compressor (hr)
 * PARAMETERS:  address(id)
 * RETURNED:    Hour
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_HOUR_COMP(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x9E;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_HOUR_COOLED_PUMP
 * DESCRIPTION: Hour of Cooled Pump (hr)
 * PARAMETERS:  address(id)
 * RETURNED:    Hour
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_HOUR_COOLED_PUMP(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x9F;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_HOUR_COOLING_TOWER
 * DESCRIPTION: Hour of Cooling Tower (hr)
 * PARAMETERS:  address(id)
 * RETURNED:    Hour
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_HOUR_COOLING_TOWER(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0xA0;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_SP_ROOM
 * DESCRIPTION: Set Point Temp of Room (°C)
 * PARAMETERS:  address(id)
 * RETURNED:    Temperature
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_SP_ROOM(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x01;
  _data_write[3] = 0x44;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    CHILLER_R717_TOTAL_KW
 * DESCRIPTION: Total kW of system
 * PARAMETERS:  address(id)
 * RETURNED:    kW
 ***********************************************************************/
float tiny32_v3::CHILLER_R717_TOTAL_KW(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x01;
  _data_write[3] = 0x47;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}


/***********************************************************************
 * FUNCTION:    ATESS_R717_begin
 * DESCRIPTION: set RX and TX pin
 * PARAMETERS:  rx, tx
 * RETURNED:    true/ false
 ***********************************************************************/
bool tiny32_v3::ATESS_R717_begin(uint8_t rx, uint8_t tx)
{
  if (((tx == TXD2) || (tx == TXD3)) && ((rx == RXD2) || (rx == RXD3)))
  {
    rs485.begin(9600, SERIAL_8N1, rx, tx);
    return 1;
  }
  else
  {
    Serial.printf("Error: Fail to define RS485 port!!\r\n");
    return 0;
  }
}


/***********************************************************************
 * FUNCTION:    ATESS_Power_PV_kW
 * DESCRIPTION: Solar, PV1 power
 * PARAMETERS:  address(id)
 * RETURNED:    kW
 ***********************************************************************/
float tiny32_v3::ATESS_Power_PV_kW(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x33;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    ATESS_Power_bat_kW
 * DESCRIPTION: Discharging, Battery power
 * PARAMETERS:  address(id)
 * RETURNED:    kW
 ***********************************************************************/
float tiny32_v3::ATESS_Power_bat_kW(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x11;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    ATESS_SOC
 * DESCRIPTION: SoC, Battery percentage
 * PARAMETERS:  address(id)
 * RETURNED:    Percent
 ***********************************************************************/
float tiny32_v3::ATESS_SOC(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x2F;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    ATESS_ActivePower_Grid_kW
 * DESCRIPTION: Import, Bypass active power
 * PARAMETERS:  address(id)
 * RETURNED:    kW
 ***********************************************************************/
float tiny32_v3::ATESS_ActivePower_Grid_kW(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x13;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}


/***********************************************************************
 * FUNCTION:    ATESS_ActivePower_Load_kW
 * DESCRIPTION: Consumption, Load active power
 * PARAMETERS:  address(id)
 * RETURNED:    kW
 ***********************************************************************/
float tiny32_v3::ATESS_ActivePower_Load_kW(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x31;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}


/***********************************************************************
 * FUNCTION:    ATESS_Energy_PVToday_kWh
 * DESCRIPTION: Pv Generation, PV dailypower generation
 * PARAMETERS:  address(id)
 * RETURNED:    kWh
 ***********************************************************************/
float tiny32_v3::ATESS_Energy_PVToday_kWh(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x3E;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

/***********************************************************************
 * FUNCTION:    ATESS_Energy_BatChargeToday_kWh
 * DESCRIPTION: Daily Chargeharge, Battery daily charge capacity
 * PARAMETERS:  address(id)
 * RETURNED:    kWh
 ***********************************************************************/
float tiny32_v3::ATESS_Energy_BatChargeToday_kWh(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x1A;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}


/***********************************************************************
 * FUNCTION:    ATESS_Energy_BatDischargeToday_kWh
 * DESCRIPTION: Daily Discharge, Battery daily discharge capacity
 * PARAMETERS:  address(id)
 * RETURNED:    kWh
 ***********************************************************************/
float tiny32_v3::ATESS_Energy_BatDischargeToday_kWh(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x18;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}


/***********************************************************************
 * FUNCTION:    ATESS_Energy_GridOutToday_kWh
 * DESCRIPTION: Exported To Grid, Daily power fed to grid
 * PARAMETERS:  address(id)
 * RETURNED:    kWh
 ***********************************************************************/
float tiny32_v3::ATESS_Energy_GridOutToday_kWh(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x5E;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}


/***********************************************************************
 * FUNCTION:    ATESS_Energy_GridInToday_kWh
 * DESCRIPTION: Import From Grid, Daily power intake from grid
 * PARAMETERS:  address(id)
 * RETURNED:    kWh
 ***********************************************************************/
float tiny32_v3::ATESS_Energy_GridInToday_kWh(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x58;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}


/***********************************************************************
 * FUNCTION:    ATESS_Energy_LoadToday_kWh
 * DESCRIPTION: Load Consumption, Daily power consumption of load
 * PARAMETERS:  address(id)
 * RETURNED:    kWh
 ***********************************************************************/
float tiny32_v3::ATESS_Energy_LoadToday_kWh(uint8_t id)
{
  // #define modbusRTU_Debug

  int16_t _crc = 0xffff;
  int16_t _crc_r = 0xffff;
  int16_t _temp_hex_16bit = 0xffff;

  uint8_t _data_write[8];
  uint8_t _data_read[20];
  uint8_t _byte_cnt = 0;
  uint8_t _data_check[7];

  _data_write[0] = id;
  _data_write[1] = 0x04;
  _data_write[2] = 0x00;
  _data_write[3] = 0x52;
  _data_write[4] = 0x00;
  _data_write[5] = 0x01;

  float _temperature;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_write) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_write[_i]);
  }

// Insert CRC16 to data byte
#ifdef modbusRTU_Debug
  Serial.printf("_crc = 0x%02X\r\n", _crc);
#endif
  _data_write[sizeof(_data_write) - 1] = _crc >> 8;
  _data_write[sizeof(_data_write) - 2] = _crc - _data_write[sizeof(_data_write) - 1] * 0x0100;

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
  Serial.printf("Data write(%d): [ ", sizeof(_data_write));
  for (byte _i = 0; _i < sizeof(_data_write); _i++)
  {
    if (_data_write[_i] > 0x0F)
    {
      Serial.printf("0x%X ", _data_write[_i]);
    }
    else
    {
      Serial.printf("0x0%X ", _data_write[_i]);
    }
  }
  Serial.printf("]\r\n");
#endif

  /**** Write data ****/
  rs485.flush();
  for (int _i = 0; _i < 8; _i++)
    rs485.write(_data_write[_i]);

  vTaskDelay(300);

  /**** Read data ****/
  if (rs485.available())
  {

    for (byte _i = 0; _i < sizeof(_data_read); _i++)
      _data_read[_i] = 0x00; // clear buffer
    _byte_cnt = 0;

    // correct data
    do
    {
      _data_read[_byte_cnt++] = rs485.read();
      if (_data_read[0] == 0x00)
      { // แก้ไช bug เนื่องจากอ่านค่าแรกได้ 0x00
        _byte_cnt = 0;
      }
      // }while(rs485.available()>0);
    } while (rs485.available() > 0 && _byte_cnt < sizeof(_data_read));

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data read(%d): [ ", _byte_cnt);
    for (byte _i = 0; _i < _byte_cnt; _i++)
    {
      if (_data_read[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_read[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_read[_i]);
      }
    }
    Serial.println("]");
    Serial.printf("Debug: Count byte => %d\r\n", _byte_cnt);
#endif
  }

  /**** correct data to buffer variable ****/
  if (_byte_cnt == 7)
  {

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else if (_byte_cnt > 7)
  {

    uint8_t _addcnt = _byte_cnt - 7; // ตัวแปรชดเชยการอ่านค่าผิดตำแหน่ง

    // Collect data
    for (int i = 0; i < 7; i++)
    {
      _data_check[i] = _data_read[i + _addcnt];
    }

/***** Debug monitor ****/
#ifdef modbusRTU_Debug
    Serial.printf("Data check(%d): [ ", sizeof(_data_check));
    for (byte _i = 0; _i < sizeof(_data_check); _i++)
    {
      if (_data_check[_i] > 0x0F)
      {
        Serial.printf("0x%X ", _data_check[_i]);
      }
      else
      {
        Serial.printf("0x0%X ", _data_check[_i]);
      }
    }
    Serial.println("]");
#endif
  }
  else
  {
    Serial.printf("Error: data error\r\n");
    return -1;
  }

  /*** crc check for data read ***/
  _crc = 0xffff;
  _crc_r = 0xffff;

  // Generate CRC16
  for (byte _i = 0; _i < sizeof(_data_check) - 2; _i++)
  {
    _crc = crc16_update(_crc, _data_check[_i]);
  }
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc = 0x%X\r\n", _crc);
#endif

  // read crc byte from data_check
  _crc_r = _data_check[sizeof(_data_check) - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r << 8;                                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
  _crc_r = _crc_r + _data_check[sizeof(_data_check) - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);
#ifdef modbusRTU_Debug
  Serial.printf("Debug: _crc_r = 0x%X\r\n", _crc_r);
#endif

  // return ON/OFF status
  if (_crc_r == _crc)
  {

    //**** Read temperature ****
    _temp_hex_16bit = _data_check[3];                   // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit << 8;             // Serial.printf("Debug: _temp_hex = 0x%X\r\n",_temp_hex);
    _temp_hex_16bit = _temp_hex_16bit | _data_check[4]; // Serial.printf("Debug: _temp_hex = 0x%X(%d)\r\n",_temp_hex,_temp_hex);
    _temperature = (float)_temp_hex_16bit / 10;

#ifdef modbusRTU_Debug
    Serial.printf("Debug: temp[hex] => %.d\r\n", _temp_hex_16bit);
    Serial.printf("Debug: temperature[float] => %.1f\r\n", _temperature);
#endif

    return _temperature; // return value here
  }
  else
  {
    Serial.printf("Error: crc16\r\n");
    return -1;
  }
}

