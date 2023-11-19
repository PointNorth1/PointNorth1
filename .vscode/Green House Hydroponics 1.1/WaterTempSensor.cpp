#include "TemperatureSensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>
#include "ArduinoIoTCloud.h"
#include "WiFiNINA.h"
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// Netzwerk-Client
WiFiClient client;

// Datenbankverbindungsdaten
const char DB_HOST[] = "IP_der_Datenbank";
const char DB_USER[] = "Datenbank_Benutzer";
const char DB_PASS[] = "Datenbank_Passwort";

MySQL_Connection dbConn(&client);

// Ersetzen Sie diese mit Ihren Cloud- und Datenbankverbindungsinformationen
extern float cloudTemperature;
extern MySQL_Connection dbConn;

// Sensor-Bibliotheken initialisieren
OneWire oneWire(_pin);
DallasTemperature sensors(&oneWire);

TemperatureSensor::TemperatureSensor(int pin) : _pin(pin) {
}

void TemperatureSensor::init() {
    sensors.begin();  // Startet die Kommunikation mit dem Sensor
}

float TemperatureSensor::readTemperature() {
    sensors.requestTemperatures(); // Sendet die Anforderung, die Temperatur zu lesen
    _lastTemperatureReading = sensors.getTempCByIndex(0); // Liest die Temperatur
    return _lastTemperatureReading;
}

void TemperatureSensor::updateTemperatureReadings() {
    float temp = readTemperature();
    // Implementieren Sie hier die Logik, um den Durchschnittswert zu berechnen, falls erforderlich

    sendDataToCloud();
    saveDataToDatabase();
}

void TemperatureSensor::sendDataToCloud() {
    cloudTemperature = _lastTemperatureReading; // Aktualisiert die Cloud-Variable
    // Fügen Sie hier den Code ein, um die Daten an die Cloud zu senden
}

void TemperatureSensor::saveDataToDatabase() {
    if (dbConn.connected()) {
        MySQL_Cursor cur = MySQL_Cursor(&dbConn);
        char query[128];
        sprintf(query, "INSERT INTO temperature_table (temperature) VALUES (%f)", _lastTemperatureReading);
        cur.execute(query);
    }
    // Fügen Sie hier den Code für Fehlerbehandlung und Wiederverbindungsversuche hinzu
}
