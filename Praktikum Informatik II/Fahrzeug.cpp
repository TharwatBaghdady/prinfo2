#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahren.h"
#include "Parken.h"

//Bitte die ersten 2 Konstruktoren nicht loeschen! sonst mekert das main.cpp!

//-----standardkonstruktor 
Fahrzeug::Fahrzeug() :
	Simulationsobjekt("")
{
	std::cout << "Ein Fahrzeug namens: " << p_sName << "und ID#: " << p_iID << " wurde anhand des Standardkonstruktors erstellt" << std::endl;
	std::cout << "" << std::endl;
} 

//------Konstruktor mit Nameangabe: intialiesierungsliste fuer name und id-----
Fahrzeug::Fahrzeug(std::string name) :
	Simulationsobjekt(name)
{
	std::cout << "Ein Fahrzeug namens: " << p_sName << " und ID#: " << p_iID << " wurde anhand des nicht-Standardkonstruktors erstellt" << std::endl;
	std::cout << "" << std::endl;
}

//------Konstruktor mit Name- und Geschwindigkeitangabe, geschwindigkeit wird mit ? nach vorzeichen geprueft, intialiesierungsliste fuer name, id, geschwindigkeit ----------------
Fahrzeug::Fahrzeug(std::string name, double dMaxSpeed) :
	Simulationsobjekt(name), p_dMaxGeschwindigkeit((dMaxSpeed > 0) ? dMaxSpeed:(dMaxSpeed*-1))
{
	std::cout << "Ein Fahrzeug namens: " << p_sName << " und ID#: " << p_iID << " wurde anhand des nicht-Standardkonstruktors erstellt" << std::endl;
	std::cout << "" << std::endl;
}

//---------Funktion für Ueberschrift: abstaende mit setw() der <iomanip> Bibliothek gemacht, anstatt Leerzeichen------------
void Fahrzeug::vKopf()
{
	Simulationsobjekt::vKopf();
	std::cout << std::resetiosflags(std::ios::left);
	std::cout << std::setw(30) << "|   MaxGeschwindigkeit [km/h]" << std::setw(25) << "|   Gesamtstrecke [km/h]" << std::setw(35) << "|   akt. Geschwindigkeit [km]" << std::setw(25) << "|   Gesamtverbrauch [L]" << std::setw(25) << "|   akt. Tankinhalt [L]" << std::endl;
	std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
}

//------------getter fuer den Namen des Fahrzeuges, Namen sind privat und koennen nur ueber Methoden (public oder protected) bearbeitet werden------------
std::string Fahrzeug::sGetName() const
{
	return p_sName;
}

//----------Funktion gibt 0 aus bei Klima+ Fahrzeuge, andere Fahrzeuge (PKW) haben entsprechende 
//----------komplexere ueberschreibende Tank-Funktionen-----------
double Fahrzeug::dTanken(double dMenge)
{
	return 0;
}

//----------maximale Geschwindigkeit des Fahrzeuges----------------
double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

//----------Ausgabe der Daten des einzelnen Fahrzeuges-----------
void Fahrzeug::vAusgeben(std::ostream& o) const
{
	Simulationsobjekt::vAusgeben(o);
	o << std::resetiosflags(std::ios::right);
	o << p_dMaxGeschwindigkeit << std::setw(25) << std::setprecision(5) << p_dGesamtStrecke << std::setw(30) << dGeschwindigkeit();
}

//---------Funktion, die zuruckgibt ob ein Fahrzeug uebrholt werden darf---------------
bool Fahrzeug::bUeberholenGueltig() const
{

	return false; 
}

//-------------------getter fuer Abschnittstrecke---------------------
double Fahrzeug::dGetAbschnitt() const
{
	return p_dAbschnittStrecke;
}

//----------------Erstellen eines neuen Verhaltens von einem fahrenden Fahrzeug in einem bestimmten Weg--------------
void Fahrzeug::vNeueStrecke(Weg& street)
{
	p_pVerhalten = std::make_unique<Fahren>(street); //die alte Instantz (mit dem vorherigen Weg) wird dann geloescht.
	this->p_dAbschnittStrecke = 0; //Die Abschnittstrecke wird auf 0 null gesetzt, denn das Fahrzeug nun in einem neuen Weg ist.
}

//-----------------Erstellen eines neuen Verhalten von einem parkenden Fahrzeuges in einem bestimmten Weg-------------------
void Fahrzeug::vNeueStrecke(Weg& street, double Startzeit)
{
	if (Startzeit >= dGlobaleZeit)
	{
		p_pVerhalten = std::make_unique<Parken>(street, Startzeit); //die alte Instantz (mit dem vorherigen Weg) wird dann geloescht.
		this->p_dAbschnittStrecke = 0; //Die Abschnittstrecke wird auf 0 null gesetzt, denn das Fahrzeug nun im neuen Weg ist.
	}
}


//---------------Simulationsfunktion des einzelnen Fahrzeuges----------------
void Fahrzeug::vSimulieren()
{
	if (dGlobaleZeit > p_dZeit)
		{
			double dFahrzeit = dGlobaleZeit - p_dZeit; //dFahrzeit entspricht dem Simulationstakt!
			double dNeueStrecke = p_pVerhalten->dStrecke(*this, dFahrzeit); 
			p_dAbschnittStrecke += dNeueStrecke; //Aktuelle Strecke auf dem Weg wird aktualisiert
			p_dGesamtStrecke += dNeueStrecke; //Gesamtstrecke wird aktualisiert.
			p_dZeit += dFahrzeit; //aktualisiern nach dem Takt.
			p_dGesamtZeit += dFahrzeit; //gesamtzeit wird aktualisiert.
		}
}

//------------Zeichnen Funktion fuer Fahrzeuge, Implementierung findet man in der ueberladenen Fubnktionen----------------
void Fahrzeug::vZeichnen(const Weg& street) const
{
}



//----------destruktor----------
Fahrzeug::~Fahrzeug()
{

}

void Fahrzeug::vEinlesen(std::istream& i)
{
	//std::cout << "Fahrzeug: \n";
	Simulationsobjekt::vEinlesen(i);
	i >> this->p_dMaxGeschwindigkeit;
}

//---------------------Ueberladung der "="-Operator: kopieren der Stammdaten "Maximale Geschwindigkeit" & "Name"-----------------------
void Fahrzeug::operator=(const Fahrzeug& vehicle)
{
	Simulationsobjekt::operator=(vehicle);
	this->p_dMaxGeschwindigkeit = vehicle.p_dMaxGeschwindigkeit;
}

//--------------------Ueberladung der "<" operator: Vergleichen zwischen Objeckten nach Gesamtstrecke-----------------------
bool Fahrzeug::operator<(const Fahrzeug& vehicle2) const
{
	return (this->p_dGesamtStrecke < vehicle2.p_dGesamtStrecke);
}

