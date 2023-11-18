#ifndef PUMP_CONTROL_H
#define PUMP_CONTROL_H

#include <Arduino.h>

class PumpControl {
public:
    PumpControl(int dripIrrigationPumpPin, int mainPumpPin, int oxygenPumpPin, int phPlusPin, int phMinusPin, int enzymePin, int growthNutrientPin, int bloomNutrientPin, int boosterNutrientPin);

// Pumpen laufen 5 sekunden bei Aktivierung
    void activatePhPlusPump();      // Aktiviert die Pumpe für PH Plus Konzentrat
    void activatePhMinusPump();     // Aktiviert die Pumpe für PH Minus Konzentrat
    void activateEnzymePump();      // Aktiviert die Pumpe für Enzyme Konzentrat
    void activateGrowthNutrientPump(); // Aktiviert die Pumpe für Wachstumsdünger
    void activateBloomNutrientPump();  // Aktiviert die Pumpe für Blütendünger
    void activateBoosterNutrientPump(); // Aktiviert die Pumpe für Booster Dünger
    
    // MainPump aktivieren/deaktivieren und Tröpfchenbewässerung 30min an 15 min pause
    void activateMainPump();       // Aktiviert die Hauptpumpe
    void deactivateMainPump();     // Deaktiviert die Hauptpumpe
    void activateDripIrrigationPump(); // Aktiviert die Tröpfchenbewässerungspumpe
    void deactivateDripIrrigationPump(); // Deaktiviert die Tröpfchenbewässerungspumpe
    void manageDripIrrigationCycle(); // Verwaltet den Zyklus der Tröpfchenbewässerungspumpe
    
    // Sauerstoff Pumpe wenn aktiv dann 30 min pumpen und 30 min Pause
    void activateOxygenPump(); // Aktiviert die Sauerstoffpumpe
    void deactivateOxygenPump(); // Deaktiviert die Sauerstoffpumpe
    void manageOxygenPumpCycle(); // Verwaltet den Zyklus der Sauerstoffpumpe

private:
    int _dripIrrigationPumpPin, int _mainPumpPin, _oxygenPumpPin, int _phPlusPin, _phMinusPin, _enzymePin, _growthNutrientPin, _bloomNutrientPin, _boosterNutrientPin;

    void activatePump(int pin); // Generische Funktion, um eine Pumpe zu aktivieren
    void deactivatePump(int pin); // Generische Funktion, um eine Pumpe zu deaktivieren
};
};


#endif
