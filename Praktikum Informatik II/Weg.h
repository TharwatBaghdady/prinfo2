#pragma once
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"
#include <list>

class Verhalten;
class Fahrzeug; //Rekursion vermeiden 
class Kreuzung;

class Weg :
    public Simulationsobjekt
{
private:
    double p_dLaenge = 0;
    Tempolimit p_eTempolimit;
    std::string sName = "";
    bool p_bUeberholverbot;
    double dSchranke = 0;
    const std::weak_ptr<Kreuzung> p_pKreuzung; // const da die sich nich aendern wird
    std::weak_ptr<Weg> p_pRueckweg;
    //um zyklus zwischen beiden Kreuzungen zu vermeiden

public:
    Weg();
    Weg(std::string sName, double dLaenge, Tempolimit eLimit = Tempolimit::Autobahn, bool p_bUeberholverbot = true, std::shared_ptr<Kreuzung> pKreuzung = nullptr);
	//Zielkr und wurde so initialisiert 
    vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge; //Liste aller Fahrzeuge auf dem Weg.
    double getTempolimit();
    static void vKopf();
    void vSimulieren() override;
    void vAusgeben(std::ostream& o) const override;
    double dGetLaenge() const;

    double dGetSchranke() const;
    void vSetSchranke(double);

    std::weak_ptr<Kreuzung> pGetKreuzung() const;
    void vSetReuckweg(std::shared_ptr<Weg> rueckweg);
    std::shared_ptr<Weg> pGetRueckweg() const;

    void vAnnahme(std::unique_ptr<Fahrzeug>);
    void vAnnahme(std::unique_ptr<Fahrzeug>, double); //ueberladen der oberen Funktion: Unterscheiden zwischen parkend und fahrend.
    std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&);
    std::string sGetName() const;
   // std::list<std::unique_ptr<Fahrzeug>> pGetList();
    virtual ~Weg();

    Weg(const Weg&) = delete; //Verbieten des Copy-Konstruktors
};

