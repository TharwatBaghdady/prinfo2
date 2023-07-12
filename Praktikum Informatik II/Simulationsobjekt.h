#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include "SimuClient.h"

extern double dGlobaleZeit; //Globale Zeit der Simulation

class Simulationsobjekt
{
private:
	static int p_iMaxID; //die letzte ID#, entspricht auch der Anzahl der Eintraege. static weil es eher mit der Klasse verknuepft ist und nicht mit Objekten

protected:
	double p_dZeit = 0; //die Zeit, zu der das Simulationsobjekt zuletzt simuliert wurde
	std::string p_sName = ""; //Name des Simulationsobjektes
	const int  p_iID; //id des Simulationsobjektes, const weil es sich eben nicht ändern sollte fuer dasselbe Simulationsobjekt.

public:
	Simulationsobjekt();
	Simulationsobjekt(std::string sName);
	virtual ~Simulationsobjekt();

	static void vKopf();
	virtual void vAusgeben(std::ostream& o) const;
	virtual void vEinlesen(std::istream& i);
	virtual void vSimulieren() = 0;

	virtual void operator=(const Simulationsobjekt&);
	virtual bool operator==(const Simulationsobjekt&);

	Simulationsobjekt(const Simulationsobjekt&) = delete; //Verbieten des Copy-Konstruktors
};


std::ostream& operator<<(std::ostream& o, const Simulationsobjekt&);
std::istream& operator>>(std::istream& i, Simulationsobjekt&);
