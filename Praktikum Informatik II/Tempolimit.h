#pragma once

//-----------Benutzter-definierter Datentyp fuer Tempolimit-------- 
enum class Tempolimit
{
	Innerorts = 50, //   km/h
	Landstrasse = 100, // km/h
	Autobahn = std::numeric_limits<int>::max() // unbegrenzt!
};
