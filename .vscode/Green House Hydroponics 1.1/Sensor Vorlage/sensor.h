#ifndef SENSORS_H
#define SENSORS_H

// Externe Variablen
extern float averageMoisture;  // Durchschnittswert der letzten 6 Messungen
extern float lastMoisture;     // Letzter Messwert

// Grundfunktionen
void initSensors();            // Initialisiert den Sensor
float readMoistureSensor();    // Liest den aktuellen Feuchtigkeitswert

// Zusätzliche Funktionen
void updateMoistureReadings(); // Aktualisiert die Feuchtigkeitsmessungen
void calculateAverageMoisture(); // Berechnet den Durchschnitt der letzten 6 Messungen

#endif
