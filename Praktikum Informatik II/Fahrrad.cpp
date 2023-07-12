#include "Fahrrad.h"
#include "Weg.h"

Fahrrad::Fahrrad(std::string name):
	Fahrzeug(name)
{
}

Fahrrad::Fahrrad(std::string sName, double dMaxGeschwindigkeit) : Fahrzeug(sName, dMaxGeschwindigkeit)
{
}

void Fahrrad::vZeichnen(const Weg& street) const
{
	double RelPosition = this->dGetAbschnitt() / street.dGetLaenge(); //realtive Position des Fahrrads zur Laenge des Weges: 
																	  //Wert zwichen 0 & 1.
	std::string WegName = street.sGetName(); //Name des Weges.
	std::string PKWName = this->sGetName(); //Name des Fahrrads.
	double KmH = this->dGeschwindigkeit(); //Geschwindigkeit des Fahrrads in KmH.

	bZeichneFahrrad(PKWName, WegName, RelPosition, KmH); //Zeichnen des Fahrrads.
}

//-------------Berechnung und Ausgabe der Fahrrad-Funktion----------
double Fahrrad::dGeschwindigkeit() const
{
	if (this->p_pVerhalten != nullptr)
	{
		if (p_dGesamtStrecke >= 15)
		{
			double dSpeed = std::pow(0.88, (int)p_dGesamtStrecke / 15) * p_dMaxGeschwindigkeit; //aktuelle Geschwindigkeit = geschwindigkeit * (0,9)^(Gesamtstrecke/20km)

			return (dSpeed >= 10) ? dSpeed : 10;
		}

		return p_dMaxGeschwindigkeit;
	}

	return p_dMaxGeschwindigkeit;
}


void Fahrrad::vEinlesen(std::istream& i)
{
	//std::cout << "Fahrrad: \n";
	Fahrzeug::vEinlesen(i);
}
