#ifndef EC_SENSOR_H
#define EC_SENSOR_H

#include <Arduino.h>
#include <WiFiNINA.h> // Für WiFi-Verbindung
#include <ArduinoIoTCloud.h> // Für die Arduino Cloud
#include <MySQL_Connection.h> // Für MariaDB Verbindung

// Externe Variablen
extern float averageEC;  // Durchschnittswert der letzten Messungen
extern float lastEC;     // Letzter EC-Messwert

// Grundfunktionen
void initECSensor();            // Initialisiert den EC-Sensor
float readECSensor();           // Liest den aktuellen EC-Wert

// Zusätzliche Funktionen
void updateECReadings();        // Aktualisiert die EC-Messungen
void calculateAverageEC();      // Berechnet den Durchschnitts-EC

// Funktionen für die Verbindung zur Arduino Cloud und MariaDB
void initCloudConnection();     // Initialisiert die Verbindung zur Arduino Cloud
void updateCloudEC();           // Aktualisiert den EC-Wert in der Arduino Cloud
void connectToDatabase();       // Stellt eine Verbindung zur MariaDB-Datenbank her
void saveECToDatabase();        // Speichert den EC-Wert in der MariaDB-Datenbank

#endif
