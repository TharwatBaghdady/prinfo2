#pragma once
#include "Fahrausnahme.h"
class Losfahren :
    public Fahrausnahme
{
public:
    Losfahren(Fahrzeug& v, Weg& s);
    void vBearbeiten();
};

