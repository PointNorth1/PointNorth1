#ifndef PH_SENSOR_H
#define PH_SENSOR_H

#include <Arduino.h>
#include <WiFiNINA.h> // Für WiFi-Verbindung
#include <ArduinoIoTCloud.h> // Für die Arduino Cloud
#include <MySQL_Connection.h> // Für MariaDB Verbindung

// Externe Variablen
extern float averagePH;  // Durchschnittswert der letzten Messungen
extern float lastPH;     // Letzter pH-Messwert

// Grundfunktionen
void initPHSensor();            // Initialisiert den pH-Sensor
float readPHSensor();           // Liest den aktuellen pH-Wert

// Zusätzliche Funktionen
void updatePHReadings();        // Aktualisiert die pH-Messungen
void calculateAveragePH();      // Berechnet den Durchschnitts-pH

// Funktionen für die Verbindung zur Arduino Cloud und MariaDB
void initCloudConnection();     // Initialisiert die Verbindung zur Arduino Cloud
void updateCloudPH();           // Aktualisiert den pH-Wert in der Arduino Cloud
void connectToDatabase();       // Stellt eine Verbindung zur MariaDB-Datenbank her
void savePHToDatabase();        // Speichert den pH-Wert in der MariaDB-Datenbank

#endif
