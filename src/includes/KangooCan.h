#pragma once
#include <iostream>
using namespace std;
class KangooCan
{
  public:
    KangooCan();
    bool ProcessISOTPResponse(const uint8_t* data);
    bool handlePID61Frame(const uint8_t* data);
    bool handlePID66Frame(const uint8_t* data);
    bool handlePID03Frame(const uint8_t* data);
    bool handlePID04Frame(const uint8_t* data);
    bool handlePID41Frame(const uint8_t* data);
    bool handlePID42Frame(const uint8_t* data);
    bool handlePID01Frame(const uint8_t* data);

    void handleFrame155(const uint8_t* data);
    void handleFrame424(const uint8_t* data);
    void handleFrame425(const uint8_t* data);

    void printData();

  private:
    uint8_t currentPID;
    uint16_t byteCount;
    uint16_t remainingByteCount;
    bool looped;

    //data from frames
    int16_t batteryTemperature;
    uint32_t ampHoursRaw;
    uint16_t packHealthRaw;
    uint16_t quickchargeCount;
    uint16_t normalchargeCount;
    uint16_t fullchargeCount;
    uint16_t partialchargeCount;
    uint32_t totalKilometers;
    uint32_t lowestMilV;
    uint32_t highestMilV;
    uint16_t maxChargingRaw;
    uint16_t cellVoltages[96];
    uint16_t packVoltage;
    uint16_t daigPackVoltage;
    uint16_t maxInputPowerRaw;
    uint16_t maxOutputPowerRaw;
    int32_t batteryCurrent;


    //data from free can messages
    float stateOfCharge;
    float stateOfHealth;
    float lowestCellVolt;
    float highestCellVolt;
    float remainingKHW;

    uint8_t lowestCellTemp;
    uint8_t highestCellTemp;
    uint16_t maxCharging;
    uint16_t maxInputPower;
    uint16_t maxOutputPower;


};