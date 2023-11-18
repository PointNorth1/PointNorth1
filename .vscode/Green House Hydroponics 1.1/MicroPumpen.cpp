#include "PumpControl.h"

PumpControl::PumpControl(int oxygenPumpPin, int mainPumpPin, int dripIrrigationPumpPin, int phPlusPin, int phMinusPin, int enzymePin, int growthNutrientPin, int bloomNutrientPin, int boosterNutrientPin)
    : _mainPumpPin(mainPumpPin), _oxygenPumpPin(oxygenPumpPin), _dripIrrigationPumpPin(dripIrrigationPumpPin), _phPlusPin(phPlusPin), _phMinusPin(phMinusPin), _enzymePin(enzymePin),
      _growthNutrientPin(growthNutrientPin), _bloomNutrientPin(bloomNutrientPin), _boosterNutrientPin(boosterNutrientPin) {
}
void PumpControl::activateOxygenPump() {
    digitalWrite(_oxygenPumpPin, HIGH);
}

void PumpControl::deactivateOxygenPump() {
    digitalWrite(_oxygenPumpPin, LOW);
}

void PumpControl::manageOxygenPumpCycle() {
    static unsigned long lastCycleTime = 0;
    unsigned long currentMillis = millis();

    if ((currentMillis - lastCycleTime >= 3600000) || (lastCycleTime == 0)) { // 60 Minuten (30 Minuten On + 30 Minuten Off) oder erstmaliger Start
        lastCycleTime = currentMillis; // Zyklus starten
    }

    if (currentMillis - lastCycleTime < 1800000) { // Erste 30 Minuten des Zyklus
        activateOxygenPump();
    } else if (currentMillis - lastCycleTime >= 1800000) { // Zweite 30 Minuten des Zyklus
        deactivateOxygenPump();
    }
}

void PumpControl::activateMainPump() {
    digitalWrite(_mainPumpPin, HIGH);
}

void PumpControl::deactivateMainPump() {
    digitalWrite(_mainPumpPin, LOW);
}

void PumpControl::activateDripIrrigationPump() {
    digitalWrite(_dripIrrigationPumpPin, HIGH);
}

void PumpControl::deactivateDripIrrigationPump() {
    digitalWrite(_dripIrrigationPumpPin, LOW);
}

void PumpControl::manageDripIrrigationCycle() {
    static unsigned long lastActivationTime = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - lastActivationTime >= 1800000) {
        activateDripIrrigationPump();
        lastActivationTime = currentMillis;
    } else if (currentMillis - lastActivationTime >= 2700000) {
        deactivateDripIrrigationPump();
    }
}

void PumpControl::activatePhPlusPump() {
    activatePump(_phPlusPin);
}

void PumpControl::activatePhMinusPump() {
    activatePump(_phMinusPin);
}

void PumpControl::activateEnzymePump() {
    activatePump(_enzymePin);
}

void PumpControl::activateGrowthNutrientPump() {
    activatePump(_growthNutrientPin);
}

void PumpControl::activateBloomNutrientPump() {
    activatePump(_bloomNutrientPin);
}

void PumpControl::activateBoosterNutrientPump() {
    activatePump(_boosterNutrientPin);
}

void PumpControl::activatePump(int pin) {
    digitalWrite(pin, HIGH); // Relais aktivieren (Pumpe einschalten)
    delay(5000);             // 5 Sekunden warten (5000 Millisekunden)
    digitalWrite(pin, LOW);  // Relais deaktivieren (Pumpe ausschalten)
}

void PumpControl::deactivateMainPump(int pin) {
    digitalWrite(pin, LOW);
}