#include "UltrasonicSensor.h"
#include <ArduinoIoTCloud.h>
#include <WiFiNINA.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// Netzwerk- und Datenbank-Verbindungsinformationen
extern WiFiClient client;
extern MySQL_Connection dbConn;

// Externe Variablen für Cloud und Datenbank
extern float cloudWaterLevel;
extern char ssid[];
extern char pass[];
extern char user[];
extern char password[];
extern char INSERT_SQL[];

// Tankmaße in Zentimetern
const float tankLength = 40; // Länge
const float tankWidth = 30;  // Breite
const float tankHeight = 30; // Höhe

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin) 
    : _triggerPin(triggerPin), _echoPin(echoPin) {
}

void UltrasonicSensor::init() {
    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

float UltrasonicSensor::readDistance() {
    digitalWrite(_triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_triggerPin, LOW);
    
    long duration = pulseIn(_echoPin, HIGH);
    float distance = duration * 0.034 / 2; // Umrechnung in Zentimeter
    return distance;
}

float UltrasonicSensor::calculateVolumeInLiters(float distance) {
    float waterHeight = tankHeight - distance; // Berechnen Sie die Höhe des Wassers
    return (tankLength * tankWidth * waterHeight) / 1000.0; // Volumen in Litern
}

void UltrasonicSensor::updateDistanceReadings() {
    float distance = readDistance();
    float volume = calculateVolumeInLiters(distance);
    
    // Cloud-Update
    cloudWaterLevel = volume;
    sendDataToCloud();

    // Datenbank-Update
    saveDataToDatabase(volume);
}

void UltrasonicSensor::sendDataToCloud() {
    // Code zum Senden an die Cloud
    // Implementieren Sie die Logik gemäß Ihrer Cloud-Konfiguration
}

void UltrasonicSensor::saveDataToDatabase(float volume) {
    if (dbConn.connected()) {
        MySQL_Cursor cur = MySQL_Cursor(&dbConn);
        char query[128];
        sprintf(query, "INSERT INTO water_level_table (volume) VALUES (%f)", volume);
        cur.execute(query);
    }
    // Implementieren Sie Fehlerbehandlung und Wiederverbindungsversuche
}
