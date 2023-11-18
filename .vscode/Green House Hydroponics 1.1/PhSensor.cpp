#include "PHSensor.h"
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
float averagePH;
float lastPH;

// Konstanten und Variablen
const int phSensorPin = A1; // Beispiel: Pin A1 für den pH-Sensor

// Anzahl der Messungen für den Durchschnitt
const int numReadings = 10;
float readings[numReadings];    // Messwerte speichern
int readIndex = 0;              // Index des aktuellen Messwerts
float total = 0;                // Summe der Messwerte

// Ersetzen Sie diese mit Ihren Netzwerk- und IoT Cloud-Anmeldedaten
const char WIFI_SSID[] = "Ihr_WiFi_Name";
const char WIFI_PASSWORD[] = "Ihr_WiFi_Passwort";

// Cloud Variablen
float cloudPH;

void initPHSensor() {
    // Initialisierungslogik für den pH-Sensor (falls erforderlich)
}

float readPHSensor() {
    int sensorValue = analogRead(phSensorPin);
    // Konvertierung des Sensorwertes in pH-Wert
    // Diese Formel muss entsprechend Ihrem Sensor angepasst werden
    lastPH = map(sensorValue, 0, 1023, 0, 14);
    return lastPH;
}

void updatePHReadings() {
    // Entferne den ältesten Messwert aus der Summe
    total = total - readings[readIndex];

    // Lese den aktuellen pH-Wert und speichere ihn in 'readings'
    readings[readIndex] = readPHSensor();

    // Füge den aktuellen Messwert zur Summe hinzu
    total = total + readings[readIndex];

    // Fortschreiten zum nächsten Messwert im Array
    readIndex = readIndex + 1;

    // Wenn wir am Ende des Arrays angekommen sind, fangen wir wieder von vorne an
    if (readIndex >= numReadings) {
        readIndex = 0;
    }

    // Berechne den Durchschnitts-pH
    averagePH = total / numReadings;
    lastPH = readings[readIndex];
}

void initCloudConnection() {
    // Initialisiere die Netzwerkverbindung
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    // Initialisiere die Cloud-Verbindung
    initProperties();  // Diese Funktion wird automatisch generiert, wenn Sie Ihr Thing in der Arduino IoT Cloud erstellen
    ArduinoCloud.begin(ArduinoIoTPreferredConnection);
}

void updateCloudPH() {
    cloudPH = averagePH; // Nehmen Sie den Durchschnittswert von averagePH
    ArduinoCloud.update();
}

// Verbindung zu MariaDb
void connectToDatabase() {
    if (dbConn.connect(DB_HOST, 3306, DB_USER, DB_PASS)) {
        // Verbindung erfolgreich
    } else {
        // Verbindung fehlgeschlagen
    }
}

void savePHToDatabase() {
    if (dbConn.connected()) {
        MySQL_Cursor cur = MySQL_Cursor(&dbConn);
        char query[128];
        sprintf(query, "INSERT INTO ph_table (ph_value) VALUES (%f)", averagePH);
        cur.execute(query);
    }
}
