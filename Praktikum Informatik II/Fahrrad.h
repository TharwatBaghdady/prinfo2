#pragma once
#include "Fahrzeug.h"
class Fahrrad :
    public Fahrzeug
{

public:
    Fahrrad(std::string name);
    Fahrrad(std::string sName, double dMaxGeschwindigkeit);
    void vZeichnen(const Weg& street) const override;
    void vEinlesen(std::istream& i);
    double dGeschwindigkeit() const;
};

