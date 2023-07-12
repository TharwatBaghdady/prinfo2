#include "Verhalten.h"
#include "Weg.h"
#include "Fahrzeug.h"

//-----------Konstruktor der Klasse: er uebergibt den Inhalt des eingegeben Weges an street1 
//-----------via call by reference, naemlich um keine lokale Kopie zu erstellen--------------
Verhalten::Verhalten(Weg& street1):
	street(street1)
{
}

//---------getter fuer die Strasse---
Weg& Verhalten::wGetWeg() const
{
	return street;
}

//------------Destruktor-------------
Verhalten::~Verhalten()
{
}

//----------die Funktion ermittelt wie weit ein Fahrzeug innerhalb des gegebenen
//----------Zeitintervalls fahren kann, ohne das Wegende zu ueberschreiten.-------------
/*
double Verhalten::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
Implementierung wird auskommentiert, da methode abstrakt ist und keine Rueckgabe hat.
}
*/

