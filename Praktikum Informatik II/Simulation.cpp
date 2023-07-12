#include "Simulation.h"

//-------------Einlesen aller Elemente in einer Datei e---------------------
void Simulation::vEinlesen(std::istream& e, bool bMitgrafik)
{
	int iZeile = 0;//zaehler fuer Zeilennummer, wird bei jeder Iteration (jede neue Zeile) inkrementiert.

	e.exceptions(std::ios_base::eofbit | std::ios_base::failbit | std::ios_base::badbit);

	if (bMitgrafik)
	{
		bInitialisiereGrafik(1500, 1500); //Ausgabefenster
	}

	try {

		std::string keyword = "";
		e >> keyword;

		while (!e.eof()) //solange das Dateiende nicht erreicht ist.
		{
			iZeile++;
			if (keyword == "KREUZUNG")
			{	
				//Einlesen der Daten der Kreuzung
				std::string sName = "";
				e >> sName;
				double dTankstelle = 0;
				e >> dTankstelle;

				auto it1 = m.find(sName); //hier wird nach der Kreuzung in der Karte gesucht 
										  //und in einen Iterator gespeichert
				if (it1 != m.end()) //wenn gefunden
				{
					throw std::runtime_error("Kreuzung ist schon eingelesen worden!");
					//dann wird ausgegeben, dass die Kreuzung und nicht erneut mit 
					//mit dem selben Namen gespeichert werden soll.
				}

				else { 
					m[sName] = std::make_shared<Kreuzung>(sName, dTankstelle); 
					//einfugen einer neuen Kreuzung in die Karte m.
				}

				if (bMitgrafik)
				{
					//Einlesen der Koordinaten
					int iX, iY;
					e >> iX;
					e >> iY;
					bZeichneKreuzung(iX, iY); //zeichnen der Kreuzung.
				}
			}

			else if (keyword == "STRASSE")
			{
				//Einlesen der Startkreuzung, siehe Reihenfolge der Daten im Skript
				std::string sKrzStart;
				e >> sKrzStart;
				auto it2 = m.find(sKrzStart);
				if (it2 == m.end()) //wenn Start-Kreuzung nicht gefunden
				{
					throw std::runtime_error("Die Startkreuzung existiert nicht!");
				}

				//Einlesen der Zielkreuzung
				std::string sKrzZiel;
				e >> sKrzZiel;
				auto it3 = m.find(sKrzZiel);
				if (it3 == m.end()) //wenn Ziel-Kreuzung nicht gefunden
				{
					throw std::runtime_error("Die Zielkreuzung existiert nicht!");
				}

				//Einlesen der Hin- und Rueckweg
				std::string sHinweg = "";
				e >> sHinweg;
				std::string sRueckweg = "";
				e >> sRueckweg;

				//Einlesen der Strassenlaenge
				int iLaenge = 0;
				e >> iLaenge;

				//Einlesen des Tempolimits (als int)
				int iTempolimit = 0;
				e >> iTempolimit;
				//Aus der Eingabe (1, 2 oder 3) wird anhand des Switch-Statement 
				//das Tempolimit festegelegt, das Tempolimit wird dann in als Parameter 
				//in vVerbinde() eingegeben. Das wird naemlich so gemacht, 
				//denn Objekte vom Typ lassen sich nicht mit >> einlesen.
				Tempolimit Limit = Tempolimit::Autobahn;
				switch (iTempolimit)
				{
				case 1:
					Limit = Tempolimit::Innerorts;
					break;
				case 2:
					Limit = Tempolimit::Landstrasse;
					break;
				case 3:
					Limit = Tempolimit::Autobahn;
					break;
				default:
					throw std::runtime_error("Undefiniertes Tempolimit!");
				}

				//Einlesen des Ueberholverbots
				int iVerbot = 1;
				e >> iVerbot;
				bool bVerbot = true;
				switch (iVerbot)
				{
				case 0:
					bVerbot = false;
					break;
				case 1:
					bVerbot = true;
					break;
				default:
					throw std::runtime_error("Undefinierte Eingabe zu Ueberholverbot!");
				}

				//durch das Verbinden der Strassen werden die Strassen -intern- erzeugt,
				//zudem machen sich die Wege bekannt.
				it2->second->vVerbinde(sHinweg, sRueckweg, (double) iLaenge, m[sKrzStart], m[sKrzZiel], Limit, bVerbot);
				//ob it2 oder it3 ist vollkommen egal, siehe implementierung in Kreuzung.cpp

				if (bMitgrafik)
				{
					//Einlesen der Daten
					int iPaare;
					e >> iPaare;
					int iKoordinaten[20]; //möglichst gross und glecihzeitig sinnvoll
					for (int i = 0; i < iPaare * 2; i++)
					{
						e >> iKoordinaten[i];
					}
					//Zeichnen der Strasse
					bZeichneStrasse(sHinweg, sRueckweg, iLaenge, iPaare, iKoordinaten);
				}
			}

			else if (keyword == "PKW")
			{
			    //das Einlesen erfolgt analog zu oben.
				std::string sName = "";
				e >> sName;

				double dGeschwindigkeit = 0;
				e >> dGeschwindigkeit;

				double dVerbrauch = 0;
				e >> dVerbrauch;

				double dTankvolumen = 55;
				e >> dTankvolumen;

				std::string sStartKrz = "";
				e >> sStartKrz;

				double dStartzeit = 0;
				e >> dStartzeit;

				auto it4 = m.find(sStartKrz);
				if (it4 == m.end()) //wenn Kreuzung nicht gefunden
				{
					throw std::runtime_error("Die Startkreuzung existiert nicht!");
				}

				else {
					//Erstellen des Autos anhand der oberen Daten
					std::unique_ptr<PKW> car = std::make_unique<PKW>(sName, dGeschwindigkeit, dVerbrauch, dTankvolumen);
					//dann einfuegen in die eingelesene Kreuzung
					m[sStartKrz]->vAnnahme(move(car), dStartzeit);
				}
			}

			else if (keyword == "FAHRRAD") {

			     //Einlesen erfolgt wie oben

			     std::string sName = "";
			     e >> sName;

				 double dGeshwindigkeit = 0;
				 e >> dGeshwindigkeit;

				 std::string sStartKrz = "";
				 e >> sStartKrz;

				 double dStartzeit = 0;
				 e >> dStartzeit;

				 auto it5 = m.find(sStartKrz);
				 if (it5 == m.end()) //wenn Kreuzung nicht gefunden
				 {
					 throw std::runtime_error("Die Startkreuzung existiert nicht!");
				 }

				 else {
					 //Erstellen und einfuegen erfolgt wie bei PKW
					 std::unique_ptr<Fahrrad> bike = std::make_unique<Fahrrad>(sName, dGeshwindigkeit);
					 m[sStartKrz]->vAnnahme(move(bike), dStartzeit);
				 }
            }

			else {
				throw std::runtime_error("Undefiniertes Keyword!");
			}

			e >> keyword; //naechste Zeile wird eingelesen
		}
	} 
	
	catch(std::runtime_error error) //Schlüsselwort unbekannt
	{
		//std::cout << error.what() << std::endl;
		//Mit den folgenden if-Abfragen werden die syntaktischen Fehler gefangen.
        if (e.bad())
		{
			std::cout << "Datei kann nicht geoeffnet werden." << std::endl;
			std::cout << "" << std::endl;
			return;
		}
		
		else if (e.fail())
		{
			std::cout << "Vorgangfehler (z.B Formatfehler)!" << std::endl;
			std::cout << "Fehler in Zeilennummer: " << iZeile << std::endl;
			std::cout << "" << std::endl;
			return;
		}
		
		else if (e.eof())
		{
			std::cout << "Datei ist leer oder Dateiende ist erreicht worden." << std::endl;
			std::cout << "" << std::endl;
			return;
		}
		
		//hier werden dann die semantischen Fehler gefangen, 
		//siehe dazu Implementierung im try-block.
		std::cout << error.what() << std::endl; //runtime errors lassen sich ausgeben/ablesen anhand what().
		std::cout << "Fehler in Zeilennummer: " << iZeile << std::endl;
		std::cout << "" << std::endl;
		return; //abbrechen des Programms beim Auftritt eines Fehlers. 
				//exit() schliesst das GANZE Programm nicht nur vAufgabe_8!
	}
}

//---------------Simulieren aller in der Karte (map) existierenden Kreuzungen-------------------------- 
void Simulation::vSimulieren(double dDauer, double dTakt)
{
	for (; dGlobaleZeit < dDauer; dGlobaleZeit += dTakt)
	{
		std::cout << "Globalezeit :" << dGlobaleZeit << std::endl;
		std::cout << "" << std::endl;
		vSetzeZeit(dGlobaleZeit); //die aktuelle Zeit -in simulink ganz oben- 
								  //wird damit angezeigt. 
		for (auto it = m.begin(); it != m.end(); it++)
		{
			it->second->vSimulieren(); //elemente der 'zweiten' Stelle von map werden simuliert
									   
			vSleep(500);
		}
	}
}
