#pragma once
#include <exception>
#include <stdexcept>
#include "Fahrzeug.h"
#include "Weg.h"

class Fahrausnahme : std::exception
{
	protected:
		Fahrzeug& vehicleAus;
		Weg& streetAus;
	public:
		Fahrausnahme(Fahrzeug& v, Weg& s);
		virtual void vBearbeiten() = 0;
};

