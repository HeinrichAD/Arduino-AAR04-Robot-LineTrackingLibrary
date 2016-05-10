#include "AARLineTracking.h"

void AARLineTrackingClass::Init()
{
    this->init();
    this->motor = new AARMotorClass();
}


void AARLineTrackingClass::Init(AARMotorClass* motor)
{
    this->init();
    this->motor = motor;
}


void AARLineTrackingClass::init()
{
    pinMode(PIN_LINE_TRACKING_LED, OUTPUT);
}



uint16_t  AARLineTrackingClass::ReadSensorLeft()
{
    return this->ReadSensorLeft(true);
}


uint16_t  AARLineTrackingClass::ReadSensorLeft(bool analazeValue)
{
    int ledValue = HIGH;
    if (analazeValue) ledValue = digitalRead(PIN_LINE_TRACKING_LED); // Current value.
    if (!ledValue) digitalWrite(PIN_LINE_TRACKING_LED, HIGH); // Only needed if not already HIGH.
    this->sensorData[SENSOR_DATA_LEFT] = analogRead(PIN_LINE_TRACKING_SENSOR_LEFT);
    delay(10);
    if (!ledValue) digitalWrite(PIN_LINE_TRACKING_LED, LOW); // Back to LOW if this was the old value.
    return this->sensorData[SENSOR_DATA_LEFT];
}


uint16_t  AARLineTrackingClass::ReadSensorRight()
{
    return this->ReadSensorRight(true);
}


uint16_t  AARLineTrackingClass::ReadSensorRight(bool analazeValue)
{
    int ledValue = HIGH;
    if (analazeValue) ledValue = digitalRead(PIN_LINE_TRACKING_LED); // Current value.
    if (!ledValue) digitalWrite(PIN_LINE_TRACKING_LED, HIGH); // Only needed if not already HIGH.
    this->sensorData[SENSOR_DATA_RIGHT] = analogRead(PIN_LINE_TRACKING_SENSOR_RIGHT);
    delay(10);
    if (!ledValue) digitalWrite(PIN_LINE_TRACKING_LED, LOW); // Back to LOW if this was the old value.
    return this->sensorData[SENSOR_DATA_RIGHT];
}


uint16_t* AARLineTrackingClass::ReadSensors()
{
    return this->ReadSensors(true);
}


uint16_t* AARLineTrackingClass::ReadSensors(bool analazeValue)
{
    this->ReadSensorLeft(analazeValue);
    this->ReadSensorRight(analazeValue);
    return this->sensorData;
}



uint16_t  AARLineTrackingClass::SensorDataLeft()
{
    return this->sensorData[SENSOR_DATA_LEFT];
}


uint16_t  AARLineTrackingClass::SensorDataRight()
{
    return this->sensorData[SENSOR_DATA_RIGHT];
}


uint16_t* AARLineTrackingClass::SensorData()
{
    return this->sensorData;
}



void AARLineTrackingClass::Track(uint64_t durationMax)
{
    int ledValue = digitalRead(PIN_LINE_TRACKING_LED); // Current value.
    if (!ledValue) digitalWrite(PIN_LINE_TRACKING_LED, HIGH); // Only needed if not already HIGH.

    this->ReadSensors(false);

    if(sensorData[SENSOR_DATA_LEFT] < SENSOR_COLOR_BLACK) {
        Serial.print("LEFT: BLACK");
        digitalWrite(PIN_MOTOR_LEFT_FORWARD, LOW);
        motor->RightForward(0);
    }
    else {
        Serial.print("LEFT: WHITE");
        //motor->RightForward(100);
    }

    Serial.print("\t\t");

    if(sensorData[SENSOR_DATA_RIGHT] < SENSOR_COLOR_BLACK) {
        Serial.println("RIGHT: BLACK");
        digitalWrite(PIN_MOTOR_RIGHT_FORWARD, LOW);
        motor->LeftForward(0);
    }
    else {
        Serial.println("RIGHT: WHITE");
        //motor->LeftForward(100);
    }

    // Back to LOW if this was the old value.
    if (!ledValue) digitalWrite(PIN_LINE_TRACKING_LED, LOW);
}
