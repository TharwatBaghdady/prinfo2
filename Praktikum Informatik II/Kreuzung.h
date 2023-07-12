#pragma once
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "Fahrzeug.h"
#include "vertagt_liste.h"
#include <list>

class Weg;

class Kreuzung :
    public Simulationsobjekt
{
private:
    double p_dTankstelle;
    std::string sName;
    //mehrere Wege koennen gleichzeitig auf dieselbe Kreuzung deuten 
    //und den Besitz fuer dieses Objekt haben, daher shared ptr.

public:
    //Kreuzung(std::string name);
    Kreuzung(std::string sName, double dTankstelle = 0);
    std::list<std::shared_ptr<Weg>> p_pWege; //liste der wegfahrenden Autos. Public, da man spaeter auf die in 
                                             //Streckenende.dpp zugreifen moechte.
    void vVerbinde(std::string sHin, std::string sRueck, double dLaenge, std::shared_ptr<Kreuzung> kStart, std::shared_ptr<Kreuzung> kZiel, Tempolimit eLimit = Tempolimit::Autobahn, bool p_bUeberholverbot = true);
    void vTanken(Fahrzeug& vehicle);
    void vAnnahme(std::unique_ptr<Fahrzeug> vehicle, double dZeit);
    void vKopf();
    void vAusgeben(std::ostream& o) const override;
    void vSimulieren();
    double dGetTankstelle() const;
    void vEinlesen(std::istream& i);
    std::string sGetName() const;
    Weg& pZufaelligerWeg(Weg& street);
};

