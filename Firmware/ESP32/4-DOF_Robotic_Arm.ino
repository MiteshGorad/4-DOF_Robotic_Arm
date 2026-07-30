#include "config.h"
#include "servoControl.h"

void setup()
{
    Serial.begin(115200);

    initServos();

    Serial.println("4-DOF Robot Arm");
    Serial.println("Manual Mode");
}

void loop()
{
    readPotentiometers();

    updateServos();

    printServoData();

    delay(10);
}
