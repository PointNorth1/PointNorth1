#include "ECSensor.h"
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

// Definition der externen Variablen
float averageEC;
float lastEC;

// Konstanten und Variablen
const int ecSensorPin = A2; // Beispiel: Pin A2 für den EC-Sensor

// Anzahl der Messungen für den Durchschnitt
const int numReadings = 10;
float readings[numReadings];    // Messwerte speichern
int readIndex = 0;              // Index des aktuellen Messwerts
float total = 0;                // Summe der Messwerte

// Ersetzen Sie diese mit Ihren Netzwerk- und IoT Cloud-Anmeldedaten
const char WIFI_SSID[] = "Ihr_WiFi_Name";
const char WIFI_PASSWORD[] = "Ihr_WiFi_Passwort";

// Cloud Variablen
float cloudEC;

void initECSensor() {
    // Initialisierungslogik für den EC-Sensor (falls erforderlich)
}

float readECSensor() {
    int sensorValue = analogRead(ecSensorPin);
    // Konvertierung des Sensorwertes in EC-Wert
    // Diese Formel muss entsprechend Ihrem Sensor angepasst werden
    lastEC = map(sensorValue, 0, 1023, 0, 20); // Beispielkonvertierung
    return lastEC;
}

void updateECReadings() {
    // Entferne den ältesten Messwert aus der Summe
    total = total - readings[readIndex];

    // Lese den aktuellen EC-Wert und speichere ihn in 'readings'
    readings[readIndex] = readECSensor();

    // Füge den aktuellen Messwert zur Summe hinzu
    total = total + readings[readIndex];

    // Fortschreiten zum nächsten Messwert im Array
    readIndex = readIndex + 1;

    // Wenn wir am Ende des Arrays angekommen sind, fangen wir wieder von vorne an
    if (readIndex >= numReadings) {
        readIndex = 0;
    }

    // Berechne den Durchschnitts-EC
    averageEC = total / numReadings;
    lastEC = readings[readIndex];
}

void initCloudConnection() {
    // Initialisiere die Netzwerkverbindung
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    // Initialisiere die Cloud-Verbindung
    initProperties(); 
