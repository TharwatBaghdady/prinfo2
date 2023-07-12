#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "PKW.h"
#include "Kreuzung.h"
#include "Simulationsobjekt.h"
#include "SimuClient.h"
#include "Simulation.h"
#include <random>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <random>

extern double dGlobaleZeit = 0.0;

void vAufgabe_1()
{	
	//Fahrzeug Fahrrad("fahrrad_1");
	//Fahrzeug Auto("auto_1");

	int* p = new int[20];
	delete[] p;

	// ----------Erzeugen von verschiedenen Smart-Pointern zum testen------------
	std::unique_ptr<Fahrzeug> p_fahrrad1 = std::make_unique<Fahrzeug>("fahrrad_1");
	std::shared_ptr<Fahrzeug> p_auto1 = std::make_shared<Fahrzeug>("auto_1");
	std::cout << p_auto1.use_count() << std::endl;
	std::shared_ptr<Fahrzeug> p_auto2 = p_auto1;
	std::cout << p_auto1.use_count() << std::endl;

	//std::unique_ptr<Fahrzeug> p_fahrrad2 = p_fahrrad1;
	//std::shared_ptr<Fahrzeug> p_fahrrad2 = move(p_fahrrad1);


	//---Erzeugen von einem Vector, smart ptr in den vector einfügen
	std::vector<std::unique_ptr<Fahrzeug>> vehicles;//
	vehicles.push_back(move(p_fahrrad1)); //smart ptr lassen sicsh nicht kopieren daher den Besitswechsel der Daten auf die Kopie!
	
	std::vector<std::shared_ptr<Fahrzeug>> vehicles_shared;
	vehicles_shared.push_back(p_auto1); //nur kopien des ptrwerden in den vector eingefügt, im gegensatz zu unique ptr (keine Kopien möglich)
	
	vehicles.clear(); //die daten sind nun ewig verloren, die sind auch nicht mehr in fahrrad1 gespeichert... 
	vehicles_shared.clear(); //...im Gegensatz zu shared ptr: nur die kopien in dem Vector wurden geloescht, die Daten befinden sich noch in Auto1
}

//-----------Funktion zum ausgewählten Testen----------
void test()
{
	//----Test fuer die Ueberschrift- und Ausgabefunktion
	{
		/*
		std::unique_ptr<Fahrzeug> p_fahrrad1 = std::make_unique<Fahrzeug>("fahrrad_1", 50);
		p_fahrrad1->vKopf();
		p_fahrrad1->vAusgeben();
		std::cout << "" << std::endl;
		*/
	}

	//------------Test für Fahrrad::dGeschwindikeit-----------------
	{
		/*
			std::unique_ptr<Fahrzeug> Rennrad = std::make_unique<Fahrrad>("Rennrad", 50);
		Rennrad->vKopf();

		double dTakt = 0.25; //15 min

		for (; dGlobaleZeit < 1.25; dGlobaleZeit += dTakt)
		{
			Rennrad->vSimulieren();
			Rennrad->vAusgeben();
			std::cout << "" << std::endl;
		}
		*/
	}
	


	//-------------Test PKW::Ausgeben()------------------
		{
			/*
			std::unique_ptr<Fahrzeug> Audi = std::make_unique<PKW>("Audi", 50, 30, 40);
			Audi->vKopf();

			double dTakt = 0.25; //15 min

			for (; dGlobaleZeit < 1.25; dGlobaleZeit += dTakt)
			{
				Audi->vSimulieren();
				Audi->vAusgeben(o);
				std::cout << "" << std::endl;
			}*/
		}


}

void vAufgabe_1a()
{
	//-----Hier werden ein vector container fuer die Fahrzeuge gemacht, anhand einer Schleife werden vom Benutzer 3 Fahrzeuge eingegeben
	std::vector<std::unique_ptr<Fahrzeug>> vehicles1a;
	for (int i = 0; i < 3; i++)
	{
		std::string sName;
		double dSpeed;
		std::cout << "Bitte geben Sie Daten des " << i + 1 << ". Fahrzeuges: " << std::endl << std::endl;
		std::cout << "Name: ";
		std::cin >> sName;
		std::cout << "Geschwindigkeit: ";
		std::cin >> dSpeed;
		std::cout << "" << std::endl;
		vehicles1a.push_back(move(std::make_unique<Fahrzeug>(sName, dSpeed)));
		std::cout << "" << std::endl;
	}

	double dTakt = 0.25; //Takt in 15 minuten

	for (; dGlobaleZeit < 1.25; dGlobaleZeit += dTakt)
	{
		vehicles1a[0]->vKopf();
		std::cout << "" << std::endl;

		for (int i = 0; i < 3; i++)
		{
			vehicles1a[i]->vSimulieren();
			std::cout << *vehicles1a[i];
			std::cout << "" << std::endl;
		}
	}
}

void vAufgabe_2()
{
	int iFahrrad; //Anzahl der Fahrraeder, eingegeben vom Benutzer
	int iPKW; //Anzahl der PKWs, eingegeben vom Benutzer

	std::vector<std::unique_ptr<Fahrzeug>> vehicles2; //container der Objekte

	std::cout << "Wie viele Fahrraeder wollen Sie eingeben? ";
	std::cin >> iFahrrad;
	std::cout << "" << std::endl;

	//------------------Schleife zum Speichern der Farraeder-daten und fuellen des containers vehicles2--------------------------
	for (int i = 1; i <= iFahrrad; i++)
	{
		std::string sName;
		double dSpeed;

		std::cout << "Bitte geben Sie die Daten des " << i << " Fahrrads:" << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Name: ";
		std::cin >> sName;
		std::cout << "Geschwindigkeit: ";
		std::cin >> dSpeed;
		vehicles2.push_back(move(std::make_unique<Fahrrad>(sName, dSpeed)));
	}

	//Frage im Skript: Warum koennen/sollten Siew keine Fahrzeugobjekte speichern? --> Fahrzeuge ist die Basisklasse, von der man mein Objekt erzeugen kann/sollte, sondern nur von den Unterklassen.
	//Frage im Skript: Warum koennen Sie PKWs und Fahrraeder in einem gemeinsamen Vektor speichern? --> Denn sie sind beide vom selben "Typ", sie sind also beide von derselben Klasse abgeleitet und koennen somit in einem vector-container gespeichert werden.

	std::cout << "Wie viele PKWs wollen Sie eingeben? ";
	std::cin >> iPKW;
	std::cout << "" << std::endl;

	//-----Schleife zum Speichern der PKW-daten und fuellen des containers vehicles2--------------------------------
	for (int i = 1; i <= iPKW; i++)
	{
		std::string sName;
		double dSpeed;
		double dVerbrauch;
		double dTankvolumen;

		std::cout << "Bitte geben Sie die Daten des " << i << " PKW:" << std::endl;
		std::cout << "" << std::endl;
		std::cout << "Name: ";
		std::cin >> sName;
		std::cout << "Geschwindigkeit: ";
		std::cin >> dSpeed;
		std::cout << "Oelverbrauch (in L/100km): ";
		std::cin >> dVerbrauch;
		std::cout << "Ist das Tankvolumen bekannt? (j/n) \n";
		std::string sAntwort;
		std::cin >> sAntwort;
		if (sAntwort == "j")
		{
			std::cout << "Tankvolumen (in Liter): ";
			std::cin >> dTankvolumen;
			vehicles2.push_back(move(std::make_unique<PKW>(sName, dSpeed, dVerbrauch,
				dTankvolumen)));
			std::cout << "" << std::endl;
		}

		else
		{
			vehicles2.push_back(move(std::make_unique<PKW>(sName, dSpeed, dVerbrauch)));
			std::cout << "" << std::endl;
		}
	}

	/*
	* //Löschen
	Fahrzeug f("test");
	Fahrzeug f2 = f;
	f2.vAusgeben(std::cout);
	f2 = f;	
	*/	


	//------------------------Simulation----------------------
	double dTakt = 0.5; //Takt in 30 minuten
	bool bTankstatus = false; //ueberpruefen ob schonmal getankt wurde

	for (; dGlobaleZeit < 4.7; dGlobaleZeit += dTakt)
	{
		
		vehicles2[0]->vKopf();
		std::cout << "" << std::endl;

		for (int i = 0; i < vehicles2.size(); i++)
		{
			vehicles2[i]->vSimulieren();
			std::cout << (*vehicles2[i]);
		}

		if (dGlobaleZeit >= 3.0 && bTankstatus == false)
		{
			std::cout << "" << std::endl; //ich mag abstaende, heutzutage: "Abstand ist die beste Medizin"
			std::cout << "3 Stunden sind um, einige Fahrzeuge moegen keine Oel mehr haben, Wollen Sie tanken? (j/n) \n";
			std::string sAntwort1;
			std::cin >> sAntwort1;
			if (sAntwort1 == "j")
			{
				std::string sAntwort2;
				std::cout << "Wollen Sie alle Fahrzeuge tanken? (j/n) \n";
				std::cin >> sAntwort2;
				if (sAntwort2 == "j")
				{
					for (int i = 0; i < vehicles2.size(); i++)
					{
						double dOelmenge = 0;
						std::cout << "Wie viel Wollen Sie das " << vehicles2[i]->sGetName() << " tanken? (in Liter) ";
						std::cin >> dOelmenge;
						vehicles2[i]->dTanken(dOelmenge);
					}

					bTankstatus = true;
				}
			}
		}

		std::cout << "" << std::endl; //Abstand ist beste Medizin.
	}
}

//-------------Testen der ueberladenen Operatoren------------------
void vAufgabe_3()
{
	std::vector<std::unique_ptr<Fahrzeug>> vehicles3; //ein container zum Testen

	//-----Ein paar Fahrraeder----------------------
	vehicles3.push_back(move(std::make_unique<Fahrrad>("Rennrad", 35)));
	vehicles3.push_back(move(std::make_unique<Fahrrad>("Trekkingrad", 20)));
	vehicles3.push_back(move(std::make_unique<Fahrrad>("CityBike", 0)));
	

	//-------ein paar Autos-----------------------
	vehicles3.push_back(move(std::make_unique<PKW>("Audi", 60, 13, 60)));
	vehicles3.push_back(move(std::make_unique<PKW>("Volvo", 80, 15, 70)));

	//----------Simulation------------------------
	double dTakt = 0.25; //Takt in 15 minuten
	for (; dGlobaleZeit < 1.25; dGlobaleZeit += dTakt)
	{
		vehicles3[0]->vKopf();
		std::cout << "" << std::endl;

		for (int i = 0; i < 5; i++)
		{
			vehicles3[i]->vSimulieren();
			std::cout << *vehicles3[i];
			std::cout << "" << std::endl;
		}

		std::cout << "" << std::endl;

	}

	//--------------Operatoren-Test-------------------

	//Nach Simulation wird zwischen den Autos verglichen (nach Gesamtstrecke).
	if (*vehicles3[3] < *vehicles3[4])
	{
		std::cout << vehicles3[4]->sGetName() << " ist weiter gefahren als " << vehicles3[3]->sGetName() << "." << std::endl;
		std::cout << "" << std::endl;
	}
	else if (*vehicles3[4] < *vehicles3[3])
	{
		std::cout << vehicles3[3]->sGetName() << " ist weiter gefahren als " << vehicles3[4]->sGetName() << "." << std::endl;
		std::cout << "" << std::endl;
	}
	else
	{
		std::cout << vehicles3[3]->sGetName() << "&" << vehicles3[4]->sGetName() << "sind genauso weit gefahren." << "." << std::endl;
		std::cout << "" << std::endl;
	}

	//Fahrraeder werden gleichgesetzt und ausgegeben.
	*vehicles3[2] = *vehicles3[1]; //Die Stammdaten vom CityBike werden vom Trekkingrad uebernommen

	//Ausgabe
	vehicles3[0]->vKopf();
	std::cout << (*vehicles3[0]);
	std::cout << (*vehicles3[1]);
	std::cout << (*vehicles3[2]);
	std::cout << "" << std::endl;
}

void vAufgabe_4()
{
	Weg Templergraben("Templergraben", 2, Tempolimit::Innerorts);
	Templergraben.vKopf();
	std::cout << Templergraben;
}

void vAufgabe_5()
{
	//std::vector<std::unique_ptr<Fahrzeug>> vehicles; //ein container zum Testen.
	Weg Templergraben("Templergraben", 20, Tempolimit::Innerorts); //eine Strasse zum testen.

	//Hinzufuegen einiger Fahrzeuge zu dem Weg.
	Templergraben.vAnnahme(std::make_unique<PKW>("Audi", 30, 30, 60));
	Templergraben.vAnnahme(std::make_unique<PKW>("BMW", 30, 30, 60));
	Templergraben.vAnnahme(std::make_unique<Fahrrad>("CityBike", 20));

	//-------------die Simulation--------------
	Templergraben.vKopf();
	double dTakt = 0.25; //Takt in 15 minuten
	for (; dGlobaleZeit < 1.25; dGlobaleZeit += dTakt)
	{
		//std::cout << "" << std::endl;
		Templergraben.vSimulieren();
		std::cout << dGlobaleZeit << std::endl;
		std::cout << Templergraben << std::endl;
		//std::vSleep(50); 
	}
}

//-------------Funktion zum Generieren von Zufallszahlen----------------
int random_generator()
{
	
	/*static std::mt19937 device(0); //seed = 0;
	std::uniform_int_distribution<int> dist(1, 10); //der Bereich liegt zwischen 1 und 10, wie im Skript angewiesen.
	int zuf = dist(device);
	return zuf;
	*/

	//---------------------Tests fuer Zufall-Mechanismus------------
	
	//Der Bereich, von dem die Zufallszahlen erzeugt werden.
	int a, b = 0;
	std::cout << "Bitte die untere Grenze 'a' festlegen: ";
	std::cin >> a;
	std::cout << "Bitte die obere Grenze 'b' festlegen: ";
	std::cin >> b;
	std::cout << "" << std::endl;

	/*
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(a, b);
	int zuf = dist(device);
	std::cout << "Ihre Zufallszahl" << ": " << zuf << std::endl;
	return zuf;
	*/

	 for (int i = 0; i < 5; i++) //Schleife zur Erzeugung 5 Zufallszahlen
	{
		//dieser Abscnitt steht im Skript und wird dort erklaert
		static std::mt19937 device(0);
		std::uniform_int_distribution<int> dist(a, b);
		int zuf = dist(device);
		std::cout << "Zufallszahl #" << i+1 << ": " << zuf << std::endl;
	}

	return 0;
	

}


void vAufgabe_6()
{
	bInitialisiereGrafik(800, 500); //Ausgabefenster

	
	 //Eine Strasse "Gasse" hat  2 xy-Koordinatenpaare.

	Weg Gasse1("Gassehin", 200, Tempolimit::Innerorts); //der Hinweg zum testen.
	Weg Gasse2("GasseRueck", 200, Tempolimit::Innerorts); //der Ruekweg zum testen.
	int iGasseKoordinaten[4] = { 700, 250, 100, 250 };
	bZeichneStrasse(Gasse1.sGetName(), Gasse2.sGetName(), Gasse1.dGetLaenge(), 2, iGasseKoordinaten);
	//zeichnen von "Gasse" mit Laenge 500 km.

	{
		//Hinzufuegen einiger Fahrzeuge zu Gasse.
		Gasse1.vAnnahme(std::make_unique<PKW>("Audi", 120, 30, 60)); //fahrendes Fahrzeug
		Gasse1.vAnnahme(std::make_unique<PKW>("Volvo", 60, 30, 60), 3); //parkendes Fahrzeug, faehrt zum Zeitpunkt dGLobalezeit = 3 los
		Gasse1.vAnnahme(std::make_unique<PKW>("BMW", 30, 30, 60)); //fahrendes Fahrzeug
		Gasse1.vAnnahme(std::make_unique<Fahrrad>("CityBike", 25)); //fahrendes Fahrrad

		//-------------die Simulation auf Gasse--------------
		std::cout << "Gasse-Simulation" << std::endl;
		std::cout << "" << std::endl;
		Gasse1.vKopf();
		double dTakt = 0.25; //Takt in 15 minuten

		for (; dGlobaleZeit < 7; dGlobaleZeit += dTakt)
		{
			std::cout << "Globalezeit :" << dGlobaleZeit << std::endl;
			std::cout << "" << std::endl;
			vSetzeZeit(dGlobaleZeit); //die aktuelle Zeit -in simulink ganz oben- 
									  //wird damit angezeigt. 
			if (dGlobaleZeit == 3.50)
			{
				Gasse2.vAnnahme(std::make_unique<PKW>("Honda", 60, 30, 60), 4.50);
				//parkendes Fahrzeug, fährt zum Zeitpunkt dGLobalezeit = 3 auf GasseRueck los
			}

			Gasse1.vSimulieren();
			Gasse2.vSimulieren();

			std::cout << Gasse1 << std::endl;
			vSleep(2000);
		}
	}

	
		
}

void vAufgabe_6a()
{
	vertagt::VListe<int> ZufallsListe; //Liste erstellen

	for (int i = 0; i < 10; i++) //Schleife zum Einfuegen 10 Zufallszahlen in die Liste
	{
		int random_number = random_generator();
		ZufallsListe.push_back(random_number); //Zahlen werden in die Liste eingefuegt, 
											   //erstmal aber in p_aktionen.
		ZufallsListe.vAktualisieren(); //Zahlen werden so als Elemente der Liste eingefuegt: 
									   //in p_objekte.

		//Achtung: Die Zahlen werden nur eingefuegt, da wir lediglich pushback benuzten.
	}

	//---------------Ausgabe--------------
	{
		std::list<int>::iterator it;
		std::cout << "Die folgenden Elemente sind in der Zufallsliste enthalten: " << std::endl;
		for (it = ZufallsListe.begin(); it != ZufallsListe.end(); it++)
		{
			std::cout << *it << std::endl;
		}
		std::cout << "" << std::endl; //Abstand ist die beste Medizin, bleib gesund.
	}

	//-------------Loeschen---------------
	{
		std::list<int>::iterator it;
		
		//Ahand dieser Schleife werde die Erase-Aktionen in die p_Aktionen liste eingefuegt, 
		//das heisst aber nicht, dass sie nun geloescht werden, das erfolgt erst nach der 
		//Ausfuehrung von vAktualisieren().
		for (it = ZufallsListe.begin(); it != ZufallsListe.end(); it++)
		{
			std::cout << "Folgendes Element wird von der Zufallsliste geloescht: " << std::endl;
			std::cout << *it << std::endl;
			ZufallsListe.erase(it); //die erase-"Auftraege" werden in die Liste p_aktionen eingefuegt
		}
		std::cout << "" << std::endl;

		//Ausgabe zum Ueberpruefen, dass die Aktionen noch nicht ausgefuehrt wurden, 
		//obwohl sie schon in der p_aktionen Liste enthalten sind
		std::cout << "Die folgenden Elemente sind in der Zufallsliste enthalten: " << std::endl;
		for (it = ZufallsListe.begin(); it != ZufallsListe.end(); it++)
		{
			std::cout << *it << std::endl;
		}
		std::cout << "" << std::endl;

		ZufallsListe.vAktualisieren(); //hier werden dann alle Auftraege auf einmal durchgefuehrt.
		std::cout << "" << std::endl;

		//Ausgabe zum Ueberpruefen, dass die Auftraege ausgefuehrt wurden, 
		//Liste soll leer sein
		std::cout << "Die folgenden Elemente sind in der Zufallsliste enthalten: " << std::endl;
		for (it = ZufallsListe.begin(); it != ZufallsListe.end(); it++)
		{
			std::cout << *it << std::endl;
		}
		std::cout << "" << std::endl;

		//------------Einfuegen 2 veschiedener Zahlen----------

		//einfuegen erfolgt in der selben Liste, in de die Elemente geloescht wurden, 
		//daher derselbe Block

		ZufallsListe.push_back(12); //wenn du hier noch eine Erklaerung benoetigst,  
									//dann solltest wirklich alles von Anfang an wiederholen.
		ZufallsListe.push_front(100);
		ZufallsListe.vAktualisieren();
		//Ausgabe zum Ueberpruefen, dass die Auftraege ausgefuehrt wurden, 
		//Liste soll 12 & 100 enthalten
		std::cout << "Die folgenden Elemente sind in der Zufallsliste enthalten: " << std::endl;
		for (it = ZufallsListe.begin(); it != ZufallsListe.end(); it++)
		{
			std::cout << *it << std::endl;
		}
		std::cout << "" << std::endl;
	}
}

void vAufgabe_7()
{
	bInitialisiereGrafik(1000, 600); //Ausgabefenster

	//--------------------------------------------------------------------
	//--------------------------Kreuzungen--------------------------------
	//--------------------------------------------------------------------
	double TS1 = 0.0; //Tankstelle der 1. Kreuzung
	std::shared_ptr<Kreuzung> Kr1 = std::make_shared<Kreuzung>("Kr1", TS1); //1. Kreuzung
	double TS2 = 10001; //Tankstelle der 2. Kreuzung
	std::shared_ptr<Kreuzung> Kr2 = std::make_shared<Kreuzung>("Kr2", TS2); //2. Kreuzung
	double TS3 = 0.0; //Tankstelle der 3. Kreuzung
	std::shared_ptr<Kreuzung> Kr3 = std::make_shared<Kreuzung>("Kr3", TS3); //3. Kreuzung
	double TS4 = 0.0; //Tankstelle der 4. Kreuzung
	std::shared_ptr<Kreuzung> Kr4 = std::make_shared<Kreuzung>("Kr4", TS4); //4. Kreuzung

	//--------------------------------------------------------------------
	//--------------------------Strassen----------------------------------
	//--------------------------------------------------------------------
	//Strasse1
	Weg W12("W12", 40, Tempolimit::Innerorts, true, Kr2); //der Hinweg von Strasse 1
	Weg W21("W21", 40, Tempolimit::Innerorts, true, Kr1); //der Rueckweg von Strasse 1 
	int iStr1Koordinaten[4] = {680, 40, 680, 300};
	

	//Strasse2
	Weg W23a("W23a", 115, Tempolimit::Autobahn, false, Kr3); //der Hinweg von Strasse 2
	Weg W32a("W32a", 115, Tempolimit::Autobahn, false, Kr2); //der Rueckweg von Strasse 2
	int iStr2Koordinaten[12] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
	
	//Strasse3
	Weg W23b("W23b", 40, Tempolimit::Innerorts, true, Kr3); //der Hinweg von Strasse 3
	Weg W32b("W32b", 40, Tempolimit::Innerorts, true, Kr2); //der Rueckweg von Strasse 3
	int iStr3Koordinaten[4] = {680, 300, 680, 570};
	
	//Strasse4
	Weg W24("W24", 55, Tempolimit::Innerorts, true, Kr4); //der Hinweg von Strasse 4
	Weg W42("W42", 55, Tempolimit::Innerorts, true, Kr2); //der Rueckweg von Strasse 4
	int iStr4Koordinaten[4] = { 680, 300, 320, 300};
	
	//Strasse5
	Weg W34("W34", 85, Tempolimit::Autobahn, false, Kr4); //der Hinweg von Strasse 5
	Weg W43("W43", 85, Tempolimit::Autobahn, false, Kr3); //der Rueckweg von Strasse 5
	int iStr5Koordinaten[10] = { 680, 570, 500, 570, 350, 510, 320, 420, 320, 300};
	
	//Strasse6
	Weg W44a("W44a", 130, Tempolimit::Landstrasse, false, Kr4); //der Hinweg von Strasse 6
	Weg W44b("W44b", 130, Tempolimit::Landstrasse, false, Kr4); //der Rueckweg von Strasse 6
	int iStr6Koordinaten[14] = {320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300};
	
	//--------------------------------------------------------------------
	//-------------------------Verbindungen-------------------------------
	//--------------------------------------------------------------------
	//Verbinden von Kr1 und Kr2 ueber Strasse 1
	Kr1->vVerbinde("W12", "W21", 40, Kr1, Kr2, Tempolimit::Innerorts, true);

	//Verbinden von Kr2 und Kr3 ueber Strasse 3
	Kr2->vVerbinde("W23b", "W32b", 40, Kr2, Kr3, Tempolimit::Innerorts, true);
	
	//verbinden von Kr3 und Kr2 ueber Strasse 2
	Kr1->vVerbinde("W23a", "W32a", 115, Kr2, Kr3, Tempolimit::Autobahn, false);

	//Verbinden von Kr2 und Kr4 ueber Strasse 4
	Kr2->vVerbinde("W24", "W42", 55, Kr2, Kr4, Tempolimit::Innerorts, true);

	//verbinden von Kr4 und Kr3 ueber Strasse 5
	Kr1->vVerbinde("W34", "W43", 85, Kr3, Kr4, Tempolimit::Autobahn, false);

	//verbinden von Kr4 und Kr4 ueber Strasse 6
	Kr1->vVerbinde("W44a", "W44b", 130, Kr4, Kr4, Tempolimit::Landstrasse, false);

	//--------------------------------------------------------------
	//-------------------------Zeichnen-----------------------------
	//--------------------------------------------------------------
	bZeichneKreuzung(680, 40); //zeichnen von Kr1
	bZeichneKreuzung(680, 300); //zeichnen von Kr2
	bZeichneKreuzung(680, 570); //zeichnen von Kr3
	bZeichneKreuzung(320, 300); //zeichnen von Kr4

	bZeichneStrasse(W12.sGetName(), W21.sGetName(), W12.dGetLaenge(), 2, iStr1Koordinaten);
	//zeichnen von "Strasse1" mit Laenge 40 Km, 50Km/h und Ueberholverbot.

	bZeichneStrasse(W23a.sGetName(), W32a.sGetName(), W23a.dGetLaenge(), 6, iStr2Koordinaten);
	//zeichnen von "Strasse2" mit Laenge 115 Km

	bZeichneStrasse(W23b.sGetName(), W32b.sGetName(), W23b.dGetLaenge(), 2, iStr3Koordinaten);
	//zeichnen von "Strasse3" mit Laenge 40 Km, 50Km/h und Ueberholverbot

	bZeichneStrasse(W24.sGetName(), W42.sGetName(), W42.dGetLaenge(), 2, iStr4Koordinaten);
	//zeichnen von "Strasse4" mit Laenge 55 Km, 50Km/h und Ueberholverbot

	bZeichneStrasse(W34.sGetName(), W43.sGetName(), W34.dGetLaenge(), 5, iStr5Koordinaten);
	//zeichnen von "Strasse5" mit Laenge 85 Km

	bZeichneStrasse(W44a.sGetName(), W44b.sGetName(), W44b.dGetLaenge(), 7, iStr6Koordinaten);
	//zeichnen von "Strasse6" mit Laenge 130 Km

	//--------------------------------------------------------------------
	//------------------------Test-Fahrzeuge------------------------------
	//--------------------------------------------------------------------
	std::unique_ptr<PKW> Audi = std::make_unique<PKW>("Audi", 120, 30, 60);
	std::unique_ptr<PKW> Volvo = std::make_unique<PKW>("Volvo", 60, 30, 60);
	std::unique_ptr<PKW> BMW = std::make_unique<PKW>("BMW", 30, 30, 60);
	std::unique_ptr<Fahrrad> CityBike = std::make_unique<Fahrrad>("CityBike", 25); 

	//-------------------------------------------------------------------------------
	//--------------------------Verhehrssystem-Simulation----------------------------
	//-------------------------------------------------------------------------------
	
	Kr1->vAnnahme(move(Audi), 0);
	Kr1->vAnnahme(move(Volvo), 0);
	Kr1->vAnnahme(move(BMW), 0);
	Kr1->vAnnahme(move(CityBike), 0);
	
	/*
	W12.vAnnahme(move(Audi));
	W12.vAnnahme(move(Volvo));
	W12.vAnnahme(move(BMW));
	W12.vAnnahme(move(CityBike));
	*/

	double dTakt = 0.25; //Takt in 15 minuten

	for (; dGlobaleZeit < 7; dGlobaleZeit += dTakt)
	{
		std::cout << "Globalezeit :" << dGlobaleZeit << std::endl;
		std::cout << "" << std::endl;
		vSetzeZeit(dGlobaleZeit); //die aktuelle Zeit -in simulink ganz oben- 
								  //wird damit angezeigt. 
		if (dGlobaleZeit == 3.50)
		{
			Kr1->vAnnahme(std::make_unique<PKW>("Honda", 60, 30, 60), 3.50);
			//parkendes Fahrzeug, fährt zum Zeitpunkt dGLobalezeit = 3.5
		}

		Kr1->vSimulieren();
		Kr2->vSimulieren();
		Kr3->vSimulieren();
		Kr4->vSimulieren();

		vSleep(2000);
	}
}

void vAufgabe_8()
{
	
		std::unique_ptr<PKW> car = std::make_unique<PKW>("");
		std::unique_ptr<Fahrrad> bike = std::make_unique<Fahrrad>("");
		std::shared_ptr<Kreuzung> joint = std::make_shared<Kreuzung>(""); //Test Simulationsobjekte
		
		std::ifstream infile("VO.dat");
		infile.exceptions(std::ios_base::eofbit | std::ios_base::failbit | std::ios_base::badbit); //direkter Nutzung von Exceptionhandling mit ifstream

		try {
			infile >> *car >> *bike >> *joint; //ablesen der Info von der Datei (operator ist geladen)
		} 
		catch (std::runtime_error e)
		{
			std::cout << e.what() << std::endl; //runtime errors lassen sich ausgeben/lesen anhand what().
			return; //abbrechen des Programms beim Auftritt eines Fehlers. 
					//exit() schliesst das GANZE Programm nicht nur vAufgabe_8!
		}

		//Ausgabe der Fahrzeuge
		car->vKopf();
		car->vAusgeben(std::cout);
		std::cout << "" << std::endl;
		bike->vAusgeben(std::cout);
		std::cout << "" << std::endl;
		std::cout << "" << std::endl;
		//Ausgabe der Kreuzung
		joint->vKopf();
		joint->vAusgeben(std::cout);
		std::cout << "" << std::endl;
		std::cout << "" << std::endl;
		

		//std::ifstream infile("Simu.dat"); //lesen der Datei.
}

void vAufgabe_9()
{
	//---------------Einlesen----------------
	std::ifstream infile("Simu.dat"); //Oeffnung der Eingabedatei.
	Simulation simu; //Erzeugung von einem Objekt der Klasse Simulation
	simu.vEinlesen(infile); //Einlesen der Eingabedaten anhand der Einlese-Funktion

	//---------------Simulation----------------
	double dDauer;
	std::cout << "Geben Sie bitte die Simulationsdauer [h] ein: " << std::endl;
	std::cin >> dDauer;

	double dTakt;
	std::cout << "Geben Sie bitte den Zeitschritt [h] ein: " << std::endl;
	std::cin >> dTakt;

	for (; dGlobaleZeit < dDauer; dGlobaleZeit += dTakt)
	{
		std::cout << "Globalezeit :" << dGlobaleZeit << std::endl;
		std::cout << "" << std::endl;
		vSetzeZeit(dGlobaleZeit); //die aktuelle Zeit -in simulink ganz oben- 
								  //wird damit angezeigt. 
		simu.vSimulieren(dDauer, dTakt);
	}
}

void vAufgabe_9a()
{
	//---------------Einlesen----------------
	std::ifstream infile("SimuDisplay.dat"); //Oeffnung der Eingabedatei.
	Simulation simu; //Erzeugung von einem Onjekt der Klasse Simulation
	simu.vEinlesen(infile, true); //Einlesen der Eingabedaten anhand der Einlese-Funktion

	//---------------Simulation----------------
	double dDauer;
	std::cout << "Geben Sie bitte die Simulationsdauer [h] ein: " << std::endl;
	std::cin >> dDauer;

	double dTakt;
	std::cout << "Geben Sie bitte den Zeritschritt [h] ein: " << std::endl;
	std::cin >> dTakt;

	for (; dGlobaleZeit < dDauer; dGlobaleZeit += dTakt)
	{
		std::cout << "Globalezeit :" << dGlobaleZeit << std::endl;
		std::cout << "" << std::endl;
		vSetzeZeit(dGlobaleZeit); //die aktuelle Zeit -in simulink ganz oben- 
								  //wird damit angezeigt. 
		simu.vSimulieren(dDauer, dTakt);
	}
}

int main()
{
	//vAufgabe_6();
	//vAufgabe_7();
	//vAufgabe_8();
	//vAufgabe_9();
	vAufgabe_9a();
	return 0;
}