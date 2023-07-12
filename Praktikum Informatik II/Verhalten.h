#pragma once
#include <iostream>
//Anstatt die H-Dateien der Klassen zu inkludieren werden die Klassen hier definiert, hauptsaechlich um Rekursion zu vermeiden.
class Weg;
class Fahrzeug;

extern double dGlobaleZeit;

class Verhalten
{
protected:
	Weg& street; //eine Referenz auf einen fuer diese Klasse erstellten Weg. Siehe Kosntruktor.

public:
	Verhalten(Weg& street);
	virtual double dStrecke(Fahrzeug& vehicle, double Startzeit) = 0; //Verhalten wird Oberklasse zu den abgeleiteten Klassen "Fahren" und "Parken" und durch diese Anweisung rein virtuell.
	virtual ~Verhalten();
	Weg& wGetWeg() const;
};

