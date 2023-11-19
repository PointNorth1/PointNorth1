#include "UltrasonicSensor.h"

#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>

class UltrasonicSensor {
public:
    UltrasonicSensor(int triggerPin, int echoPin); // Konstruktor mit Pin-Angaben

    void init();                       // Initialisiert den Ultraschallsensor
    float readDistance();              // Liest den aktuellen Abstand (Wasserstand)
    float calculateVolumeInLiters(float distance); // Berechnet das Volumen in Litern

    void updateDistanceReadings();     // Aktualisiert die Distanzmessungen und verarbeitet sie
    void sendDataToCloud();            // Sendet die Distanzdaten an die Cloud
    void saveDataToDatabase(float volume); // Speichert die Distanzdaten in der MariaDB-Datenbank

private:
    int _triggerPin, _echoPin;         // Pins für den Ultraschallsensor
    float _lastDistanceReading;        // Letzter Abstandmesswert
};

#endif
