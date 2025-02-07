/***********************************************************************
 * File         :     tiny32_v3.h
 * Description  :     Class for Hardware config and function for tiny32_v3 module
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     23 Nov 2021
 * Revision     :     3.13
 * Rev1.0       :     Original
 * Rev1.1       :     Add TimeStamp_minute
 *                    Add TimeStamp_24hr_minute
 * Rev1.2             Add EC RS485 sensor
 * Rev1.3             Change define switch to int
 * Rev1.4       :     Add EC sensor (RS485)
 * Rev1.5       :     Add PZEM-016 Energy Meter AC
 *                    Add PZEM-003 Energy Meter DC
 *                    Add rs485_2.begin(9600, SERIAL_8N2, RXD2, TXD2) for PZEM-003
 * Rev1.6             Intial board to BuildIN LED = > LOW
 * Rev1.7       :     Fix bug for PZEM-003 and PZEM-016 were read data error
 * Rev1.8       :     Add PZEM-003_begin, PZEM-016_begin and ec_modbusRTU_begin for initial set RS485 pin
 * Rev3.0       :     Major change hardware from tiny32_v2.0 to tiny32_v3.0
 *                    Add WTR10_E(SHT20) temperature and humidity sensor (RS485)
 * Rev3.1       :     Add XY-MD02(SHT20) temperature and humidity sensor (RS485)
 * Rev3.2       :     Add SOIL MOISTURE PR-3000-H-N01 sensor (RS485) fix id = 1, baud rate = 4800
 * Rev3.3       :     Add RS485 Water Flow Meter RS485 MODBUS output
 * Rev3.4       :     Add PYR20-Solar Radiation/Pyranometer Sensor, RS485, Modbus
 * Rev3.5       :     Add tiny32 ModbusRTU communication
 * Rev3.5.1     :     Fix bug for modbusRTU by relay 300mS after write modbus RTU (complier of some computer problem)
 * Rev3.5.2     :     Add Example_OTA.ino
 * Rev3.5.3     :     Revise code for Add RS485 Water Flow Meter RS485 MODBUS output (Rev3.3)
 * Rev3.6       :     Add ENenergic ModbusRTU Power Meter
 * Rev3.7       :     Add Schneider EasyLogic PM2xxx Digital Power Meter
 * Rev3.8       :     Add EASTRON Powermeter model : SDM1210CT
 * Rev3.8.1     :     fix bug pzem-016 and pzem-003
 * Rev3.9       :     Frequency_Out function for control Frequency to Volage Module with PWM output is 0-10V
 * Rev3.10      :     Add Wind speed sensor Model RS-FS-N01 485 type [PR-3000FSJT-N01]
 * Rev3.10.1    :     Revise and improve of SDM1210CT
 * Rev3.11      :     Add EASTRON Powermeter 3-phase model :SDM630MCT
 * Rev3.12      :     Add Chiller_R717 ModbusRTU [27-04-2024]
 * Rev3.13      :     Add Inverter ATESS ModbusRUT [28-04-2024]
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@tenergyinnovation.co.th
 * TEL          :     089-140-7205
 ***********************************************************************/

#ifndef TINY32_H
#define TINY32_H
#include "Ticker.h"

class tiny32_v3
{
private:
#define version_c "3.13"

public:
/**************************************/
/*           GPIO define              */
/**************************************/
#define RXD2 16
#define TXD2 17
#define RXD3 27
#define TXD3 26
#define SW1 34
#define SW2 35
#define RELAY 25
#define LED_IO4 4
#define LED_IO12 12
#define SLID_SW 36
#define BUZZER 13
#define BUILTIN_LED 2
//#define LED_BUILTIN 2

    tiny32_v3(/* args */);
    void Relay(bool state);
    void RedLED(bool state);
    void BlueLED(bool state);
    void BuildinLED(bool state);
    void buzzer_beep(int times);
    bool Sw1(void);
    bool Sw2(void);
    bool Slid_sw(void);
    void library_version(void);

private:
    uint8_t _resolution_bit;
    uint16_t crc16_update(uint16_t crc, uint8_t a);

public:
    void TickBlueLED(float second);
    void TickRedLED(float second);
    void TickBuildinLED(float second);
    bool PWM_Setup(uint8_t channel, double freq, uint8_t resolution_bit, uint8_t pin);
    bool PWM_Drive(uint8_t channel, uint8_t percentage);
    bool Frequency_Out(uint8_t pin, double freq);
    uint16_t TimeStamp_minute_encode(uint16_t y, uint8_t m, uint8_t d, uint8_t h, uint8_t mi);
    uint16_t TimeStamp_24hr_encode(uint16_t h, uint16_t mi);
    void TimeStamp_hour_minute_decode(uint16_t timestemp, uint16_t &h, uint16_t &mi);

private:
    uint16_t ec_modbusRTU(uint8_t id);
    bool ec_modbusRTU_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);

public:
    /* PZEM-016 Modbus RTU AC power meter module */
    bool PZEM_016(uint8_t id, float &volt, float &amp, float &power, uint32_t &energy, float &freq, float &pf);
    float PZEM_016_Volt(uint8_t id);
    float PZEM_016_Amp(uint8_t id);
    float PZEM_016_Power(uint8_t id);
    int16_t PZEM_016_Energy(uint8_t id);
    float PZEM_016_Freq(uint8_t id);
    float PZEM_016_PF(uint8_t id);
    bool PZEM_016_ResetEnergy(uint8_t id);
    int8_t PZEM_016_SetAddress(uint8_t id, uint8_t new_id);
    int8_t PZEM_016_SearchAddress(void);
    bool PZEM_016_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);

    /* PZEM-003 Modbus RTU DC power meter module */
    bool PZEM_003(uint8_t id, float &volt, float &amp, float &power, uint32_t &energy);
    float PZEM_003_Volt(uint8_t id);
    float PZEM_003_Amp(uint8_t id);
    float PZEM_003_Power(uint8_t id);
    int16_t PZEM_003_Energy(uint8_t id);
    bool PZEM_003_ResetEnergy(uint8_t id);
    int8_t PZEM_003_SetAddress(uint8_t id, uint8_t new_id);
    int8_t PZEM_003_SearchAddress(void);
    bool PZEM_003_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);

    /* WTR10-E Modbus RTU Temperature and Humidity sensor module */
    bool WTR10_E_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    bool WTR10_E(uint8_t id, float &temp, float &humi);
    float WTR10_E_tempeature(uint8_t id);
    float WTR10_E_humidity(uint8_t id);

    /* XY-MD02 Modbus RTU Temperature and Humidity sensor module */
    bool XY_MD02_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    bool XY_MD02(uint8_t id, float &temp, float &humi);
    float XY_MD02_tempeature(uint8_t id);
    float XY_MD02_humidity(uint8_t id);
    int8_t XY_MD02_searchAddress(void);
    int8_t XY_MD02_SetAddress(uint8_t id, uint8_t new_id);

    /* SOIL MOISTURE PR-3000-H-N01 sensor (RS485) module */
    bool PR3000_H_N01_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    bool PR3000_H_N01(float &temp, float &humi);
    float PR3000_H_N01_tempeature();
    float PR3000_H_N01_humidity();

    /* RS485 Water Flow Meter RS485 MODBUS output  */
    bool WATER_FLOW_METER_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t WATER_FLOW_METER_searchAddress(void);
    int8_t WATER_FLOW_METER_SetAddress(uint8_t id, uint8_t new_id);
    float WATER_FLOW_METER(uint8_t id);

    /* PYR20-Solar Radiation/Pyranometer Sensor, RS485, Modbus */
    bool PYR20_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t PYR20_searchAddress(void);
    int8_t PYR20_SetAddress(uint8_t id, uint8_t new_id);
    int16_t PYR20_read(uint8_t id);

    /* tiny32 ModbusRTU communication*/
    bool tiny32_ModbusRTU_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t tiny32_ModbusRTU_searchAddress(void);
    int8_t tiny32_ModbusRTU_setAddress(uint8_t id, uint8_t new_id);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8, float &val9, float &val10);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8, float &val9);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2);
    bool tiny32_ModbusRTU(uint8_t id, float &val1);

    /* Enenergic ModbusRTU PowerMeter*/
    bool ENenergic_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t ENenergic_searchAddress(void);
    int8_t ENenergic_setAddress(uint8_t id, uint8_t new_id);
    float ENenergic_getTemperature(uint8_t id);
    bool ENenergic_Volt_L_N(uint8_t id, float &L1_N, float &L2_N, float &L3_N);
    bool ENenergic_Volt_L_L(uint8_t id, float &L1_L2, float &L2_L3, float &L3_L1);
    bool ENenergic_Current_L(uint8_t id, float &L1, float &L2, float &L3);
    float ENenergic_NeutralCurrent(uint8_t id);
    float ENenergic_Freq(uint8_t id);
    bool ENenergic_PhaseVolt_Angle(uint8_t id, float &L1, float &L2, float &L3);
    bool ENenergic_PhaseCurrent_Angle(uint8_t id, float &L1, float &L2, float &L3);

    /* Schneider EasyLogic PM2xxx Digital Power Meter */
    bool SchneiderPM2xxx_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t SchneiderPM2xxx_searchAddress(void);

    bool SchneiderPM2xxx_MeteringSetup(void);

    float SchneiderPM2xxx_CurrentA(uint8_t id);
    float SchneiderPM2xxx_CurrentB(uint8_t id);
    float SchneiderPM2xxx_CurrentC(uint8_t id);
    float SchneiderPM2xxx_CurrentN(uint8_t id);
    float SchneiderPM2xxx_CurrentG(uint8_t id);
    float SchneiderPM2xxx_CurrentAvg(uint8_t id);
    float SchneiderPM2xxx_CurrentUnblanceA(uint8_t id);
    float SchneiderPM2xxx_CurrentUnblanceB(uint8_t id);
    float SchneiderPM2xxx_CurrentUnblanceC(uint8_t id);
    float SchneiderPM2xxx_CurrentUnblanceWorst(uint8_t id);

    float SchneiderPM2xxx_Voltage_AB(uint8_t id);
    float SchneiderPM2xxx_Voltage_BC(uint8_t id);
    float SchneiderPM2xxx_Voltage_CA(uint8_t id);
    float SchneiderPM2xxx_Voltage_LL_Avg(uint8_t id);
    float SchneiderPM2xxx_Voltage_AN(uint8_t id);
    float SchneiderPM2xxx_Voltage_BN(uint8_t id);
    float SchneiderPM2xxx_Voltage_CN(uint8_t id);
    float SchneiderPM2xxx_Voltage_LN_Avg(uint8_t id);

    float SchneiderPM2xxx_VoltageUnblance_AB(uint8_t id);
    float SchneiderPM2xxx_VoltageUnblance_BC(uint8_t id);
    float SchneiderPM2xxx_VoltageUnblance_CA(uint8_t id);
    float SchneiderPM2xxx_VoltageUnblance_LL_Worst(uint8_t id);
    float SchneiderPM2xxx_VoltageUnblance_AN(uint8_t id);
    float SchneiderPM2xxx_VoltageUnblance_BN(uint8_t id);
    float SchneiderPM2xxx_VoltageUnblance_CN(uint8_t id);
    float SchneiderPM2xxx_VoltageUnblance_LN_Worst(uint8_t id);

    float SchneiderPM2xxx_ActivePowerA(uint8_t id);
    float SchneiderPM2xxx_ActivePowerB(uint8_t id);
    float SchneiderPM2xxx_ActivePowerC(uint8_t id);
    float SchneiderPM2xxx_ActivePowerTotal(uint8_t id);

    float SchneiderPM2xxx_ReactivePowerA(uint8_t id);
    float SchneiderPM2xxx_ReactivePowerB(uint8_t id);
    float SchneiderPM2xxx_ReactivePowerC(uint8_t id);
    float SchneiderPM2xxx_ReactivePowerTotal(uint8_t id);

    float SchneiderPM2xxx_ApparentPowerA(uint8_t id);
    float SchneiderPM2xxx_ApparentPowerB(uint8_t id);
    float SchneiderPM2xxx_ApparentPowerC(uint8_t id);
    float SchneiderPM2xxx_ApparentPowerTotal(uint8_t id);

    float SchneiderPM2xxx_PowerFactorA(uint8_t id);
    float SchneiderPM2xxx_PowerFactorB(uint8_t id);
    float SchneiderPM2xxx_PowerFactorC(uint8_t id);
    float SchneiderPM2xxx_PowerFactorTotal(uint8_t id);

    float SchneiderPM2xxx_Freq(uint8_t id);

    /* EASTRON SDM120CT Modbus 1-Phase Powermeter */
    bool SDM120CT_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t SDM120CT_searchAddress(void);
    float SDM120CT_Volt(uint8_t id);
    float SDM120CT_Freq(uint8_t id);
    float SDM120CT_Power(uint8_t id);
    float SDM120CT_Current(uint8_t id);
    float SDM120CT_Total_Energy(uint8_t id);
    float SDM120CT_POWER_FACTOR(uint8_t id);

    /* Wind speed sensor [PR-3000FSJT-N01] */
    bool tiny32_WIND_RSFSN01_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t tiny32_WIND_RSFSN01_searchAddress(void);
    int8_t tiny32_WIND_RSFSN01_setAddress(uint8_t id, uint8_t new_id);
    float tiny32_WIND_RSFSN01_SPEED(uint8_t id);

    /* EASTRON SDM630MCT Modbus 3-Phase Powermeter */
    bool SDM630MCT_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t SDM630MCT_searchAddress(void);

    float SDM630MCT_P1_Volt(uint8_t id); // 30000 - 30001 [ID 04 00 00 00 02 ]
    float SDM630MCT_P2_Volt(uint8_t id); // 30002 - 30003 [ID 04 00 02 00 02 ]
    float SDM630MCT_P3_Volt(uint8_t id); // 30004 - 30005 [ID 04 00 04 00 02 ]

    float SDM630MCT_P1_Current(uint8_t id); // 30006 - 30007 [ID 04 00 06 00 02 ]
    float SDM630MCT_P2_Current(uint8_t id); // 30008 - 30009 [ID 04 00 08 00 02 ]
    float SDM630MCT_P3_Current(uint8_t id); // 300A0 - 300A1 [ID 04 00 0A 00 02 ]

    float SDM630MCT_P1_Watt(uint8_t id); // 300C0 - 3000D [ID 04 00 0C 00 02 ]
    float SDM630MCT_P2_Watt(uint8_t id); // 3000E - 3000F [ID 04 00 0E 00 02 ]
    float SDM630MCT_P3_Watt(uint8_t id); // 30010 - 30011 [ID 04 00 10 00 02 ]

    float SDM630MCT_P1_VA(uint8_t id); // 30012 - 30013 [ID 04 00 12 00 02 ]
    float SDM630MCT_P2_VA(uint8_t id); // 30014 - 30015 [ID 04 00 14 00 02 ]
    float SDM630MCT_P3_VA(uint8_t id); // 30016 - 30017 [ID 04 00 16 00 02 ]

    float SDM630MCT_P1_VAr(uint8_t id); // 30018 - 30019 [ID 04 00 18 00 02 ]
    float SDM630MCT_P2_VAr(uint8_t id); // 3001A - 3001B [ID 04 00 1A 00 02 ]
    float SDM630MCT_P3_VAr(uint8_t id); // 3001C - 3001D [ID 04 00 1C 00 02 ]

    float SDM630MCT_P1_PF(uint8_t id); // 3001E - 3001F [ID 04 00 1E 00 02 ]
    float SDM630MCT_P2_PF(uint8_t id); // 30020 - 30021 [ID 04 00 20 00 02 ]
    float SDM630MCT_P3_PF(uint8_t id); // 30022 - 30023 [ID 04 00 22 00 02 ]

    float SDM630MCT_Freq(uint8_t id); // 30046 - 30047 [ID 04 00 46 00 02 ]

    float SDM630MCT_Sum_Current(uint8_t id); // 30030 - 30031 [ID 04 00 30 00 02 ]
    float SDM630MCT_Total_Watt(uint8_t id);  // 30034 - 30035 [ID 04 00 34 00 02 ]
    float SDM630MCT_Total_VA(uint8_t id);    // 300057 - 30058 [ID 04 00 38 00 02 ]
    float SDM630MCT_Total_VAr(uint8_t id);   // 30061 - 30062 [ID 04 00 3C 00 02 ]

    /* Chiller R717 ModbusRTU for Read sensor */
    bool CHILLER_R717_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);

    float CHILLER_R717_AI01_CHILLED_IN(uint8_t id);
    float CHILLER_R717_AI02_CHILLED_OUT(uint8_t id);
    float CHILLER_R717_AI03_COOLED_IN(uint8_t id);
    float CHILLER_R717_AI04_COOLED_OUT(uint8_t id);
    float CHILLER_R717_AI05_SUCTION_TEMP(uint8_t id);

    float CHILLER_R717_AI06_DISCHARGE_TEMP(uint8_t id);
    float CHILLER_R717_AI08_COND_PRESS(uint8_t id);
    float CHILLER_R717_AI10_EVAP_PRESS(uint8_t id);
    float CHILLER_R717_Slurry1_Temp(uint8_t id);
    float CHILLER_R717_Slurry2_Temp(uint8_t id);

    float CHILLER_R717_Slurry3_Temp(uint8_t id);
    float CHILLER_R717_Slurry4_Temp(uint8_t id);
    float CHILLER_R717_Coil_Temp(uint8_t id);
    float CHILLER_R717_Room_Temp(uint8_t id);
    float CHILLER_R717_CURRENT_COMP(uint8_t id);

    float CHILLER_R717_VOLT_COMP(uint8_t id);
    float CHILLER_R717_FREQ_COMP(uint8_t id);
    float CHILLER_R717_POWER_COMP(uint8_t id);
    float CHILLER_R717_PER_COMP(uint8_t id);
    float CHILLER_R717_HOUR_CHILLED_PUMP(uint8_t id);

    float CHILLER_R717_HOUR_COMP(uint8_t id);
    float CHILLER_R717_HOUR_COOLED_PUMP(uint8_t id);
    float CHILLER_R717_HOUR_COOLING_TOWER(uint8_t id);
    float CHILLER_R717_SP_ROOM(uint8_t id);
    float CHILLER_R717_TOTAL_KW(uint8_t id);

    /* Inverter ATESS ModbusRTU for Read parameter */
    bool ATESS_R717_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    
    float ATESS_Power_PV_kW(uint8_t id);
    float ATESS_Power_bat_kW(uint8_t id);
    float ATESS_SOC(uint8_t id);
    float ATESS_ActivePower_Grid_kW(uint8_t id);
    float ATESS_ActivePower_Load_kW(uint8_t id);
    float ATESS_Energy_PVToday_kWh(uint8_t id);
    float ATESS_Energy_BatChargeToday_kWh(uint8_t id);
    float ATESS_Energy_BatDischargeToday_kWh(uint8_t id);
    float ATESS_Energy_GridOutToday_kWh(uint8_t id);
    float ATESS_Energy_GridInToday_kWh(uint8_t id);
    float ATESS_Energy_LoadToday_kWh(uint8_t id);
};
#endif
