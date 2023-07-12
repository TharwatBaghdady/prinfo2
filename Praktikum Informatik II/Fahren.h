#pragma once
#include "Verhalten.h"      
class Fahren :
    public Verhalten
{
public:
    Fahren(Weg& street) : Verhalten(street) {};
    double dStrecke(Fahrzeug& vehicle, double dZeitIntervall) override;
};

