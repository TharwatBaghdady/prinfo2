#pragma once
#include "Verhalten.h"

class Parken :
    public Verhalten
{
private:
    double p_dStartzeit; //startzeit eines Fahrzeuges: Übergang von "Parken" zu "Fahren".

public:
    Parken(Weg& street, double time); //zweiter Parameter fuer Startzeit.
    double dStrecke(Fahrzeug& vehicle, double Startzeit) override; //hier ist der 2. Parameter der Startzeitpunkt (auch der Zeitintervall zum simulieren des Fahrzeuges)
};




