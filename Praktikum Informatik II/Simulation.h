#pragma once
#include <iostream>
#include <fstream>
#include "Fahrrad.h"
#include "PKW.h"
#include "Kreuzung.h"
#include <map>

class Simulation
{
	public:
		void vEinlesen(std::istream&, bool bMitgrafik = false); //default = false
		void vSimulieren(double, double);
		std::map<std::string, std::shared_ptr<Kreuzung>> m;
};

