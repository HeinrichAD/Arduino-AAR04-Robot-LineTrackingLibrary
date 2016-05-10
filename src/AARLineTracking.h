/******************************************************************************
 * AREXX AAR-04 ARDUINO ROBOT
 * AARobot line tracking class.
 *
 ******************************************************************************
 * Autors
 * HeinrichAD
 *
 ******************************************************************************
 * License
 * GNU General Public License v3.0, see LICENSE file.
 *
 ******************************************************************************
 * Source code
 * **GIT REPOSITORY URL**
 *
******************************************************************************/


#ifndef _AARLINETRACKING_h
#define _AARLINETRACKING_h

#include "AARMotor.h"
//#include "AARPins.h" // Already included in AARMotor.

/**
 * AAR Robot line tracking class.
**/
class AARLineTrackingClass
{
private:
    static const uint8_t LINE_TRACKING_DEAFULT_SPEED = 0x8F;
    static const uint8_t SENSOR_COUNT                = 2;
    static const int8_t  TRACK_BUFFER                = 4;

    uint16_t sensorData[SENSOR_COUNT];

    uint16_t  ReadSensorLeft(bool skipRead);
    uint16_t  ReadSensorRight(bool skipRead);
    uint16_t* ReadSensors(bool skipRead);

    AARMotorClass* motor;

    void init();


public:
    static const uint8_t SENSOR_DATA_LEFT  = 0;
    static const uint8_t SENSOR_DATA_RIGHT = 1;

    void Init();
    void Init(AARMotorClass* motor);

    uint16_t  ReadSensorLeft();
    uint16_t  ReadSensorRight();
    uint16_t* ReadSensors();

    uint16_t  SensorDataLeft();
    uint16_t  SensorDataRight();
    uint16_t* SensorData();

    void Track(uint64_t durationMax);
};

#endif
