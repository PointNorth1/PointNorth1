#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <Arduino.h>

class TemperatureSensor {
public:
    TemperatureSensor(int pin); // Konstruktor mit Angabe des Sensor-Pins

    void init();                       // Initialisiert den Temperatursensor
    float readTemperature();           // Liest die aktuelle Temperatur

    void updateTemperatureReadings();  // Aktualisiert die Temperaturmessungen
    void sendDataToCloud();            // Sendet die Temperaturdaten an die Cloud
    void saveDataToDatabase();         // Speichert die Temperaturdaten in der MariaDB-Datenbank

private:
    int _pin;                          // Pin, an dem der Sensor angeschlossen ist
    float _lastTemperatureReading;     // Letzter Temperaturmesswert
};

#endif
