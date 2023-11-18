#include "Sensors.h"
#include <Arduino.h>
#include <ArduinoIoTCloud.h>
#include <WiFiNINA.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// Externe Netzwerkvariablen
extern WiFiClient client;
extern MySQL_Connection conn((Client *)&client);
extern char ssid[];
extern char pass[];
extern char user[];
extern char password[];
extern char INSERT_SQL[];

const int moistureSensorPin = A0; // Pin des Feuchtigkeitssensors
float moistureThreshold = 300.0; // Standard-Schwellenwert für Feuchtigkeit

void initSensors() {
    pinMode(moistureSensorPin, INPUT); // Initialisiere den Sensorpin als Eingang
}

float readMoistureSensor() {
    return analogRead(moistureSensorPin); // Lese den Wert des Sensors
}

void updateThreshold(float newThreshold) {
    moistureThreshold = newThreshold;
}

void sendToCloud(float moistureValue) {
    // Funktion, um die Feuchtigkeitswerte an die Arduino Cloud zu senden
    // Beispiel: ArduinoCloud.addProperty(moistureValue, READWRITE, ON_CHANGE, NULL);
    // ...
}

void sendToDatabase(float moistureValue) {
    if (conn.connect(ssid, pass)) {
// Verbindung zur Datenbank herstellen
        MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

        // Bereite das SQL-Statement vor
        char query[128];
        sprintf(query, INSERT_SQL, moistureValue);

        // Führe das SQL-Statement aus
        cur_mem->execute(query);
        delete cur_mem;
        conn.close();
    }
}

void onMoistureThresholdChange() {
    float newMoistureThreshold = ArduinoIoTCloud.getProperty(moistureThreshold);
    updateThreshold(newMoistureThreshold);
}

void updateMoistureReadings() {
    unsigned long currentTime = millis();
    if (currentTime - lastMeasurementTime >= measurementInterval) {
        lastMeasurementTime = currentTime;

        for (int i = 0; i < 5; i++) {
            moistureReadings[i] = moistureReadings[i + 1];
        }

        moistureReadings[5] = readMoistureSensor();
        lastMoisture = moistureReadings[5];
        calculateAverageMoisture();
    }
}

void calculateAverageMoisture() {
    float sum = 0.0;
    for (int i = 0; i < 6; i++) {
        sum += moistureReadings[i];
    }
    averageMoisture = sum / 6.0;
}
