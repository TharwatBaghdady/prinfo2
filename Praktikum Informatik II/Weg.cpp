#include "Weg.h"
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Fahrausnahme.h"
#include "Kreuzung.h"

//-------Standardkonstruktor------------
Weg::Weg() :
	Simulationsobjekt("")
{
}

//--------Parametisierter Konstruktor mit optionalen Parametern (Tempolimit & Ueberholverbot)----------
Weg::Weg(std::string sName, double dLaenge, Tempolimit eLimit, bool p_bUeberholverbot, std::shared_ptr<Kreuzung> pKreuzung) :
	sName(sName), Simulationsobjekt(sName), p_dLaenge(dLaenge), p_eTempolimit(eLimit), p_bUeberholverbot(p_bUeberholverbot), p_pKreuzung(pKreuzung)
{
}

//----------gibt die Geschwindigkeitbegrenzung fuer den entsprechenden Weg (innerorts = 50,....) aus-----------
double Weg::getTempolimit()
{
	return (double)p_eTempolimit;
}

//-------------Simuliert alle auf dem Weg befindlichen Fahrzeuge anhand des iterator it---------------
void Weg::vSimulieren()
{
	p_pFahrzeuge.vAktualisieren(); //aktualieseren der Liste vor jeder Simulation, 
								   //laut letztes Unterpunktes von AB2.

	//std::list<std::unique_ptr<Fahrzeug>>::iterator it; //iterator muss vom selben Typ der Elemente in der Liste sein: unique ptr<Fahrzeug>, benutzen wir aber nicht.

	//simulieren aller Fahrzeuge anhand einer range-basierter Schleife

	vSetSchranke(this->dGetLaenge());

	for (auto& Mitglied : p_pFahrzeuge)
	{
		try
		{
			Mitglied->vSimulieren(); //simulieren aller Fahrzeuge.

			//Gilt das Uebrholverbot? das wird bei der Instanzierung vom Weg angegeben
			if (p_bUeberholverbot == true)
			{
				//Kann das Farhzeug -PKW- trotzdem uebrholt werden, 
				//z.B im Falle eines leeren Tanks
				if (Mitglied->bUeberholenGueltig() == false)
				{
					//Der ganze Mechanismus gilt nur fuer Fahrzeuge, die schon begonnnen haben, zu fahren!
					if (Mitglied->dGetAbschnitt() > 0)
					{
						//Die virtuelle Schranke wird dann fuer das erste fahrende Fahrzeug gesetzt.
						vSetSchranke(Mitglied->dGetAbschnitt());
					}
				}
			}

			Mitglied->vZeichnen(*this); //Zeichnen des Fahrzeuges im Weg.
		}
		catch (Fahrausnahme & x)
		{
			x.vBearbeiten(); //wenn eine bestimmte Ausnahme (entweder Losfahren oder Streckenende) geworfen wurde, 
							 //dann wird sie hier gefangen und ihre entsprechende vBearbeiten() wird dann aufgereufen.
		}

		//Frage im Skript: beide Ausnahmen koennen mit einem catch-Block gefangen werden, denn sie beide von der selben Klasse(fahrausnahme) erben
		//und ihre speziefische Art (Losfahren oder Streckenende) wird vorhin schon festgelegt durch die throw-Stelle. 
		//Beide Ausnahmen besitzen darueber hinaus die vBearbeiten Funktion, aber mit verchiedenen Implementierungen.
	}

	p_pFahrzeuge.vAktualisieren(); //aktualieseren der Liste nach jeder Simulation, 
								   //laut letztes Unterpunktes von AB2.
}

//---------Funktion f�r Ueberschrift: Abstaende mit setw() der <iomanip> Bibliothek gemacht, anstatt Leerzeichen------------
void Weg::vKopf()
{
	Simulationsobjekt::vKopf();
	std::cout << std::resetiosflags(std::ios::left);
	std::cout << std::setw(28) << "|  Laenge" << std::setw(20) << "|  Fahrzeuge" << std::endl;
	std::cout << "-----------------------------------------------------------------------------------------------------" << std::endl;
}

//-------------Ausgabe des
void Weg::vAusgeben(std::ostream& o) const
{
	std::string sAlleFahrzeuge = "";

	for (auto& Mitglied : p_pFahrzeuge)
	{
		sAlleFahrzeuge = sAlleFahrzeuge + " " + Mitglied->sGetName(); //Uebergeben aller Fahrzeuge auf dem Weg in einem String,
																	  //damit die demnaechst ausgegeben werden.
	}

	Simulationsobjekt::vAusgeben(o);
	o << std::resetiosflags(std::ios::right);
	o << std::setw(15) << ":" << std::setw(10) << p_dLaenge << std::setw(10) << std::setprecision(5) << "(" << sAlleFahrzeuge << ")" << std::endl;
}

//------getter fuer laenge des Weges-----
double Weg::dGetLaenge() const
{
	return p_dLaenge;
}

void Weg::vSetSchranke(double dNewSchranke)
{
	dSchranke = dNewSchranke;
}

double Weg::dGetSchranke() const
{
	if (p_bUeberholverbot == true)
	{
		return dSchranke;
	}

	return p_dLaenge; //wenn es kein Uebrholverbot gibt, dann wird das Wegende zurueckgegeben.
}

//-------------------Hinzufuegen eines fahrenden Fahrzeuges in einen Weg------------------
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> vehicle)
{
	vehicle->vNeueStrecke(*this); //das Fahrzeug wird signalisiert, dass es jetzt auf einem anderen Weg ist: siehe Fahrzeug::vNeueStrecke;
	p_pFahrzeuge.push_back(move(vehicle)); //fahrendes Fahrzeug wird hinten hinzugefuegt in die Liste der Fahrzeuge, die sich im Weg befinden.
}

//----------ganuso wie oben aber fuer parkende Fahrezeuge, dazu wird eine Starzeit fuer parkende Fahrzeuge uebergegeben----------------
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> vehicle, double Startzeit)
{
	vehicle->vNeueStrecke(*this, Startzeit); //das Fahrzeug wird signalisiert, dass es jetzt auf einem anderen Weg ist: siehe Fahrzeug::vNeueStrecke;
	p_pFahrzeuge.push_front(move(vehicle));//parkendes Fahrzeug wird vorne hinzugefuegt in die Liste der Fahrzeuge, die sich im Weg befinden.
}


//------------Funktion zum Loeschen der parkenden Fahrzeuge aus der Liste p_pFahrzeuge----------- 
std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& vehicle)
{
	

	std::unique_ptr<Fahrzeug> pTempLokal;

	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		if ((*it).get() == &vehicle) //doppelt dereferenziert, da it Zeiger auf einen anderen Zeiger ist. 
									 //warum (*it).get() == &vehicle und nicht **it == vehicleAus? 
									 //Siehe Kommentar in Streckekende.cpp
		{
			p_pFahrzeuge.erase(it); //loeschen des parkenden Fahrzeuges aus der liste.
			pTempLokal = move(*it); //der Inhalt des Zeigers wird hier verschoben, 
									//damit es anschliessend ausgegeben werden kann.
			return pTempLokal;
		}
	}
}

//------------setter fuer den Rueckweg vonWegen------------
void Weg::vSetReuckweg(std::shared_ptr<Weg> reuckweg)
{
	p_pRueckweg = reuckweg;
}

//---------------Getter fuer die Zielkreuzung eines Weges-------------
std::weak_ptr<Kreuzung> Weg::pGetKreuzung() const
{
	return p_pKreuzung.lock();
}

//--------------Getter fuer den Rueckweg-------------------------
std::shared_ptr<Weg> Weg::pGetRueckweg() const
{
	return this->p_pRueckweg.lock();
}

//--------------getter fuer den Wegnamen---------------
std::string Weg::sGetName() const
{
	return sName;
}

/*
* //-----------getter fuer die Liste der Fahrzeuge auf dem Weg--------------
std::list<std::unique_ptr<Fahrzeug>> Weg::pGetList()
{
	return p_pFahrzeuge;
}
*/


//----------destruktor----------
Weg::~Weg()
{

}