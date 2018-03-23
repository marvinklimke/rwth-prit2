// file:	FahrAusnahme.h
// author:	Marvin Klimke
// date:	12.09.2016

#pragma once

#include "Fahrzeug.h"
#include "Weg.h"

// Diese Klasse stellt abstrakt eine Ausnahmesituation beim Fahren der Fahrzeuge dar.
class FahrAusnahme
{

public:

	// Erstellt ein Ausnahmeobjekt mit dem Zeiger auf ein Fahrzeug und einen Weg.
	FahrAusnahme(Fahrzeug* pFahrzeug, Weg* pWeg);

	// Standard-Destruktor.
	virtual ~FahrAusnahme();

	// Behandelt die aufgetretene Ausnahme
	virtual void vBearbeiten() = 0;

protected:
	
	// Zeiger auf das Fahrzeug, welches die Ausnahme ausl�st.
	Fahrzeug* p_pFahrzeug;

	// Zeiger auf den Weg, wo die Ausnahme auftrat.
	Weg* p_pWeg;

};

