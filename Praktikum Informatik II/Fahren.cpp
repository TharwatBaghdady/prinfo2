#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

//----------------dStrecke() fuer fahrende Fahrzeuge-----------------

double Fahren::dStrecke(Fahrzeug& vehicle, double dZeitIntervall)
{
	Weg& street = this->wGetWeg(); //eine Kopie der Strassse

	double dStreckeMax = dZeitIntervall * vehicle.dGeschwindigkeit(); //die fahrbare Strecke vom Fahrzeug in dem gegebenen Zeitintervall 
																    
	double dRestStrecke = street.dGetSchranke() - vehicle.dGetAbschnitt(); //die restliche Strecke eines Weges.
	//dRestStrecke = Abstand zwischen dem ersten Fahrzeug und dem nächsten.

	if (dStreckeMax > dRestStrecke)
	{
		if (dRestStrecke > 0) //nächstes auto im Intervall aber nicht hinter dem ersten
		{
			
			return dRestStrecke;		
		}

		std::cout << vehicle.sGetName() << " ist am Ende des Weges." << std::endl;
		throw Streckenende(vehicle, street); //die zugehoerige Fahrausnahme wird hier geworfen.
		//anhand exception handling wird die Funktionlitaet ergaenzt daher ist kein return dRestsrecke mehr noetig.
	}

	return dStreckeMax;
		
	
}