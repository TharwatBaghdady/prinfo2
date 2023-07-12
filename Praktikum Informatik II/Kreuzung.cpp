#include "Kreuzung.h"
#include "Weg.h"
#include <cmath>
#include <random>

/*
Kreuzung::Kreuzung(std::string name):
	Simulationsobjekt(sName), p_dTankstelle(0)
{
}
*/

Kreuzung::Kreuzung(std::string sName, double dTankstelle):
	Simulationsobjekt(sName), p_dTankstelle(dTankstelle)
{
}

//--------------------Verbinden von 2 Kreuzungen---------------------------------
void Kreuzung::vVerbinde(std::string sHin, std::string sRueck, double dLaenge, std::shared_ptr<Kreuzung> kStart, std::shared_ptr<Kreuzung> kZiel, Tempolimit eLimit, bool p_bUeberholverbot)
{
	//Erstellung des Hinweges.
	std::shared_ptr<Weg> Hinweg = std::make_shared<Weg>(sHin, dLaenge, eLimit, p_bUeberholverbot, kZiel);
	//Ersellung des Rueckweges.
	std::shared_ptr<Weg> Rueckweg = std::make_shared<Weg>(sRueck, dLaenge, eLimit, p_bUeberholverbot, kStart);

	 
	//individuellen "Rueckwege" abgeleitet und bekannt machen.

	Hinweg->vSetReuckweg(Rueckweg); //der "Reuckweg" vom Hinweg ist der Rueckweg. 
	kStart->p_pWege.push_back(move(Hinweg)); //Einfuegen des hinweges in Liste der Wege von der Startkreuzung.

	Rueckweg->vSetReuckweg(Hinweg); //der "Reuckweg" vom Rueckweg ist der Hinweg.
	kZiel->p_pWege.push_back(move(Rueckweg)); //Einfuegen des Rueckweges in Liste der Wege von der Zielkreuzung.
}

//-----------------Tanken des uebergebenen Fahrzeuges---------------------
void Kreuzung::vTanken(Fahrzeug& vehicle)
{
	if (this->p_dTankstelle == 0)
	{
		return;
	}

	else if (this->p_dTankstelle < 0)
	{
		this->p_dTankstelle = 0.0;
	}

	else {
		double dOelMenge = vehicle.dTanken(); //PKW wird getankt, die getankte Menge wird eine Variable gespeichert..
		this->p_dTankstelle = this->p_dTankstelle - dOelMenge;  //und von der Tankstelle der Krezung abgezogen.
	}
}

//-----------------Annehmen der Fahrzeuge "Parkend" in den ersten wegfuehrenden Weg von der Kreuzung--------------------- 
void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> vehicle, double dZeit)
{
	this->vTanken(*vehicle);                                      //PKW wird getankt.
	this->p_pWege.begin()->get()->vAnnahme(move(vehicle), dZeit); //und auf der abhgehende Strasse rechtzeitlich losgefahren
}

//---------Funktion für Ueberschrift: abstaende mit setw() der <iomanip> Bibliothek gemacht, anstatt Leerzeichen------------
void Kreuzung::vKopf()
{
	Simulationsobjekt::vKopf();
	std::cout << std::resetiosflags(std::ios::left);
	std::cout << std::setw(30) << "|   Tankstelle-Oelinhalt [L]" << std::setw(25) << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

}

//----------Ausgabe der Daten der einzelnen Kreuzung-----------
void Kreuzung::vAusgeben(std::ostream& o) const
{
	Simulationsobjekt::vAusgeben(o);
	o << std::resetiosflags(std::ios::right);
	o << p_dTankstelle << std::setw(25);
}

//------------Simulieren aller von der Kreuzung abgehenden Wege------------
void Kreuzung::vSimulieren()
{
	for (auto& street : p_pWege)
	{
		street->vSimulieren(); 
	}
}

//----------------Erzeugung eines zufaelligen Weges aus der Wegeliste einer Kreuzung-------------------------
Weg& Kreuzung::pZufaelligerWeg(Weg& street)
{
	int b = this->p_pWege.size(); //Groesse der Liste, kann auch als Index benutzt werden.
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1, b);
	int i = dist(device);
	// zufaellige Zahl i in p_pWege und dann als index in p_pWege betrachtet.
	auto it = this->p_pWege.begin(); //it am Anfang
	std::advance(it, i - 1);  // it wird durch advance zu ite Stelle verschoben
						    

	if (this->p_pWege.size() > 2) //Wenn die Kreuzung mehrere Strassen verbindet
								
	{
		if (*it == street.pGetRueckweg()) // gleiche Straße?
		{
	
			return this->pZufaelligerWeg(street); // alles wiederholen
		}

		return **it; 
	}
	else return *p_pWege.front(); //sonst die einzige Straße zurückgeben

}

//-------------Getter fuer die verbleibende Oelmenge in der Tankstelle-----------
double Kreuzung::dGetTankstelle() const
{
	return p_dTankstelle;
}

//--------------getter fuer den Namen der Kreuzung----------------
std::string Kreuzung::sGetName() const
{
	return p_sName;
}

void Kreuzung::vEinlesen(std::istream& i)
{
	//std::cout << "Kreuzung: \n";
	Simulationsobjekt::vEinlesen(i);
	i >> this->p_dTankstelle;
}

