#include "Simulationsobjekt.h"

int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt() :
	p_sName(""), p_iID(p_iMaxID++)
{
	std::cout << "Ein Simulationsobjekt namens: " << p_sName << "und ID#: " << p_iID << " wurde anhand des Standardkonstruktors erstellt" << std::endl;
	std::cout << "" << std::endl;
}

// ------Konstruktor mit Nameangabe : intialiesierungsliste fuer name und id
Simulationsobjekt::Simulationsobjekt(std::string name) :
	p_sName(name), p_iID(p_iMaxID++)
{
	std::cout << "Ein Simulationsobjekt namens: " << p_sName << " und ID#: " << p_iID << " wurde anhand des nicht-Standardkonstruktors erstellt" << std::endl;
	std::cout << "" << std::endl;
}

//---------Funktion für Ueberschrift: abstaende mit setw() der <iomanip> Bibliothek gemacht, anstatt Leerzeichen------------
void Simulationsobjekt::vKopf()
{
	std::cout << std::resetiosflags(std::ios::left);
	std::cout << std::setw(10) << "ID" << std::setw(15) << "|   Name";
}

//----------Ausgabe der Daten des einzelnen Simulationsobjektes-----------
void Simulationsobjekt::vAusgeben(std::ostream& o) const
{
	o << std::resetiosflags(std::ios::left);
	o << std::setiosflags(std::ios::right) << std::setw(15) << p_iID << std::setw(10) << p_sName << std::setw(25);
	//std::cout << "" << std::endl;
}

//-------------Einlesen der Daten des Simulationsobjektes----------
void Simulationsobjekt::vEinlesen(std::istream& i)
{
	if (p_sName != "") //Wenn der Name nicht leer ist --> da wurde schon was gespeichert
	{
		throw std::runtime_error("Der Name ist schon definiert!");  //dann wird das ausgegeben
	}
	i >> this->p_sName; //sonst wird der eingelesene Name gespeichert
}

//----------destruktor----------
Simulationsobjekt::~Simulationsobjekt()
{
	std::cout << "das Simulationsobjekt '" << p_sName << "' mit ID: " << p_iID << " wird geloescht" << std::endl;
	std::cout << "" << std::endl;
}

//---------------------Ueberladung der "="-Operator: kopieren der Stammdaten "Maximale Geschwindigkeit" & "Name"-----------------------
void Simulationsobjekt::operator=(const Simulationsobjekt& SimObjekt)
{
	//Frage im Skript: Was muss man bei der ID beachten? --> ID ist eine konstante variable und kann nicht bearbeitet werden sobald sie initialisiert wurde.

	//this->p_dMaxGeschwindigkeit = SimObjekt.p_dMaxGeschwindigkeit;
	//obere Zeile ist auskommentiert, da Weg keine Geschwindigkeit hat, die Zeile muss dann separat bei Fahrzeug ueberladen werden.
	this->p_sName = SimObjekt.p_sName + "-Kopie";

	//Frage im Skript: Was wuerde passieren, wenn Sie keine eigene Definition fuer den Operator erstellt haben? --> Dann werden alle Daten kopiert in dem neuen
	//Objekt (auch mit ID) kopiert, was wir mit Loeschen des Copy-Konstruktors vermeiden wollten. 
}

//---------------------Ueberladung der "=="-Operator: ueberpruefen ob die IDs uebereinstimmen: true wenn ja-----------------------
bool Simulationsobjekt::operator==(const Simulationsobjekt& SimObjekt)
{
	//Frage im Skript: Was muss man bei der ID beachten? --> ID ist eine konstante variable und kann nicht bearbeitet werden sobald sie initialisiert wurde.
	//this->p_dMaxGeschwindigkeit = vehicle3.p_dMaxGeschwindigkeit;
	if (this->p_iID == SimObjekt.p_iID)
	{
		return true;
	}

	else
	{
		return false;
	}
	//Frage im Skript: Was wuerde passieren, wenn Sie keine eigene Definition fuer den Operator erstellt haben? --> Dann werden alle Daten kopiert in dem neuen
	//Objekt (auch mit ID) kopiert, was wir mit Loeschen des Copy-Konstruktors vermeiden wollten. 
}

//----------------------Ueberladug der "<<" Operator: Objektdaten werden durch den Operator ausgegeben-------------------
std::ostream& operator<<(std::ostream& o, const Simulationsobjekt& SimObjekt)
{
	SimObjekt.vAusgeben(o);
	std::cout << "" << std::endl;
	return o;
}

//---------------------Ueberladung der ">>" Operator: Objektdaten werden durch den Operator eingegeben--------------------
std::istream& operator>>(std::istream& i, Simulationsobjekt& SimObjekt)
{
	SimObjekt.vEinlesen(i);
	return i;
}


