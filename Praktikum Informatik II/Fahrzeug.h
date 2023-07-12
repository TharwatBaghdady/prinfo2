#pragma once
#include "Simulationsobjekt.h"

class Verhalten;
class Weg; //Anstatt die Headerdatei zu inkludieren, kann man einfach die Klasse hier deklaririen, um z.B Rekursion zu vermeiden 

// Wichtig Notiz: Es werden zwar keine Fahrzeug-Instanzen erzeugt, aber die Fahrzeug-Klasse wollen wir nicht als abstrakte (rein virtuell) Klasse
// implementieren, damit es nicht zu ungewuenschten Fehlermeldungen in alten Aufgaben fuehrt. Die aktuelle Implementierung ist auch ausreichend
// und fuer alle Aufgaben im Praktikum geeignet. 

class Fahrzeug :
	public Simulationsobjekt
{
private:
	//std::unique_ptr<Verhalten> p_pVerhalten = nullptr; //jedes Fahrzeug besitz ein eigenes "Verhalten-Objekt", das nicht geteilt wird.
	//das verhalten wurde auf public uebertragen damit das von PKW zugegriffen werden kann.

protected:
	double p_dMaxGeschwindigkeit = 0; //geschwindigkeit des Fahrzeuges in KM/h
	double p_dGesamtStrecke = 0; //die bisher zurückgelegte Gesamtstrecke
	double p_dAbschnittStrecke = 0; //die bisher zurückgelegte Gesamtstrecke auf einem Weg. 
									//Nicht zu verwechseln mit der Gesamtstrecke!
	double p_dGesamtZeit = 0; //die gesamte Fahrzeit des Objektes
	std::unique_ptr<Verhalten> p_pVerhalten = nullptr; //jedes Fahrzeug besitzt ein eigenes "Verhalten-Objekt", das nicht geteilt wird.

public:
	//------------Konstruktoren und Methoden werden in den cpp-Dateien erklärt----------------
	Fahrzeug();
	Fahrzeug(std::string sName);
	Fahrzeug(std::string sName, double dMaxSpeed);
	std::string sGetName() const;
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());
	virtual double dGeschwindigkeit() const;
	static void vKopf();
	void vAusgeben(std::ostream& o) const override;
	virtual bool bUeberholenGueltig() const;
	double dGetAbschnitt() const;
	void vNeueStrecke(Weg&);
	void vNeueStrecke(Weg&, double); //ueberladen der oberen Funktion mit einem 2. Parameter: Startzeit.
	virtual void vSimulieren() override;
	virtual void vZeichnen(const Weg&) const;
	virtual void vEinlesen(std::istream& i);

	void operator=(const Fahrzeug&);
	bool operator<(const Fahrzeug&) const;

	virtual ~Fahrzeug();

	Fahrzeug(const Fahrzeug&) = delete; //Verbieten des Copy-Konstruktors
	//Frage im Skript: Wo wird der Copy-Konstruktor implizit aufgerufen? --> Wenn eine Variable an eine Methode nicht als Referenz uebergeben wird.
	//Frage im Skrpt: Was bedeutet dies in diesem Szenario? --> In diesem Szenario wird die ID auch kopiert, wenn der Copy-Konstruktor aufgerufen wird,
	//was wir vermeiden wollen. Es könnte beim loeschen der Objekte zu wilden Zeigern fuehren: der Inhalt ist geloescht worden, die Zeiger aber nicht.
};