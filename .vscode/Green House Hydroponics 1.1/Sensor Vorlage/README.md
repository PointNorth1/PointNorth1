# Überblick

Dieses Sensor-Modul ist Teil eines Arduino-Projekts, das darauf abzielt, Feuchtigkeitsdaten zu erfassen, zu verarbeiten und an verschiedene Dienste wie die Arduino Cloud und eine MariaDB-Datenbank zu senden.

## Funktionen

- `initSensors()`: Initialisiert den Feuchtigkeitssensor.
- `readMoistureSensor()`: Liest den aktuellen Feuchtigkeitswert des Sensors.
- `updateThreshold(float newThreshold)`: Aktualisiert den Schwellenwert für Feuchtigkeit.
- `sendToCloud(float moistureValue)`: Sendet die Feuchtigkeitswerte an die Arduino Cloud. **Hinweis:** Diese Funktion muss basierend auf dem spezifischen Cloud-Setup konfiguriert werden.
- `sendToDatabase(float moistureValue)`: Sendet die Feuchtigkeitswerte an eine MariaDB-Datenbank. **Wichtig:** Konfigurationsdetails wie `ssid`, `pass`, `user`, `password` und `INSERT_SQL` müssen korrekt gesetzt werden.
- `onMoistureThresholdChange()`: Wird aufgerufen, wenn der Feuchtigkeitsschwellenwert in der Cloud geändert wird.

## Konfiguration

Stellen Sie sicher, dass alle erforderlichen Bibliotheken in Ihr Arduino-Projekt eingebunden sind. Überprüfen Sie die Konfigurationsdetails, insbesondere:

- Datenbank-Zugangsdaten
- Cloud-Property-Namen
- Netzwerkeinstellungen (SSID und Passwort für WLAN)

## Installation

1. Binden Sie die erforderlichen Bibliotheken in Ihr Arduino-Projekt ein.
2. Definieren Sie die Netzwerkkonfiguration und Datenbank-Zugangsdaten.
3. Laden Sie den Code auf Ihr Arduino-Gerät.

## Netzwerkverbindung und Ausnahmebehandlung

- Stellen Sie sicher, dass die Netzwerkverbindung stabil ist.
- Implementieren Sie eine angemessene Ausnahmebehandlung für alle Netzwerkoperationen, um Ausfälle und Fehler zu handhaben.
