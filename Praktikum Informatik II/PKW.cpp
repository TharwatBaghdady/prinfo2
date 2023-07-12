#include "PKW.h"
#include "Verhalten.h"
#include "Weg.h"

PKW::PKW(std::string name) :
	Fahrzeug(name)
{
}

PKW::PKW(std::string name, double speed, double dconsumbtion, double dtankvolume) :
	Fahrzeug(name, speed), p_dVerbrauch(dconsumbtion), p_dTankvolumen(dtankvolume),p_dTankinhalt(dtankvolume/2)
{
}

//----------Tanken das Fahrzeuges nach Eingabe des Benutzers, wenn Menge zu  viel ist wird Fahrzeug vollgetankt-------------
double PKW::dTanken(double dMenge)
{
	double dLeerTank = p_dTankvolumen - p_dTankinhalt;

	//passende Menge ueberpruefen
	if (dMenge > dLeerTank)
	{
		std::cout << "Ihr Fahrzeug: " << this->sGetName() << " wird vollgetankt." << std::endl;
		dMenge = dLeerTank;
	}

	else {
		//Tankinhalt aktualisieren
		p_dTankinhalt += dMenge;
		return dMenge;
	}
}

//---------Funktion Simuliert Fahrzeuge mit Oel-Verbrauch, dazu wird der Tankinhalt nach jedem Simulationsschritt aktualisiert 
void PKW::vSimulieren()
{
	//ueberpruefen, ob Tank leer ist, wenn nicht, dann wird weiter gefahren und der Tank aktualisiert
	if (p_dTankinhalt > 0)
	{
		double speed = dGeschwindigkeit(); //zu Debugg-Zwecken wird die Geschwindigkeit hier gespeichert,
									   	  //insbesondere kann ich dGeschwindigkeit besser debuggen.
		double dTempStrecke = p_dAbschnittStrecke;
		Fahrzeug::vSimulieren();
		double dVerbrauch = (p_dAbschnittStrecke - dTempStrecke) * p_dVerbrauch/100;
		double dFahrzeit = dGlobaleZeit - p_dZeit;
		//double dTankVerbrauch = / 100*dFahrzeit*speed; //Verbrauchrate*gefahrene strecke seit letztem Simulationsschritt
		p_dTankinhalt -= dVerbrauch; //Verbrauchrate*gefahrene strecke seit letztem Simulationsschritt.

		if (p_dTankinhalt < 0)
		{
			p_dTankinhalt = 0;
		}
	}

	//wenn doch Leer, wird nicht weiter gefahren, sonder kommt eine Meldung.
	else
	{
		p_dTankinhalt = 0; //Falls der Tank minus Liter hat aus der letzten Simulation, wird er auf 0 gesetzt 
		std::cout << "Tank von "<< this->sGetName() << " ist Leer, bitte Tanken!" << std::endl;
	}

}

bool PKW::bUeberholenGueltig() const 
{
	if (p_dTankinhalt > 0)
	{
		//Tank ist nicht leer --> PKW faehrt noch
		//dann darf es nicht uebrholt werden
		return false;
	}

	//sonst ist der Tank leer --> Fahrzeug faehrt nicht mehr und steht mitten im Weg.
	//Laut Skript darf das Fahrzeug dann uebrholt werden.
	return true;
}

//---------------Geschwindigkeit des PKWs wird festgelegt nach dem Tempolimit des Weges---------------
double PKW::dGeschwindigkeit() const
{
	if (p_pVerhalten != nullptr) //wenn ein PKW nicht auf einem Weg ist und trotzdem simuliert werden soll, 
								 //dann hat es kein Verhalte -siehe vNeueStrecke-, das fuerht zur 
								 //Rueckgabe von einem nullptr. Das kann man umgehen anhand dieser if-block!
	{
		Weg& street = p_pVerhalten->wGetWeg(); //auf den Weg wird durch das Verhalten-Objekt 
										       //des PKWs zugegriffen
		double dLimit = street.getTempolimit(); //das Tempolimit des Weges wird hier gespeichert

		if (dLimit > p_dMaxGeschwindigkeit)
		{
			return p_dMaxGeschwindigkeit;
		}

		return dLimit; //wenn die Maximale Geschwindigkeit groesser ist, wird doch das limit zurueckgegeben
	}

	return p_dMaxGeschwindigkeit; //wenn das PKW kein Verhalten hat, weil es noch auf keinem Weg ist 
								  //dann wird eben die maximale Geschwindigkeit zurueckgegeben.
}

//-----------getter fuer den Tankinhalt des PKWs----------------
double PKW::dGetTankinhalt() const
{
	return p_dTankinhalt;
}

//------------Ueberladung von vAusgeben, so dass die restlichen relevanten Parameter von PKW ausgegeben werden----------------
void PKW::vAusgeben(std::ostream& o) const
{
	Fahrzeug::vAusgeben(o);
	o << std::resetiosflags(std::ios::right);
	o << std::setw(20) << p_dVerbrauch * p_dGesamtStrecke/100 << std::setw(25) << p_dTankinhalt;
	//o << "" << std::endl;
}

void PKW::vZeichnen(const Weg& street) const
{
	double RelPosition = this->dGetAbschnitt() / street.dGetLaenge(); //realtive Position des PKWs zur Laenge des Weges: 
																 //Wert zwichen 0 & 1.
	std::string WegName = street.sGetName(); //Name des Weges.
	std::string PKWName = this->sGetName(); //Name des PKWs.
	double KmH = this->dGeschwindigkeit(); //Geschwindigkeit des PKWs in KmH.
	double Tank = this->p_dTankinhalt; //Tankinhalt des PKWs.
	
	bZeichnePKW(PKWName, WegName, RelPosition, KmH, Tank);
}

void PKW::vEinlesen(std::istream& i)
{
	//std::cout << "PKW: \n";
	Fahrzeug::vEinlesen(i);
	i >> this->p_dVerbrauch >> this->p_dTankvolumen;
}



