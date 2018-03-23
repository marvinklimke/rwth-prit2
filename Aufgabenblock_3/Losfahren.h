// file:	Losfahren.h
// author:	Marvin Klimke
// date:	12.09.2016

#pragma once

#include "FahrAusnahme.h"

// Diese Klasse stellt eine Ausnahme, ausgel�st durch das Losfahren eines Fahreuges, dar.
class Losfahren : public FahrAusnahme
{

public:

	// Erstellt ein Ausnahmeobjekt mit dem Zeiger auf ein Fahrzeug und einen Weg.
	Losfahren(Fahrzeug* pFahrzeug, Weg* pWeg);

	// Standard-Destruktor.
	virtual ~Losfahren();

	// Diese Funktion behandelt die Losfahren-Ausnahme.
	virtual void vBearbeiten();
};

