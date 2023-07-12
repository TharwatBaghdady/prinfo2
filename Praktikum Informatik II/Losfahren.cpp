#include "Losfahren.h"
#include "Fahrzeug.h"

Losfahren::Losfahren(Fahrzeug& v, Weg& s):
	Fahrausnahme(v,s)
{
}

//------------Implementierung der Fahrausnahme: Losfahren----------
void Losfahren::vBearbeiten()
{
	std::cout << "Das Fahrzeug: " << vehicleAus.sGetName() << std::endl;
	std::cout << "Der Weg: " << streetAus.sGetName() << std::endl;
	std::cout << "Ausnahmeart: Losfahren";
	std::cout << " " << std::endl;
	std::cout << " " << std::endl;
	streetAus.vAnnahme(streetAus.pAbgabe(vehicleAus)); //nun wird das Fahrzeug als "Parkend" von der Liste geloescht 
													   //und als "Fahrend" hinten in die Liste hinzugefuegt.
}
