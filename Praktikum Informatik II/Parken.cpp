#include "Parken.h"
#include "Fahrzeug.h"
#include "Losfahren.h"

//----------------Konstruktor fuer Parken----------------
Parken::Parken(Weg& street, double time):
	Verhalten(street), p_dStartzeit(time)
{
}

//-----------dStrecke() fuer parkende Fahrzeuge: gibt null aus, solange die Startzeit nicht erreicht wurde----------------
double Parken::dStrecke(Fahrzeug& vehicle, double dFahrzeit)
{
	if (dGlobaleZeit + 1e-6 < p_dStartzeit) //Genauigkeitsfaktor wird zur Optimierung addiert (kann man aberauch weglassen).
	{
		return 0.0;
	}

	else
	{
		throw Losfahren(vehicle, street); //die zugehoerige Fahrausnahme wird hier geworfen.
	}

	std::cout << "Die Startzeit von " << vehicle.sGetName() << " wurde erreicht." << std::endl;
}
