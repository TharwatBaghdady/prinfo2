#pragma once
#include "Fahrausnahme.h"
class Streckenende :
    public Fahrausnahme
{
public:
    Streckenende(Fahrzeug& v, Weg& s);
    void vBearbeiten();
};

