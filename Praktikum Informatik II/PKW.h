#pragma once
#include "Fahrzeug.h"
class PKW :
    public Fahrzeug
{
private:
    double p_dVerbrauch = 0; //Oel-Verbaruch in Liter/100km
    double p_dTankvolumen = 0; //Tankvolumen in Liter p_dTankvolumen
    double p_dTankinhalt = 0; //in Liter


public:
    PKW(std::string name);
    PKW(std::string sName, double dMaxSpeed, double dVerbrauch, double dTankvolumen = 55); //default parameter für Volumen, muss auch immer als letztes stehen
    double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override; //Wenn Funktion ohne parameter aufgerufen wird, dann wird vollgetankt
    void vSimulieren() override;
    bool bUeberholenGueltig() const override;
    double dGeschwindigkeit() const override;
    double dGetTankinhalt() const;
    void vAusgeben(std::ostream& o) const override;
    void vZeichnen(const Weg& street) const override;
    void vEinlesen(std::istream& i);
};

