#include "Streckenende.h"
#include "PKW.h"
#include "Kreuzung.h"

Streckenende::Streckenende(Fahrzeug& v, Weg& s):
	Fahrausnahme(v, s)
{
}

//------------Implementierung der Fahrausnahme: Streckenende----------
void Streckenende::vBearbeiten()
{
	//Loeschen des Fahrzeuges aus der Fahrzeugliste des Weges bei Antritt der Ausnahme
	//Einfuegen des Fahrzeuges in einen zufaelligen Weg, der von der Kreuzung abgeht
	for (auto it = streetAus.p_pFahrzeuge.begin(); it != streetAus.p_pFahrzeuge.end(); it++)
	{
		if ((*it).get() == &vehicleAus && *it != nullptr) //doppelt dereferenziert, da it Zeiger auf einen anderen Zeiger ist.
		{
			
			if (streetAus.pGetKreuzung().lock()->dGetTankstelle() != 0)
			{
				streetAus.pGetKreuzung().lock()->vTanken(**it); //Tanken des Fahrzeuges.
			}

			streetAus.p_pFahrzeuge.erase(it); //loeschen des parkenden Fahrzeuges aus der liste.

			if (streetAus.pGetKreuzung().lock()->p_pWege.size() > 2) //Wenn die Kreuzung mehrere Strassen 
								                                     //verbindet, 1 Strasse = 2 Wege
			{
				Weg& streetEin = streetAus.pGetKreuzung().lock()->pZufaelligerWeg(streetAus); //neuer zufälliger wegWeg

				std::cout << std::resetiosflags(std::ios::left);
				std::cout << std::setw(10) << "ZEIT: " << std::setw(15) << dGlobaleZeit << std::endl;
				std::cout << std::setw(10) << "KREUZUNG: " << std::setw(15) << streetAus.pGetKreuzung().lock()->sGetName() << "   " << streetAus.pGetKreuzung().lock()->dGetTankstelle() << std::endl;
				std::cout << std::setw(10) << "WECHSEL: " << std::setw(15) << streetAus.sGetName() << " ---> " << streetEin.sGetName() << std::endl;
				std::cout << std::setw(10) << "FAHRZEUG: " << std::setw(15) << it->get()->sGetName() << std::setw(15) << it->get()->dGeschwindigkeit() << " km/h" << std::endl;

				streetEin.vAnnahme(move(*it)); //einfuegen des Fahrzeuges "Fahrend" 
											   //in einen zufaelligen Weg aus der Kreuzung.
			}
			
			else {
				std::cout << std::resetiosflags(std::ios::left);
				std::cout << std::setw(10) << "ZEIT: " << std::setw(15) << dGlobaleZeit << std::endl;
				std::cout << std::setw(10) << "KREUZUNG: " << std::setw(15) << streetAus.pGetKreuzung().lock()->sGetName() << "   " << streetAus.pGetKreuzung().lock()->dGetTankstelle() << std::endl;
				std::cout << std::setw(10) << "WECHSEL: " << std::setw(15) << streetAus.sGetName() << " ---> " << streetAus.pGetRueckweg()->sGetName() << std::endl;
				std::cout << std::setw(10) << "FAHRZEUG: " << std::setw(15) << it->get()->sGetName() << std::setw(15) << it->get()->dGeschwindigkeit() << " km/h" << std::endl;

				streetAus.pGetRueckweg()->vAnnahme(move(*it)); //sonst fuehrt die geliche Strasse
			}

			
		}
	}

	std::cout << "" << std::endl;
	std::cout << "" << std::endl;
}


